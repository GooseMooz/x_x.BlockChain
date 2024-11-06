#include "BlockChain.h"

BlockChain::BlockChain(int difficulty) : difficulty(difficulty) {
    chain.emplace_back(createGenesisBlock());
}

void BlockChain::addBlock(Block newBlock) {
    newBlock.previousHash = getLatestBlock().hash;
    newBlock.mineBlock(difficulty);
    chain.push_back(std::move(newBlock));
}

Block BlockChain::getLatestBlock() const {
    return chain.back();
}

Block BlockChain::createGenesisBlock() {
    std::vector<Transaction> genesisTransactions;
    genesisTransactions.emplace_back("0", "Genesis", 0.0);
    return Block(0, "0", genesisTransactions);
}
