//
// Created by Temesgen on 2/12/2020.
//

#ifndef PROGRAM3_GRAPHM_H
#define PROGRAM3_GRAPHM_H

#include "nodedata.h"
#include <climits>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;


class GraphM
{
public:
    //constructor
    GraphM();

    //buildGraph: use infile to update nodes and costs
    void buildGraph(ifstream& infile);

    //insertEdge: inserts an edge between parameters with specified cost
    void insertEdge(int from, int to, int cost);

    //removeEdge: removes an edge between two nodes
    void removeEdge(int from, int to);

    //findShortestPath: finds all shortest paths between all other nodes
    void findShortestPath();

    //displayAll: display algorithm works
    void displayAll();

    //display: display the path between two nodes
    void display(int from, int to);


private:
    static const int MAXNODES = 100;

    struct TableType {

        bool visited;          // whether node has been visited

        int dist;              // shortest distance from source known so far

        int path;              // previous node in path of min dist
    };

    NodeData data[MAXNODES];              // data for graph nodes

    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix

    int size;                             // number of nodes in the graph

    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path


    //helper methods for display and displayAll
    void getPath(int from, int to);
    void getPathData(int from, int to);

};



#endif //PROGRAM3_GRAPHM_H
