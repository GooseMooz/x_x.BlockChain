#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H

#include "BlockChain.h"
#include <asio.hpp>
#include <thread>

/**
 * @class Node
 * @brief Represents a blockchain node that listens for network requests.
 */
class Node {
public:
    /**
     * @brief Constructor for the Node class.
     * @param port The port on which the node will listen.
     * @param difficulty The mining difficulty.
     */
    Node(unsigned short port, int difficulty);

    /**
     * @brief Starts the node and begins listening for connections.
     */
    void start();

private:
    asio::io_service io_service;          ///< ASIO service object
    asio::ip::tcp::acceptor acceptor;     ///< Accepts incoming connections
    BlockChain blockchain;                ///< The blockchain instance
    int difficulty;                       ///< Mining difficulty

    /**
     * @brief Starts accepting connections.
     */
    void acceptConnections();

    /**
     * @brief Handles a client session.
     * @param socket The socket connected to the client.
     */
    void handleClient(asio::ip::tcp::socket socket);
};

#endif // BLOCKCHAIN_NODE_H
