#include "Node.h"

int main() {
    const unsigned short port = 12345; // Choose a suitable port
    const int difficulty = 4;          // Mining difficulty

    Node node(port, difficulty);
    node.start();

    return 0;
}
