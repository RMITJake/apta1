#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){
    // TODO
}

int Node::getRow(){
    return this->row;
}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    // int manhattanDistance = (this->col + goal->getCol())*-1 + (this->row - goal->getRow())*-1;
    int cols = this->col - goal->getCol();
    int rows = this->row - goal->getRow();
    if(cols < 0)
    {
        cols *= -1;
    }
    if(rows < 0)
    {
        rows *= -1;
    }

    int manhattanDistance = cols + rows;
    // std::cout << "|--------------------------------------------|" << std::endl;
    // std::cout << "|this->col " << this->col;
    // std::cout << ". goal->col " << goal->getCol();
    // std::cout << ", col-gcol = " << cols << std::endl;

    // std::cout << "|this->row " << this->row;
    // std::cout << ", goal->row " << goal->row;
    // std::cout << ", row-grow = " << rows << std::endl;
    // std::cout << "|Manhattan distance = " << manhattanDistance << std::endl;
    // std::cout << "|--------------------------------------------|" << std::endl;
    // std::cout << "this->col - goal->col " << this->col - goal->getCol() << std::endl;
    // std::cout << "this->row - goal->row " << this->row - goal->getRow() << std::endl;

    return this->dist_traveled + manhattanDistance;
    // distance_travelled of node p + Manhattan distance from p to G
    // Manhattan_distance = |colp − colG| + |rowp − row G|
}
    
//--------------------------------                             