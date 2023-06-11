#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // Declare necessary starting Nodes
    // StartNode - holds the starting position
    Node *StartNode;
    // GoalNode - holds the goal position
    Node *GoalNode;
    // CheckNode - used as a temporary iterator in functions
    Node *CheckNode;
    // DeadEndNode - used as a temporary iterator in functions
    Node* DeadEndNode;
    // CurrentPosition - used to store the current node
    Node *CurrentPosition;

    // Delcare NodeLists
    // availableNodes - saves the coordinates of each of the empty nodes
    NodeList *availableNodes;
    // wallNodes - saves the coordinates of each of the wall nodes
    NodeList *wallNodes;
    // unexploredNodes - to temporarily store surroundingNodes which haven't been explored so far
    NodeList *unexploredNodes;
    // solution - to store the solved path
    NodeList* solution;
    // surroundingNodes - to temporarily store the nodes above, right, below, left of the current node
    NodeList *surroundingNodes;
    // deadEnds - to store the nodes which are known to lead to dead ends after the backtrack method is called
    NodeList *deadEnds;

    // Declare Functions
    // setCurrentPosition - to update the current node and add this node to the exploredNodes list
    Node* setCurrentPosition(Node *CurrentPosition, NodeList* ExploredNodes);
    // getSurroundingNodes - to get each node above, right, below, left of the current node
    NodeList* getSurroundingNodes(Node* CurrentPosition, NodeList* AvailableNodes, NodeList* ExploredNodes);
    // inExplored - to check if a node is in the exploredNodes list
    bool inExplored(Node *CheckNode, NodeList *ExploredNodes);
    // backTrack - to iterate backwards through the exploredNodes list until an available node is present
    Node* backTrack(Node *CurrentPosition, NodeList *AvailableNodes, NodeList *NodesExplored, NodeList* SurroundingNodes, NodeList* DeadEnds);
    // solve - to populate the solution nodelist
    NodeList* solve(NodeList* ExploredNodes, NodeList* DeadEnds, Node* GoalNode);
};

#endif //COSC_ASSIGN_ONE_PATHSOLVER