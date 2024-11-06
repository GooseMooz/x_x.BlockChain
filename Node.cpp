#include "Node.h"
#include <iostream>
#include <asio.hpp>
#include <thread>
#include <mutex>

Node::Node(unsigned short port, int difficulty)
    : acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
      blockchain(difficulty), difficulty(difficulty) {}

void Node::start() {
    std::cout << "Node started. Listening on port " << acceptor.local_endpoint().port() << std::endl;
    acceptConnections();
    io_service.run();
}

void Node::acceptConnections() {
    acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket) {
        if (!ec) {
            std::thread(&Node::handleClient, this, std::move(socket)).detach();
        }
        acceptConnections();
    });
}

void Node::handleClient(asio::ip::tcp::socket socket) {
    try {
        asio::streambuf buffer;
        asio::read_until(socket, buffer, "\n");
        std::istream is(&buffer);
        std::string request;
        std::getline(is, request);

        // Parse the request (simple protocol)
        if (request == "GET_BLOCKCHAIN") {
            // Send the blockchain data
            std::ostringstream oss;
            for (const auto &block : blockchain.chain) {
                oss << "Block ID: " << block.id << "\n";
                oss << "Timestamp: " << block.timestamp << "\n";
                oss << "Previous Hash: " << block.previousHash << "\n";
                oss << "Hash: " << block.hash << "\n";
                oss << "Nonce: " << block.nonce << "\n";
                oss << "Transactions:\n";
                for (const auto &tx : block.transactions) {
                    oss << tx.getTransactionData() << "\n";
                }
                oss << "------------------------\n";
            }
            std::string response = oss.str();
            asio::write(socket, asio::buffer(response));
        } else if (request.find("ADD_TRANSACTION") == 0) {
            // Extract transaction details
            // Format: ADD_TRANSACTION sender receiver amount
            std::istringstream iss(request);
            std::string cmd, sender, receiver;
            double amount;
            iss >> cmd >> sender >> receiver >> amount;
            Transaction tx(sender, receiver, amount);
            tx.signTransaction(sender + "_PrivateKey"); // Simplified signing
            if (tx.isValid()) {
                // Lock the blockchain for thread safety
                std::lock_guard<std::mutex> lock(blockchain_mutex);

                // Create a new block with this transaction
                std::vector<Transaction> transactions = {tx};
                Block newBlock(blockchain.getLatestBlock().id + 1,
                               blockchain.getLatestBlock().hash, transactions);
                blockchain.addBlock(newBlock);
                std::string response = "Transaction added and block mined.\n";
                asio::write(socket, asio::buffer(response));
            } else {
                std::string response = "Invalid transaction.\n";
                asio::write(socket, asio::buffer(response));
            }
        } else {
            std::string response = "Unknown command.\n";
            asio::write(socket, asio::buffer(response));
        }
    } catch (std::exception &e) {
        std::cerr << "Client session error: " << e.what() << std::endl;
    }
}
