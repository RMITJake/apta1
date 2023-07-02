#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    // availableNodes - saves the coordinates of each of the empty nodes
    availableNodes = new NodeList();
    // wallNodes - saves the coordinates of each of the wall nodes
    wallNodes = new NodeList();
    // nodesExplored - saves the list of nodes which have been explored
    nodesExplored = new NodeList();
    // deadEnd - saves the nodes which are discovered to be dead ends after the backtrack method
    deadEnds = new NodeList();
    // solution - holds the final path for the robot
    solution = new NodeList();

    // Delcare the key nodes
    GoalNode = nullptr;
    StartNode = nullptr;
    CurrentPosition = nullptr;
}

PathSolver::~PathSolver()
{
    // TODO
}

void PathSolver::forwardSearch(Env env)
{
    // Iterate through the environment map and app nodes to their respective lists
    // Iterate through rows
    for (int row = 0; row < ENV_DIM; row++)
    {
        // Iterate through columns
        for (int col = 0; col < ENV_DIM; col++)
        {
            // std::cin to take the map character by character as input
            std::cin >> env[row][col];
            // Check if [row][col] matches the start symbol
            if (env[row][col] == SYMBOL_START)
            {
                // Create the start node with a dist_traveled value of 0
                this->StartNode = new Node(row, col, 0);
                // Add the start node to the list of nodes that are available to be explored
                this->availableNodes->addElement(this->StartNode);
            }
            // Check if [row][col] matches the goal symbol
            else if (env[row][col] == SYMBOL_GOAL)
            {
                // Create the goal node with a dist_traveled value of 0
                this->GoalNode = new Node(row, col, 0);
                // Add the goal node to the list of nodes that are available to be explored
                this->availableNodes->addElement(this->GoalNode);
            }
            // Check if [row][col] matches the wall symbol
            else if (env[row][col] == SYMBOL_WALL)
            {
                // Create a wall node with a dist_traveled value of 0
                Node* WallNode = new Node(row, col, 0);
                // Add the wall node to the list of wall nodes that cannot be explored
                this->wallNodes->addElement(WallNode);
            }
            // Check if [row][col] matches the empty symbol
            else if (env[row][col] == SYMBOL_EMPTY) {
                // Create an empty node with a dist_traveled value of 0
                Node* EmptyNode = new Node(row, col, 0);
                // Add the empty node to the list of empty nodes that are available be explored
                this->availableNodes->addElement(EmptyNode);
            }
        }
    }

    // Set current position as the starting position and then add the current position to the explored nodes list
    this->CurrentPosition = setCurrentPosition(this->StartNode, this->nodesExplored);

    // create the distance tracker with a value of 0
    int distanceTracker = 0;
    
    // main loop
    while(this->CurrentPosition != this->GoalNode)
    {
        // Start distance tracker at 1
        distanceTracker++;
        // Get surrounding nodes
        NodeList* SurroundingNodes = getSurroundingNodes(this->CurrentPosition, this->availableNodes, this->nodesExplored);

        // If there are no nodes in the surrounding nodes list, backtrack
        if(SurroundingNodes->getLength() == 0)
        {
            this->CurrentPosition = backTrack(this->CurrentPosition, this->availableNodes, this->nodesExplored, SurroundingNodes, this->deadEnds);
        }

        // Create an empty closest node
        Node *ClosestNode = nullptr;
        for (int checkSurrounding = 0; checkSurrounding < SurroundingNodes->getLength(); checkSurrounding++)
        {
            if(this->CurrentPosition->getEstimatedDist2Goal(this->GoalNode) <= SurroundingNodes->getNode(checkSurrounding)->getEstimatedDist2Goal(this->GoalNode))
            {
                // If the goal to dist of current node is closer than closest node, make this closest node
                ClosestNode = SurroundingNodes->getNode(checkSurrounding);
            }
            if(ClosestNode == nullptr)
            {
                // If closest node hasn't been set yet, initialize it here
                ClosestNode = SurroundingNodes->getNode(checkSurrounding);
            }
            this->CurrentPosition = ClosestNode;
            this->CurrentPosition->setDistanceTraveled(distanceTracker);
        }
        this->CurrentPosition = setCurrentPosition(CurrentPosition, this->nodesExplored);
    }

    this->solution = solve(this->nodesExplored, this->deadEnds, this->GoalNode);
}

