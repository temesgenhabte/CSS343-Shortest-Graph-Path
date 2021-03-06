//
// Created by Temesgen on 2/15/2020.
//

#include "graphl.h"
#include <iomanip>
#include "nodedata.h"


// ------------------------------------Default Constructor-----------------------------------------------

// Description

// Default Constructor: Constructor that initializes all instance variables

// preconditions: None
// postconditions: All nodes in graphNodes are set to nullptr

// --------------------------------------------------------------------------------------------
GraphL::GraphL() {

    for(int i = 0; i < MAXNODES; i++) {
        graphNodes[i] = nullptr;
    }

}

// ------------------------------------Destructor-----------------------------------------------

// Description

// Destructor: Destructor that frees all the allocated memory

// preconditions: None
// postconditions: No memory leaks

// --------------------------------------------------------------------------------------------
GraphL::~GraphL()
{
    EdgeNode* toDelete;

    for(int i = 1; i < MAXNODES; i++){ //go through all nodes
        if(graphNodes[i] != nullptr) {
            toDelete = graphNodes[i]->edgeHead; //set to head of the list

            while(toDelete != nullptr){ // traverse list
                graphNodes[i]->edgeHead = graphNodes[i]->edgeHead->nextEdge;
                delete toDelete; //move the head, then delete the old head
                toDelete = graphNodes[i]->edgeHead; //set toDelete to new head
            }
        }
    }

    toDelete = nullptr; //clean for memory leaks
}

// ------------------------------------buildGraph---------------------------------------------

// Description

// buildGraph: function to build a graph given a valid input txt file
// preconditions: The txt file is valid, formatted, and all is as expected
// postconditions: Edges are added with correct relationships

// --------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile) {
    int nodeCount;
    int source;
    int dest;
    string name;

    infile >> nodeCount; //store first value
    infile.get(); //move cursor down a line

    if(nodeCount > 0 && nodeCount < MAXNODES){ //check validity

        for(int i = 1; i <= nodeCount; i++){ //set graphNodes
            graphNodes[i] = new GraphNode(); //initialize pointer
            graphNodes[i]->data.setData(infile); //utilize NodeData method
        }


        while(!infile.eof()){ //collect the rest of the data
            infile >> source >> dest;
            infile.get(); //move cursor

            if(source == 0) //end of graph
                break;

            insertEdge(source, dest);
        }
    }else{ //invalid node amount
        cout << "Exceeded 100 node limit" << endl;
    }
}

// ------------------------------------insertEdge---------------------------------------------

// Description

// insertEdge: function to add a node at the head of the list
// preconditions: Valid input, ie no negatives
// postconditions: list is correctly updated

// --------------------------------------------------------------------------------------------

void GraphL::insertEdge(int source, int dest){
        EdgeNode* toAdd = new EdgeNode;
        toAdd->adjGraphNode = dest; //store dest in temp pointer
        toAdd->nextEdge = graphNodes[source]->edgeHead; //point to list head
        graphNodes[source]->edgeHead = toAdd; //insert at the beginning
        toAdd = nullptr; //clean for memory leaks
        delete toAdd;
}

// ------------------------------------depthFirstSearch---------------------------------------------

// Description

// depthFirstSearch: perform a DFS with a helper method and print the DF order
// preconditions: None
// postconditions: The printed paths are correct

// --------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch(){
//    for(int i = 1; i < MAXNODES; i++){
//        if(graphNodes[i] != nullptr)
//            graphNodes[i]->visited = false;      //DELETE THIS IF UNNECESSARY!!
//        else
//            break;
//    }

    cout << endl << "Depth-first ordering: ";

    for(int v = 1; v < MAXNODES; v++){
        if(graphNodes[v] != nullptr){ //for all valid points
            if (!graphNodes[v]->visited)
                searchHelper(v); //helper function call
        }//else
            //break;             //DELETE THIS IF UNNECESSARY!!
    }

    cout << endl << endl;
}

// ------------------------------------searchHelper---------------------------------------------

// Description

// searchHelper: helper method for DFS method
// preconditions: None
// postconditions: The printed paths are correct

// --------------------------------------------------------------------------------------------
void GraphL::searchHelper(int v){
    EdgeNode* search = graphNodes[v]->edgeHead; //start at the beginning

    graphNodes[v]->visited = true; //mark your path
    cout << v << " "; //between each node

    while(search != nullptr){ //traverse list
        if (!graphNodes[search->adjGraphNode]->visited) //go to unvisited nodes
            searchHelper(search->adjGraphNode); //recursive call

        search = search->nextEdge; //step forward
    }
}

// ------------------------------------displayGraph---------------------------------------------

// Description

// displayGraph: function to display all the node lists and edges
// preconditions: None
// postconditions: The lists are not changed, and correct printing format

// --------------------------------------------------------------------------------------------
void GraphL::displayGraph() const{
    EdgeNode* cur;

    cout << endl << "Graph:" << endl;

    for(int i = 1; i < MAXNODES && graphNodes[i] != nullptr; i++){
        cout << "Node " << setw(4) << i << "        "
             << graphNodes[i]->data << endl; //state the node label

        cur = graphNodes[i]->edgeHead; //start at the beginning

        while(cur != nullptr){ //traverse, and display the paths
            cout << "  edge " << i << " " << cur->adjGraphNode << endl;
            cur = cur->nextEdge;
        }
    }

    cout << endl;
}