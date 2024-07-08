#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <vector>
#include "Block.h"

class BlockChain {
public:
    BlockChain();

    /*
     * Adds new block to the chain, calculating hashes.
     * Doesn't have any verifying mechanism yet. WIP.
     */
    void addBlock(Block& newBlock);

    /*
     * Returns latest block in the chain.
     */
    Block getLatestBlock() const;

private:
    /*
     * Vector representing the blockchain.
     * Right now doesn't have any self-clearing mechanisms. WIP.
     */
    std::vector<Block> chain;

    /*
     * Generates genesis block.
     * Right now has "0" hash. WIP
     */
    static Block initBlockChain();
};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
