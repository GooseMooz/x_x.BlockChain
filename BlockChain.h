#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <vector>
#include "Block.h"

/**
 * @class BlockChain
 * @brief Represents the blockchain.
 */
class BlockChain {
public:
    /**
     * @brief Constructor for the BlockChain class.
     * @param difficulty The mining difficulty.
     */
    explicit BlockChain(int difficulty);

    /**
     * @brief Adds a new block to the blockchain.
     * @param newBlock The block to add.
     */
    void addBlock(Block newBlock);

    /**
     * @brief Gets the latest block in the blockchain.
     * @return The latest block.
     */
    Block getLatestBlock() const;

    /**
     * @brief The chain of blocks.
     */
    std::vector<Block> chain; ///< Exposed for simplicity

private:
    int difficulty;           ///< The mining difficulty

    /**
     * @brief Creates the genesis block.
     * @return The genesis block.
     */
    static Block createGenesisBlock();
};

#endif // BLOCKCHAIN_BLOCKCHAIN_H
