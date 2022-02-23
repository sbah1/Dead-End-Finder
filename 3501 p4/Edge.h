/*
Sulaiman Bah
CIS 3501
Fall 2020
Prof. John Baugh
*/

//Edge.h
//Description: Header file for Edge classes.
//Version: 1.0

#pragma once
#include <vector> //Needed for vector usage

using namespace std; //Namespace definition

//Edge class definition
//Contains a edge ID# (int), a dead end flag (bool), and a vector of connected nodes, initialized with 2 numbers (connectedNodes)
//Working functions are setID(int), getID(), setDeadEndStatus(bool), getDeadEndStatus(), addConnectedNode(int), and getConnectedNodes(int[])
//Note: Pass in an array of size 2 to getConnectedNodes to return the node ID numbers
class Edge
{
private: //Private variables
	int edgeID = 0; //Edge ID
	vector<int> connectedNodes; //Array to store ID#s of vectors connected to this edge, max of 2
	bool isDeadEnd = false; //Flag for if this edge leads to a dead end

public: //Public functions
	void setID(int); //Sets the ID# of the edge
	int getID(); //Returns Edge ID#
	void setDeadEndStatus(bool); //Changes status of if this leads to a dead end or not
	bool getDeadEndStatus(); //Returns dead end status
	void addConnectedNode(int); //Adds a connected node to this edge (max of 2)
	void getConnectedNodes(int[]); //Returns the connected nodes of this edge
};