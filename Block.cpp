#include <openssl/evp.h>
#include <iostream>
#include <ctime>
#include <sstream>
#include <utility>
#include <iomanip>
#include <vector>

class Block {
public:
    int id;
    std::string timestamp;
    std::string data;
    std::string hash;
    std::string previousHash;
    std::vector<std::string> txs;
    int nonce = 0;

    Block(int tx, std::string prevHash, std::string blockData) {
        id = tx;
        timestamp = std::to_string(std::time(nullptr));
        data = std::move(blockData);
        hash = calculateHash();
        previousHash = std::move(prevHash);
    }

    std::string calculateHash() const {
        std::stringstream ss;
        ss << id << previousHash << timestamp << data;
        return sha256(ss.str());
    }

private:
    static std::string sha256(const std::string &inputStr) {
        EVP_MD_CTX* context = EVP_MD_CTX_new();
        if (context == nullptr) {
            throw std::runtime_error("Failed to create context!");
        }

        const EVP_MD* md = EVP_sha256();
        unsigned char hashCalculate[EVP_MAX_MD_SIZE];
        unsigned int hashLen = 0;

        if (EVP_DigestInit_ex(context, md, nullptr) != 1) {
            EVP_MD_CTX_free(context);
            throw std::runtime_error("Failed to initialize digest!");
        }

        if (EVP_DigestUpdate(context, inputStr.c_str(), inputStr.size()) != 1) {
            EVP_MD_CTX_free(context);
            throw std::runtime_error("Failed to update digest!");
        }

        if (EVP_DigestFinal_ex(context, hashCalculate, &hashLen) != 1) {
            EVP_MD_CTX_free(context);
            throw std::runtime_error("Failed to finalize digest!");
        }

        EVP_MD_CTX_free(context);

        std::stringstream ss;
        for (unsigned int i = 0; i < hashLen; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hashCalculate[i];
        }

        return ss.str();
    }
};
