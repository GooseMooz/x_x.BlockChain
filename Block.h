#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H
#include <iostream>

class Block {
public:
    /*
     * Block ID
     */
    int index;

    /*
     * Timestamp of a Block
     */
    std::string timestamp;

    /*
     * Data/Message of a Block
     */
    std::string data;

    /*
     * Hash of a previous Block
     */
    std::string previousHash;

    /*
     * Hash of this Block
     */
    std::string hash;

    /*
     * Simple Block constructor. WIP
     */
    Block(int tx, std::string prevHash, std::string blockData);

    /*
     * Function for calculating hash of a current block.
     * Right now doesn't use any additional information for Security and Identity. WIP.
     */
    std::string calculateHash() const;
};

#endif //BLOCKCHAIN_BLOCK_H