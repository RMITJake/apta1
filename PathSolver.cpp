#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    // std::cout << std::endl;
    // std::cout << "###########################" << std::endl;
    // std::cout << "#    Inside PathSolver    #" << std::endl;
    // std::cout << "###########################" << std::endl;
}   

PathSolver::~PathSolver(){
    // TODO
}

void PathSolver::forwardSearch(Env env){
    // std::cout << std::endl;
    // std::cout << "###########################" << std::endl;
    // std::cout << "#   Inside FowardSearch   #" << std::endl;
    // std::cout << "###########################" << std::endl;
    
    // Create a NodeList for key nodes
    NodeList* KeyNodes = new NodeList();
    NodeList* WallNodes = new NodeList();
    NodeList* AvailableNodes = new NodeList();
    NodeList* ExploredNodes = new NodeList();
    NodeList* DeadEnds = new NodeList();

    // Delcare the key nodes
    Node* GoalNode = nullptr;
    Node* StartNode = nullptr;

    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cin >> env[row][col];
            if (env[row][col] == SYMBOL_START)
            {
                StartNode = new Node(row, col, 0);
                KeyNodes->addElement(StartNode);
                AvailableNodes->addElement(StartNode);
                // std::cout << "Starting node = ";
                // std::cout << "[" << StartNode->getRow() << "]";
                // std::cout << "[" << StartNode->getCol() << "]";
                // std::cout << std::endl; 
            }
            else if (env[row][col] == SYMBOL_GOAL)
            {
                GoalNode = new Node(row, col, 0);
                KeyNodes->addElement(GoalNode);
                AvailableNodes->addElement(GoalNode);
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

    // std::cout << std::endl;
    // std::cout << "###########################" << std::endl;
    // std::cout << "#   Setting CurrentPos    #" << std::endl;
    // std::cout << "###########################" << std::endl;
    // Must be included in below loop
    Node* CurrentPosition = StartNode;
    // std::cout << "Initial node added to availablenodes" << std::endl;
    ExploredNodes->addElement(CurrentPosition);
    // std::cout << "Initial node added to explorednodes" << std::endl;

    while(CurrentPosition != GoalNode)
    // for(int loopCounter=0; loopCounter < 2; loopCounter++)
    {

        // std::cout << "CurrentPosition = ";
        // std::cout << "[" << CurrentPosition->getRow() << "]";
        // std::cout << "[" << CurrentPosition->getCol() << "]";
        // std::cout << "[" << CurrentPosition->getEstimatedDist2Goal(GoalNode) << "]";
        // std::cout << std::endl;

        NodeList* SurroundingNodes = getSurroundingNodes(CurrentPosition, AvailableNodes, ExploredNodes);
        // std::cout << "Next unexplored nodes = ";
        // for (int i = 0; i < unexploredNodes->getLength(); i++)
        // {
        //     std::cout << "[" << unexploredNodes->getNode(0)->getRow() << "]";
        //     std::cout << "[" << unexploredNodes->getNode(0)->getCol() << "]";
        //     std::cout << "[" << unexploredNodes->getNode(0)->getEstimatedDist2Goal(GoalNode) << "]";
        // }
        // std::cout << std::endl;

        // std::cout << "SurroundingNodes->getLength() = " << SurroundingNodes->getLength() << std::endl;
        if(SurroundingNodes->getLength() == 0)
        {
            CurrentPosition = backTrack(CurrentPosition, AvailableNodes, ExploredNodes, SurroundingNodes, DeadEnds);
            for (int i = 0; i < DeadEnds->getLength(); i++)
            {
                // std::cout << "Node added to DeadEnds = ";
                // std::cout << "[" << DeadEnds->getNode(i)->getRow() << "]";
                // std::cout << "[" << DeadEnds->getNode(i)->getCol() << "]";
                // std::cout << std::endl; 
            }
        }

        // for (int i = 0; i < SurroundingNodes->getLength(); i++)
        // {
        //     std::cout << "In surrounding nodes = ";
        //     std::cout << "[" << SurroundingNodes->getNode(i)->getRow() << "]";
        //     std::cout << "[" << SurroundingNodes->getNode(i)->getCol() << "]";
        //     std::cout << "[" << SurroundingNodes->getNode(i)->getEstimatedDist2Goal(GoalNode) << "]";
        //     std::cout << std::endl; 
        // }

        // Check Surrounding Nodes - Maybe makes this into a function
        // Check Right Node: Row +0 Col +1
        for (int checkSurrounding = 0; checkSurrounding < SurroundingNodes->getLength(); checkSurrounding++)
        {
           if(CurrentPosition->getEstimatedDist2Goal(GoalNode) <= SurroundingNodes->getNode(checkSurrounding)->getEstimatedDist2Goal(GoalNode))
            {
                CurrentPosition = SurroundingNodes->getNode(checkSurrounding);
            } else {
                CurrentPosition = SurroundingNodes->getNode(checkSurrounding);
            }
        }
        ExploredNodes->addElement(CurrentPosition);
        // std::cout << "Moved to = ";
        // std::cout << "[" << CurrentPosition->getRow() << "]";
        // std::cout << "[" << CurrentPosition->getCol() << "]";
        // std::cout << std::endl; 

        // Print the environment
        // for (int row = 0; row < ENV_DIM; row++)
        //     {
        //         for (int col = 0; col < ENV_DIM; col++)
        //         {
        //             if (env[row][col] == 'G')
        //             {
        //                 env[row][col] = 'G';
        //             }
        //             else if (row == CurrentPosition->getRow() && col == CurrentPosition->getCol())
        //             {
        //                 env[row][col] = 'x';
        //             }
        //             std::cout << env[row][col];
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << "|========================================================" << std::endl;
    }

    NodeList* Solution = new NodeList();
    Solution = Solve(ExploredNodes, DeadEnds, GoalNode);
    Solution = Solution;
    std::cout << "###########################" << std::endl;
    std::cout << "# Printing Solution       #" << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << "# Solution length = " << Solution->getLength() << std::endl;

    for(int i=0; i < Solution->getLength(); i++)
    {
        std::cout << "[" << Solution->getNode(i)->getRow() << "]";
        std::cout << "[" << Solution->getNode(i)->getCol() << "]";
        std::cout << std::endl; 
    }

}

NodeList* PathSolver::getNodesExplored(){
    return this->nodesExplored;
}

NodeList* PathSolver::getPath(Env env){
    return this->Solution;
}

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
            // std::cout << "CheckingAvailableNode = ";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getRow() << "]";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getCol() << "]";
            // std::cout << " Added to surrounding" << std::endl;
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
        if(nextRow == availableRow && currentCol == availableCol)
        {
            // std::cout << "CheckingAvailableNode = ";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getRow() << "]";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getCol() << "]";
            // std::cout << " Added to surrounding" << std::endl;
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
        if(prevCol == availableCol && currentRow == availableRow)
        {
            // std::cout << "CheckingAvailableNode = ";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getRow() << "]";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getCol() << "]";
            // std::cout << " Added to surrounding" << std::endl;
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
        if(prevRow == availableRow && currentCol == availableCol)
        {
            // std::cout << "CheckingAvailableNode = ";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getRow() << "]";
            // std::cout << "[" << AvailableNodes->getNode(checkLoop)->getCol() << "]";
            // std::cout << " Added to surrounding" << std::endl;
            surroundingNodes->addElement(AvailableNodes->getNode(checkLoop));
        }
    }

    // for (int sNodes = 0; sNodes < this->surroundingNodes->getLength(); sNodes++)
    // {
    //     std::cout << "# Surrounding node = ";
    //     std::cout << "[" << this->surroundingNodes->getNode(sNodes)->getRow() << "]";
    //     std::cout << "[" << this->surroundingNodes->getNode(sNodes)->getCol() << "]";
    //     std::cout << "." << std::endl;
    // }

    this->unexploredNodes = new NodeList;


    for (int checkExplored = 0; checkExplored < surroundingNodes->getLength(); checkExplored++)
    {
        Node *CheckNode = surroundingNodes->getNode(checkExplored);

        if (!inExplored(CheckNode, ExploredNodes))
        {
            this->unexploredNodes->addElement(CheckNode);
            // std::cout << "Node " << checkExplored << " = ";
            // std::cout << "[" << CheckNode->getRow() << "]";
            // std::cout << "[" << CheckNode->getCol() << "]";
            // std::cout << " added to unexploredNodes";
            // std::cout << std::endl;
        } 
    }
    return this->unexploredNodes;
}

bool PathSolver::inExplored(Node* CheckNode, NodeList* ExploredNodes)
{
    int currentRow = CheckNode->getRow();
    int currentCol = CheckNode->getCol();
    // std::cout << "Checking node = ";
    // std::cout << "[" << CheckNode->getRow() << "]";
    // std::cout << "[" << CheckNode->getCol() << "]";
    // std::cout << std::endl;


    for (int checkExplored = 0; checkExplored < ExploredNodes->getLength(); checkExplored++)
    {
        int exploredRow = ExploredNodes->getNode(checkExplored)->getRow();
        int exploredCol = ExploredNodes->getNode(checkExplored)->getCol();
        // std::cout << "Comparing with = ";
        // std::cout << "[" << exploredRow << "]";
        // std::cout << "[" << exploredCol << "]";
        // std::cout << std::endl;

        if(currentRow == exploredRow && currentCol == exploredCol)
        {
            // std::cout << "Node is explored = ";
            // std::cout << "[" << currentRow << "]";
            // std::cout << "[" << currentCol << "]";
            // std::cout << std::endl;
            return true;
        }
    }
    return false;

}

Node* PathSolver::backTrack(Node* CurrentPosition, NodeList* AvailableNodes, NodeList* ExploredNodes, NodeList* SurroundingNodes, NodeList* DeadEnds)
{
    // std::cout << "###########################" << std::endl;
    // std::cout << "#       Backtracking      #" << std::endl;
    // std::cout << "###########################" << std::endl;
    int backTrackCounter = 1;
    while (SurroundingNodes->getLength() == 0)
    {
        backTrackCounter++;
        CurrentPosition = ExploredNodes->getNode(ExploredNodes->getLength()-backTrackCounter);
        // std::cout << "CurrentPosition = ";
        // std::cout << "[" << CurrentPosition->getRow() << "]";
        // std::cout << "[" << CurrentPosition->getCol() << "]";
        // std::cout << std::endl;
        SurroundingNodes = getSurroundingNodes(CurrentPosition, AvailableNodes, ExploredNodes);
    }

    DeadEnds->addElement(ExploredNodes->getNode(ExploredNodes->getLength() - backTrackCounter + 1));

    return CurrentPosition;
}

NodeList* PathSolver::Solve(NodeList* ExploredNodes, NodeList* DeadEnds, Node* GoalNode)
{
    std::cout << "###########################" << std::endl;
    std::cout << "#       Solving.....      #" << std::endl;
    std::cout << "###########################" << std::endl;

    NodeList* Solution = new NodeList();
    Node* CurrentPosition = nullptr;

    for(int inDeadEnds=0; inDeadEnds < DeadEnds->getLength(); inDeadEnds++)
    {
        CurrentPosition = DeadEnds->getNode(inDeadEnds);
        std::cout << "DeadEnd nodes = ";
        std::cout << "[" << CurrentPosition->getRow() << "]";
        std::cout << "[" << CurrentPosition->getCol() << "]";
        std::cout << std::endl;
    }

    // for(int node=0; node < ExploredNodes->getLength(); node++)
    // {
    //     std::cout << "Explored nodes = ";
    //     std::cout << "[" << ExploredNodes->getNode(node)->getRow() << "]";
    //     std::cout << "[" << ExploredNodes->getNode(node)->getCol() << "]";
    //     std::cout << std::endl;
    // }


    CurrentPosition = ExploredNodes->getNode(0);
    for(int node=0; node < ExploredNodes->getLength(); node++)
    {

        CurrentPosition = ExploredNodes->getNode(node);
        for(int inDeadEnds=0; inDeadEnds < DeadEnds->getLength(); inDeadEnds++)
        {
            int newnode=node;
            if(inExplored(CurrentPosition, DeadEnds))
            {
                std::cout << "CurrentPosition leads to dead end = ";
                std::cout << "[" << CurrentPosition->getRow() << "]";
                std::cout << "[" << CurrentPosition->getCol() << "]";
                std::cout << std::endl;
                newnode=node;
                // Node* DeadEndPath = ExploredNodes->getNode(node+1);
                // DeadEndPath = DeadEndPath;
                // for(int i=0; i < 3; i++)
                while(CurrentPosition != ExploredNodes->getNode(node-1))
                {
                    CurrentPosition = ExploredNodes->getNode(newnode);
                    std::cout << "Position removed from solution = ";
                    std::cout << "[" << CurrentPosition->getRow() << "]";
                    std::cout << "[" << CurrentPosition->getCol() << "]";
                    std::cout << std::endl;
                    newnode++;
                    // inDeadEnds++;
                }
                newnode--;
                // node++;
            } else {
                std::cout << "CurrentPosition added to solution = ";
                std::cout << "[" << CurrentPosition->getRow() << "]";
                std::cout << "[" << CurrentPosition->getCol() << "]";
                std::cout << std::endl;
                Solution->addElement(CurrentPosition);
            }
            node=newnode;
        }
    }

    return Solution;
}

//-----------------------------