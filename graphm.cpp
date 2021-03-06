////
//// Created by Temesgen on 2/12/2020.
////

#include "graphm.h"
#include "nodedata.h"
#include <climits>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// ------------------------------------Default Constructor-----------------------------------------------

// Description

// Default Constructor: Constructor that initializes all instance variables

// preconditions: None
// postconditions: T.dist and all C are infinity, visited is false, path is 0

// --------------------------------------------------------------------------------------------

GraphM::GraphM(){
    size = 0;

    for(int i = 1; i < MAXNODES; i++){ //initialize all slots of T and C
        for(int j = 1; j < MAXNODES; j++){
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
            C[i][j] = INT_MAX;
        }
    }
}


// ------------------------------------buildGraph---------------------------------------------

// Description

// buildGraph: function to build a graph given a valid input txt file
// preconditions: The txt file is valid, formatted, and all is as expected
// postconditions: T and C are correctly updated with the cost relationships

// --------------------------------------------------------------------------------------------

void GraphM::buildGraph(ifstream& infile){
    int from = 0;
    int to = 0;
    int cost = 0;
    string inputVal = "";

    infile >> inputVal;
    infile.get();

    if(inputVal != "") {

        size = stoi(inputVal); //string to integer
        inputVal = "";

        for (int i = 1; i <= size; i++) {
            data[i].setData(infile);
        }

        while (!infile.eof()) {
            infile >> from >> to >> cost;
            infile.get();

            if (from != 0)
                insertEdge(from, to, cost);
            else
                break;
        }
    }
}

// ------------------------------------insertEdge---------------------------------------------

// Description

// insertEdge: function to update the cost between two nodes
// preconditions: Valid input, ie no negatives
// postconditions: C is correctly updated

// --------------------------------------------------------------------------------------------

void GraphM::insertEdge(int from, int to, int cost){
    if(cost >= 0)
        C[from][to] = cost;
    else
        cout << "Invalid input for cost";
}

// ------------------------------------removeEdge---------------------------------------------

// Description

// removeEdge: function to return the cost between two nodes to Infinity
// preconditions: None
// postconditions: C is properly reset and nothing else is changed

// --------------------------------------------------------------------------------------------

void GraphM::removeEdge(int from, int to){
    C[from][to] = INT_MAX;      //reset the edge value to infinity
}

// ------------------------------------findShortestPath---------------------------------------------

// Description

// findShortestPath: finds shortest paths from every node to every other node
// preconditions: None
// postconditions: T is correctly updated with only the shortest valid paths

// --------------------------------------------------------------------------------------------

void GraphM::findShortestPath(){ //O(n^3)
    int minVect = 0;
    for(int from = 1; from <= size; from++){
        T[from][from].dist = 0;

        for(int j = 1; j <= size; j++){
            int curMin = INT_MAX;
            for(int min = 1; min <= size; min++){ //find min vector
                if(T[from][min].dist < curMin && !(T[from][min].visited)){
                    curMin = T[from][min].dist;
                    minVect = min;
                }
            }
            T[from][minVect].visited = true;

            for(int i = 1; i <= size; i++){
                if((T[from][i].visited) || (C[minVect][i] == INT_MAX)) {
                    continue;
                }
                if ((T[from][i].dist > (T[from][minVect].dist + C[minVect][i]))) {
                        T[from][i].dist = T[from][minVect].dist + C[minVect][i];
                        T[from][i].path = minVect;
                }
            }
        }
    }
}

// ------------------------------------getPath---------------------------------------------

// Description

// getPath: function to recursively get the path from one node to another
//          Helper method for display and displayAll
// preconditions: A path exists between from and to
// postconditions: The path is printed out correctly to the console

// --------------------------------------------------------------------------------------------

void GraphM::getPath(int from, int to){
    if(from != to){
        if(T[from][to].path != 0)
            getPath(from, T[from][to].path);
    }

    cout << to << " ";
}

// ------------------------------------display---------------------------------------------

// Description

// display: function to print the shortest path from one node to another
// preconditions: A path exists between from and to
// postconditions: The path is not changed, and correct path is printed

// --------------------------------------------------------------------------------------------

void GraphM::display(int from, int to){
    cout << endl;
    if(from <= 0 || to <= 0 || from > 100 || to > 100)
        cout << "Error printing, invalid path node" << endl;

    else if(T[from][to].dist != INT_MAX){

        cout << from << setw(20) << to;
        cout << setw(20) << T[from][to].dist << setw(20);
        getPath(from, to);
        cout << endl;
    }
    else{

        cout << from << setw(20) << to;
        cout << setw(20) << " ----";
        cout << endl;
        return;
    }

    getPathData(from, to);
    cout << data[to];
    cout << endl;
}

// ------------------------------------getPathData---------------------------------------------

// Description

// getPathData: function to recursively get path name data in a path
//          Helper method for display
// preconditions: A path exists between from and to
// postconditions: The path is printed out correctly to the console

// --------------------------------------------------------------------------------------------
void GraphM::getPathData(int from, int to){
    if(from != to){
        if(T[from][to].path != 0)
            getPathData(from, T[from][to].path);
    }
    cout << data[(T[from][to].path)] << endl;
}


// ------------------------------------displayAll---------------------------------------------

// Description

// displayAll: function to display all the nodes' paths
// preconditions: None
// postconditions: The paths are printed out correctly and unchanged

// --------------------------------------------------------------------------------------------
void GraphM::displayAll(){
    cout << endl;
    cout << "Description     " << "From Node    " << "To Node    " << "Dijikstra's  ";
    cout << "Path" << endl;


    for(int i = 1;i <= size; i++){

        cout << data[i] << endl;

        for(int j = 1; j <= size; j++){
            if(i != j) {
                if (T[i][j].dist > 0 && T[i][j].dist < INT_MAX) {
                    cout << setw(20) << i << setw(10) << j << " ";
                    cout << setw(10) << T[i][j].dist << setw(13);
                    getPath(i, j);
                    cout << endl;
                }else{
                    cout << setw(20) << i << setw(10) << j;
                    cout << setw(15) << "-----" << endl;
                }
            }
        }
    }

}