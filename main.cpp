#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
// #include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
// void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    std::cout << "Loaded env" << std::endl;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    // PathSolver* pathSolver = new PathSolver();
    // pathSolver->forwardSearch(env);

    // NodeList* exploredPositions = nullptr;
    // exploredPositions = pathSolver->getNodesExplored();

    // // Get the path
    // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    // NodeList* solution = pathSolver->getPath(env);

    // printEnvStdout(env, solution);

    // delete pathSolver;
    // delete exploredPositions;
    // delete solution;

}

void readEnvStdin(Env env){
    std::cout << "###########################" << std::endl;
    std::cout << "# Inside readEncStdin #####" << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "# env reference: " << env << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "# Reding Input File   #####" << std::endl;
    std::cout << "###########################" << std::endl;

    // Create a NodeList for key nodes
    NodeList* KeyNodes = new NodeList();

    // Node S = new Node(0, 0, 0);
    // Node G = new Node(0, 0, 0);
    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cin >> env[row][col];
            if (env[row][col] == SYMBOL_START)
            {
                Node* S = new Node(row, col, 0);
                KeyNodes->addElement(S);
            }
            else if (env[row][col] == SYMBOL_GOAL)
            {
                Node* G = new Node(row, col, 0);
                KeyNodes->addElement(G);
            } else if (env[row][col] == SYMBOL_WALL)
            {
                // Node* W = new Node(row, col, 0);
            } else if (env[row][col] == SYMBOL_EMPTY)
            {
                // Node* E = new Node(row, col, 0);
            }
        }
    }
    std::cout << "S is at location: [" << KeyNodes->getNode(1)->getRow() << "][" << KeyNodes->getNode(1)->getCol() << "]" << std::endl;
    std::cout << "G is at location: [" << KeyNodes->getNode(2)->getRow() << "][" << KeyNodes->getNode(2)->getCol() << "]" << std::endl;

    std::cout << "###########################" << std::endl;
    std::cout << "# Printing Env        #####" << std::endl;
    std::cout << "###########################" << std::endl;
    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }
    std::cout << "#TBD#######################" << std::endl;
    std::cout << "# Print Key Nodes     #####" << std::endl;
    std::cout << "###########################" << std::endl;

    std::cout << "###########################" << std::endl;
    std::cout << "# Print Random Chars  #####" << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "[0][3]: " << env[0][3];
    std::cout << std::endl;
    std::cout << "[2][1]: " << env[2][1];
    std::cout << std::endl;
    std::cout << "[5][9]: " << env[5][9];
    std::cout << std::endl;
    std::cout << "[4][8]: " << env[4][8];
    std::cout << std::endl;
    std::cout << "[9][3]: " << env[9][3];
    std::cout << std::endl;
}

// void printEnvStdout(Env env, NodeList* solution) {
//     //TODO
// }

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}