#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);
char pathSymbol(int solutionNode, NodeList* Solution);

int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // // Get the path
    // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);
    solution = solution;

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env){
    // Iterate through columns and rows from cin
    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cin >> env[row][col];
        }
    }
}

void printEnvStdout(Env env, NodeList* solution) {
    Node *currentPosition = nullptr;
    for (int solutionNode = 0; solutionNode < solution->getLength(); solutionNode++)
    {
        currentPosition = solution->getNode(solutionNode);
        for (int row = 0; row < ENV_DIM; row++)
        {
            for (int col = 0; col < ENV_DIM; col++)
            {
                // Assign the globally defined symbols
                if (env[row][col] == SYMBOL_GOAL)
                {
                    env[row][col] = SYMBOL_GOAL;
                }
                else if (env[row][col] == SYMBOL_START)
                {
                    env[row][col] = SYMBOL_START;
                }
                else if (row == currentPosition->getRow() && col == currentPosition->getCol())
                {
                    // Check where the next node is
                    env[row][col] = pathSymbol(solutionNode, solution);
                    int nextRow = solution->getNode(solutionNode + 1)->getRow();
                    int nextCol = solution->getNode(solutionNode + 1)->getCol();
                    int currentRow = solution->getNode(solutionNode)->getRow();
                    int currentCol = solution->getNode(solutionNode)->getCol();

                    // Assign the current node symbol based on the next nodes location
                    if(nextCol == currentCol+1)
                    {
                        env[row][col] = '>';
                    } else if (nextRow == currentRow+1){
                        env[row][col] = 'v';
                    } else if (nextCol == currentCol-1){
                        env[row][col] = '<';
                    } else if (nextRow == currentRow-1){
                        env[row][col] = '^';
                    }
                }
            }
        }
    }
    
    // Print out the environment solution
    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void testNode() {
    // std::cout << "TESTING Node" << std::endl;

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
    // std::cout << "TESTING NodeList" << std::endl;

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

char pathSymbol(int solutionNode, NodeList* Solution)
{
    int nextRow = Solution->getNode(solutionNode + 1)->getRow();
    int nextCol = Solution->getNode(solutionNode + 1)->getCol();
    int currentRow = Solution->getNode(solutionNode)->getRow();
    int currentCol = Solution->getNode(solutionNode)->getCol();

    if(nextCol == currentCol+1)
    {
        return '>';
    } else if (nextRow == currentRow+1){
        return 'v';
    } else if (nextCol == currentCol-1){
        return '<';
    } else if (nextRow == currentRow-1){
        return '^';
    }

    return 'x';
}