NodeList* PathSolver::getNodesExplored()
{
    return this->nodesExplored;
}

NodeList* PathSolver::getPath(Env env)
{
    return this->solution;
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

    // Check all nodes up, left, below, and right of the current node, if they are available add them to the surrounding nodes list
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

    // node list to store the available but unexplored nodes
    this->unexploredNodes = new NodeList;

    // go through the available node list, if the current node is not in available nodes add that node to unexplored nodes
    for (int checkExplored = 0; checkExplored < surroundingNodes->getLength(); checkExplored++)
    {
        Node *CheckNode = surroundingNodes->getNode(checkExplored);

        if (!inExplored(CheckNode, ExploredNodes))
        {
            this->unexploredNodes->addElement(CheckNode);
        } 
    }
    return this->unexploredNodes;
}

bool PathSolver::inExplored(Node* CheckNode, NodeList* ExploredNodes)
{
    int currentRow = CheckNode->getRow();
    int currentCol = CheckNode->getCol();

    // check if the current node is in teh explored node list
    for (int checkExplored = 0; checkExplored < ExploredNodes->getLength(); checkExplored++)
    {
        int exploredRow = ExploredNodes->getNode(checkExplored)->getRow();
        int exploredCol = ExploredNodes->getNode(checkExplored)->getCol();

        if(currentRow == exploredRow && currentCol == exploredCol)
        {
            return true;
        }
    }
    return false;

}

Node* PathSolver::backTrack(Node* CurrentPosition, NodeList* AvailableNodes, NodeList* ExploredNodes, NodeList* SurroundingNodes, NodeList* DeadEnds)
{
    // go backwards down the nodelist until there is an available node in surrounding nodes
    int backTrackCounter = 1;
    while (SurroundingNodes->getLength() == 0)
    {
        backTrackCounter++;
        CurrentPosition = ExploredNodes->getNode(ExploredNodes->getLength()-backTrackCounter);
        SurroundingNodes = getSurroundingNodes(CurrentPosition, AvailableNodes, ExploredNodes);
    }

    // add the last touched node to deadends
    DeadEnds->addElement(ExploredNodes->getNode(ExploredNodes->getLength() - backTrackCounter + 1));
    return CurrentPosition;
}

NodeList* PathSolver::solve(NodeList* ExploredNodes, NodeList* DeadEnds, Node* GoalNode)
{
    NodeList* Solution = new NodeList();
    Node* CurrentPosition = nullptr;

    if(DeadEnds->getLength() == 1)
    {
        DeadEnds->addElement(new Node(1, 1, 0));
    }

    CurrentPosition = ExploredNodes->getNode(0);
    for(int node=0; node < ExploredNodes->getLength(); node++)
    {
        CurrentPosition = ExploredNodes->getNode(node);
        if (DeadEnds->getLength() == 0)
        {
            DeadEnds->addElement(new Node(0, 0, 0));
        }
        for(int inDeadEnds=0; inDeadEnds < DeadEnds->getLength(); inDeadEnds++)
        {
            int newnode=node;
            if(inExplored(CurrentPosition, DeadEnds))
            {
                newnode=node;
                while(CurrentPosition != ExploredNodes->getNode(node-1))
                {
                    CurrentPosition = ExploredNodes->getNode(newnode);
                    newnode++;
                }
                newnode--;
            } else {
                Solution->addElement(CurrentPosition);
            }
            node=newnode;
        }
    }
    return Solution;
}

// Method to take in the new current position, add it to the explored nodes list and return the current position
Node* PathSolver::setCurrentPosition(Node* CurrentPosition, NodeList* ExploredNodes)
{
    ExploredNodes->addElement(CurrentPosition);
    return CurrentPosition;
}

//-----------------------------