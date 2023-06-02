#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    // Set the current number of Nodes in NodeList
    this->length = 0;

    // Initialise the NodeList with empty nodes
    int i = 0;
    for (int row=0; row < ENV_DIM; row++)
    {
        for (int col=0; col < ENV_DIM; col++)
        {
            nodes[i] = new Node(row, col, 0);
            std::cout << "Created Node[" << i << "]";
            std::cout << " at [" << row << "][" << col << "]";
            std::cout << std::endl;
            i++;
        }
    }
}

NodeList::~NodeList(){
    // TODO
}

NodeList::NodeList(NodeList& other){
    // TODO
}

int NodeList::getLength(){
    return this->length;
}

void NodeList::addElement(Node* newPos){
    this->length++;
    this->nodes[length] = newPos;
}

Node* NodeList::getNode(int i){
    return this->nodes[i];
}