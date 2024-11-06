#include "Transaction.h"
#include <openssl/evp.h>
#include <sstream>
#include <stdexcept>

Transaction::Transaction(std::string sender, std::string receiver, double amount)
        : sender(std::move(sender)), receiver(std::move(receiver)), amount(amount) {}

void Transaction::signTransaction(const std::string &privateKey) {
    // Simplified signature (in practice, use RSA or ECDSA)
    signature = calculateHash() + privateKey;
}

bool Transaction::isValid() const {
    if (sender.empty()) {
        // Genesis transaction
        return true;
    }
    // Simplified verification
    return signature == calculateHash() + sender;
}

std::string Transaction::getTransactionData() const {
    std::stringstream ss;
    ss << sender << receiver << amount << signature;
    return ss.str();
}

std::string Transaction::calculateHash() const {
    std::stringstream ss;
    ss << sender << receiver << amount;
    // Use SHA-256 as before
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    EVP_MD_CTX *context = EVP_MD_CTX_new();
    if (context == nullptr) {
        throw std::runtime_error("Failed to create OpenSSL context");
    }

    std::string data = ss.str();
    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(context, data.c_str(), data.length()) != 1 ||
        EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to compute SHA-256 hash");
    }

    EVP_MD_CTX_free(context);

    std::stringstream hash_ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        hash_ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return hash_ss.str();
}
