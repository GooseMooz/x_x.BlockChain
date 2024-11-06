#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include <string>
#include <vector>
#include "Transaction.h"
#include <openssl/evp.h>

/**
 * @class Block
 * @brief Represents a single block in the blockchain.
 */
class Block {
public:
    int id;                      ///< Block ID
    std::string timestamp;       ///< Timestamp of the block
    std::string previousHash;    ///< Hash of the previous block
    std::string hash;            ///< Current block's hash
    std::vector<Transaction> transactions; ///< List of transactions
    int nonce;                   ///< Nonce used for PoW

    /**
     * @brief Constructor for the Block class.
     * @param id The block ID.
     * @param prevHash The hash of the previous block.
     * @param transactions The list of transactions.
     */
    Block(int id, std::string prevHash, std::vector<Transaction> transactions);

    /**
     * @brief Calculates the hash of the block.
     * @return The calculated hash as a string.
     */
    std::string calculateHash() const;

    /**
     * @brief Mines the block using Proof of Work.
     * @param difficulty The difficulty level (number of leading zeros required in the hash).
     */
    void mineBlock(int difficulty);

    /**
     * @brief Generates a Proof of History timestamp.
     * @return The PoH value as a string.
     */
    std::string generateProofOfHistory() const;

private:
    /**
     * @brief Computes SHA-256 hash of the input string.
     * @param inputStr The input string.
     * @return The SHA-256 hash as a string.
     */
    static std::string sha256(const std::string &inputStr);
};

#endif // BLOCKCHAIN_BLOCK_H
