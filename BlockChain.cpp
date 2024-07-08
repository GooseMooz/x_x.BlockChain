#include "Block.h"
#include <vector>

class BlockChain {
public:
    BlockChain() {
        chain.push_back(initBlockChain());
    }

    void addBlock(Block& newBlock) {
        newBlock.previousHash = getLatestBlock().hash;
        newBlock.hash = newBlock.calculateHash();
        chain.push_back(newBlock);
    }

    Block getLatestBlock() const {
        return chain.back();
    }

private:
    std::vector<Block> chain;

    static Block initBlockChain() {
        return {0, "0", "GenesisBlock"};
    };
};