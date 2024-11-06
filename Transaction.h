#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H

#include <string>

/**
 * @class Transaction
 * @brief Represents a transaction in the blockchain.
 */
class Transaction {
public:
    /**
     * @brief Constructor for the Transaction class.
     * @param sender The sender's address.
     * @param receiver The receiver's address.
     * @param amount The amount to transfer.
     */
    Transaction(std::string sender, std::string receiver, double amount);

    /**
     * @brief Signs the transaction with the sender's private key.
     * @param privateKey The sender's private key.
     */
    void signTransaction(const std::string &privateKey);

    /**
     * @brief Verifies if the transaction is valid.
     * @return True if valid, false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Gets the transaction data as a string.
     * @return The transaction data.
     */
    std::string getTransactionData() const;

private:
    std::string sender;    ///< Sender's address
    std::string receiver;  ///< Receiver's address
    double amount;         ///< Amount to transfer
    std::string signature; ///< Digital signature

    /**
     * @brief Calculates the hash of the transaction.
     * @return The transaction hash.
     */
    std::string calculateHash() const;
};

#endif // BLOCKCHAIN_TRANSACTION_H
