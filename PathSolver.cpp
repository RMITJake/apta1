#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    std::cout << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "#    Inside PathSolver    #" << std::endl;
    std::cout << "###########################" << std::endl;
}   

PathSolver::~PathSolver(){
    // TODO
}

void PathSolver::forwardSearch(Env env){
    std::cout << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "#   Inside FowardSearch   #" << std::endl;
    std::cout << "###########################" << std::endl;
    
    // Create a NodeList for key nodes
    NodeList* KeyNodes = new NodeList();
    NodeList* WallNodes = new NodeList();
    NodeList* UnexploredNodes = new NodeList();
    NodeList* ExploredNodes = new NodeList();

    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cin >> env[row][col];
            if (env[row][col] == SYMBOL_START)
            {
                Node* S = new Node(row, col, 0);
                KeyNodes->addElement(S);
                ExploredNodes->addElement(S);
            }
            else if (env[row][col] == SYMBOL_GOAL)
            {
                Node* G = new Node(row, col, 0);
                KeyNodes->addElement(G);
            } else if (env[row][col] == SYMBOL_WALL)
            {
                Node* W = new Node(row, col, 0);
                WallNodes->addElement(W);
            } else if (env[row][col] == SYMBOL_EMPTY)
            {
                Node* U = new Node(row, col, 0);
                UnexploredNodes->addElement(U);
            }
        }
    }

    std::cout << "###########################" << std::endl;
    std::cout << "# Printing Env            #" << std::endl;
    std::cout << "###########################" << std::endl;
    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "# Print Key Nodes         #" << std::endl;
    std::cout << "###########################" << std::endl;
    
    // Echo the row and col of S
    std::cout << "S is at location: [" << KeyNodes->getNode(0)->getRow() << "][" << KeyNodes->getNode(0)->getCol() << "]";
    // Confirm the symbol at location [row][col]
    std::cout << "[" << env[KeyNodes->getNode(0)->getRow()][KeyNodes->getNode(0)->getCol()] << "]" << std::endl;

    std::cout << "G is at location: [" << KeyNodes->getNode(1)->getRow() << "][" << KeyNodes->getNode(1)->getCol() << "]";
    std::cout << "[" << env[KeyNodes->getNode(1)->getRow()][KeyNodes->getNode(1)->getCol()] << "]" << std::endl;

    std::cout << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "# Print Wall Nodes        #" << std::endl;
    std::cout << "###########################" << std::endl;
    for (int iterator=0; iterator < WallNodes->getLength(); iterator++)
    {
        std::cout << "[" << WallNodes->getNode(iterator)->getRow() << "]";
        std::cout << "[" << WallNodes->getNode(iterator)->getCol() << "]";
        if (iterator != (WallNodes->getLength()-1))
        {
            std::cout << ", ";
        }
    }

    std::cout << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "# Print Unexplored Nodes  #" << std::endl;
    std::cout << "###########################" << std::endl;
    for (int iterator=0; iterator < UnexploredNodes->getLength(); iterator++)
    {
        std::cout << "[" << UnexploredNodes->getNode(iterator)->getRow() << "]";
        std::cout << "[" << UnexploredNodes->getNode(iterator)->getCol() << "]";
        if (iterator != (UnexploredNodes->getLength()-1))
        {
            std::cout << ", ";
        }
    }


    std::cout << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "# Print Random Chars      #" << std::endl;
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

NodeList* PathSolver::getNodesExplored(){
    return this->nodesExplored;
}

// NodeList* PathSolver::getPath(Env env){
//     // TODO
// }

//-----------------------------