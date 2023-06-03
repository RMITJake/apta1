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
    NodeList* AvailableNodes = new NodeList();
    NodeList* ExploredNodes = new NodeList();
    // NodeList* Solution = new NodeList();

    // Delcare the key nodes
    Node* GoalNode = nullptr;

    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cin >> env[row][col];
            if (env[row][col] == SYMBOL_START)
            {
                Node* StartNode = new Node(row, col, 0);
                KeyNodes->addElement(StartNode);
                AvailableNodes->addElement(StartNode);
            }
            else if (env[row][col] == SYMBOL_GOAL)
            {
                GoalNode = new Node(row, col, 0);
                KeyNodes->addElement(GoalNode);
            } else if (env[row][col] == SYMBOL_WALL)
            {
                Node* WallNode = new Node(row, col, 0);
                WallNodes->addElement(WallNode);
            } else if (env[row][col] == SYMBOL_EMPTY)
            {
                Node* EmptyNode = new Node(row, col, 0);
                AvailableNodes->addElement(EmptyNode);
            }
        }
    }

    std::cout << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "#   Setting CurrentPos    #" << std::endl;
    std::cout << "###########################" << std::endl;
    // Must be included in below loop
    Node* CurrentPosition = AvailableNodes->getNode(0);

    for(int loopCounter=0; loopCounter < 13; loopCounter++)
    {
        ExploredNodes->addElement(CurrentPosition);
        std::cout << "CurrentPosition = ";
        std::cout << "[" << CurrentPosition->getRow() << "]";
        std::cout << "[" << CurrentPosition->getCol() << "]";
        std::cout << " explored." << std::endl;

        NodeList* SurroundingNodes = getSurroundingNodes(CurrentPosition, AvailableNodes, ExploredNodes);

        // Check Surrounding Nodes - Maybe makes this into a function
        // Check Right Node: Row +0 Col +1
        CurrentPosition = SurroundingNodes->getNode(0);
        for (int checkSurrounding = 0; checkSurrounding < SurroundingNodes->getLength(); checkSurrounding++)
        {
           //Check which node has the least estimated distance and set currentposition to that node
           if(CurrentPosition->getEstimatedDist2Goal(GoalNode) > SurroundingNodes->getNode(checkSurrounding)->getEstimatedDist2Goal(GoalNode))
           {
                CurrentPosition = SurroundingNodes->getNode(checkSurrounding);
           }
        }
    }


    // std::cout << "###########################" << std::endl;
    // std::cout << "# Printing Env            #" << std::endl;
    // std::cout << "###########################" << std::endl;
    // for (int row = 0; row < ENV_DIM; row++)
    // {
    //     for (int col = 0; col < ENV_DIM; col++)
    //     {
    //         std::cout << env[row][col];
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;
    // std::cout << "###########################" << std::endl;
    // std::cout << "# Print Key Nodes         #" << std::endl;
    // std::cout << "###########################" << std::endl;
    
    // // Echo the row and col of S
    // std::cout << "S is at location: [" << KeyNodes->getNode(0)->getRow() << "][" << KeyNodes->getNode(0)->getCol() << "]";
    // // Confirm the symbol at location [row][col]
    // std::cout << "[" << env[KeyNodes->getNode(0)->getRow()][KeyNodes->getNode(0)->getCol()] << "]" << std::endl;

    // std::cout << "G is at location: [" << KeyNodes->getNode(1)->getRow() << "][" << KeyNodes->getNode(1)->getCol() << "]";
    // std::cout << "[" << env[KeyNodes->getNode(1)->getRow()][KeyNodes->getNode(1)->getCol()] << "]" << std::endl;

    // std::cout << std::endl;
    // std::cout << "###########################" << std::endl;
    // std::cout << "# Print Wall Nodes        #" << std::endl;
    // std::cout << "###########################" << std::endl;
    // for (int iterator=0; iterator < WallNodes->getLength(); iterator++)
    // {
    //     std::cout << "[" << WallNodes->getNode(iterator)->getRow() << "]";
    //     std::cout << "[" << WallNodes->getNode(iterator)->getCol() << "]";
    //     if (iterator != (WallNodes->getLength()-1))
    //     {
    //         std::cout << ", ";
    //     }
    // }

    // std::cout << std::endl;
    // std::cout << "###########################" << std::endl;
    // std::cout << "# Print Unexplored Nodes  #" << std::endl;
    // std::cout << "###########################" << std::endl;
    // for (int iterator=0; iterator < UnexploredNodes->getLength(); iterator++)
    // {
    //     std::cout << "[" << UnexploredNodes->getNode(iterator)->getRow() << "]";
    //     std::cout << "[" << UnexploredNodes->getNode(iterator)->getCol() << "]";
    //     if (iterator != (UnexploredNodes->getLength()-1))
    //     {
    //         std::cout << ", ";
    //     }
    // }
}

NodeList* PathSolver::getNodesExplored(){
    return this->nodesExplored;
}

// NodeList* PathSolver::getPath(Env env){
//     // TODO
// }

NodeList* PathSolver::getSurroundingNodes(Node* CurrentPosition, NodeList* AvailableNodes, NodeList* ExploredNodes)
{
    this->surroundingNodes = new NodeList;

    int currentRow = CurrentPosition->getRow();
    int currentCol = CurrentPosition->getCol();
    int nextRow = currentRow + 1;
    int nextCol = currentCol + 1;
    int prevRow = currentRow - 1;
    int prevCol = currentCol - 1;

    for (int checkLoop = 0; checkLoop < AvailableNodes->getLength(); checkLoop++)
    {
        int availableRow = AvailableNodes->getNode(checkLoop)->getRow();
        int availableCol = AvailableNodes->getNode(checkLoop)->getCol();
        if(nextCol == availableCol && currentRow == availableRow)
        {
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
        if(nextRow == availableRow && currentCol == availableCol)
        {
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
        if(prevCol == availableCol && currentRow == availableRow)
        {
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
        if(prevRow == availableRow && currentCol == availableCol)
        {
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
    }

    return this->surroundingNodes;
}

//-----------------------------