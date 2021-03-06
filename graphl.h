//
// Created by Temesgen on 2/15/2020.
//

#ifndef PROGRAM3_GRAPHL_H
#define PROGRAM3_GRAPHL_H

#include <cstdlib>
#include <iomanip>
#include "nodedata.h"

using namespace std;
const int MAXNODES = 100;


struct EdgeNode; // forward reference for the compiler
struct GraphNode { //  structs used for simplicity, use classes if desired

    EdgeNode* edgeHead; // head of the list of edges

    NodeData data; // data information about each node

    bool visited;
};

struct EdgeNode {

    int adjGraphNode; // subscript of the adjacent graph node

    EdgeNode* nextEdge;
};

class GraphL{
public:
    GraphL();

    virtual ~GraphL();

    void buildGraph(ifstream& infile);

    void depthFirstSearch();

    void displayGraph() const;

private:

    GraphNode* graphNodes[MAXNODES];     // adjacency list of nodes

    void insertEdge(int source, int dest);

    void searchHelper(int v);

};


#endif //PROGRAM3_GRAPHL_H
