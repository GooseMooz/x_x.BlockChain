#include "Block.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <thread>
#include <mutex>

// Mutex for thread synchronization
std::mutex mtx;

Block::Block(int id, std::string prevHash, std::vector<Transaction> transactions)
        : id(id), previousHash(std::move(prevHash)), transactions(std::move(transactions)), nonce(0) {
    timestamp = std::to_string(std::time(nullptr));
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << id << previousHash << timestamp << nonce << generateProofOfHistory();
    for (const auto &tx : transactions) {
        ss << tx.getTransactionData();
    }
    return sha256(ss.str());
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');

    auto mine = [&](int thread_id, int max_nonce) {
        while (true) {
            std::lock_guard<std::mutex> lock(mtx);
            if (hash.substr(0, difficulty) == target) {
                break;
            }
            nonce++;
            hash = calculateHash();
            if (nonce >= max_nonce) {
                break;
            }
        }
    };

    const int max_nonce = INT32_MAX;
    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Start mining threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(mine, i, max_nonce);
    }

    // Join threads
    for (auto &t : threads) {
        t.join();
    }
}

std::string Block::generateProofOfHistory() const {
    // Simplified PoH implementation
    std::string poh = sha256(timestamp + previousHash);
    return poh;
}

std::string Block::sha256(const std::string &inputStr) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    EVP_MD_CTX *context = EVP_MD_CTX_new();

    if (context == nullptr) {
        throw std::runtime_error("Failed to create OpenSSL context");
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(context, inputStr.c_str(), inputStr.length()) != 1 ||
        EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to compute SHA-256 hash");
    }

    EVP_MD_CTX_free(context);

    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}
