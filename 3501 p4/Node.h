/*
Sulaiman Bah
CIS 3501
Fall 2020
Prof. John Baugh
*/

//Node.h
//Description: Header file for Node classes.
//Version: 1.1
//Changelog:
	//V1.1:
		//Added a setDeadEndStatus and getDeadEndStatus function for referential purposes
		//Added bool isolated and bool isDeadEnd for referential purposes
	//v1.2:
		//Added a numConnectedEdges function for referential purposes

#pragma once
#include <vector> //Needed for vector usage

using namespace std; //Namespace definition

//Node class definition
//Contains a Node ID (nodeID), a visited flag (visited), and a vector for connecting edges (connectingEdge[])
//Working functions are setID(int), getID(), setVisited(bool), getVisited(), addEdge(int), getEdge(int)
//Note: getEdge(int) should be used in a for-loop, with i or its equivalent int value being used as an argument to read the number of edges
class Node
{
private: //Private variables
	int nodeID = 0; //Node ID
	vector<int> connectingEdge; //List of edges it connects to, referenced by the edge ID
	bool visited = false; //Flag for if this node has been visited already
	bool isolated = false; //Flag for if the node is isolated
	bool isDeadEnd = false; //Flag for if the node is a dead end

public: //Public functions
	void setID(int); //Sets ID# for this node
	int getID(); //Returns ID# for this node
	void setVisited(bool); //Sets visited status for this node
	bool getVisited(); //Returns visited status for this node
	void addEdge(int); //Add a connecting edge into the database
	int getEdge(int); //Gets a connecting edge, provided the program hasn't attempted to exceed the size of the vector
	bool isIsolated(); //Returns bool of whether node is isolated (no connected nodes)
	void setDeadEndStatus(bool); //Sets dead end status of the node (Added in 1.1)
	bool getDeadEndStatus(); //Gets dead end status of the node (Added in 1.1)
};
