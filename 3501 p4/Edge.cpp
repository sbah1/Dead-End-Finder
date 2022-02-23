/*
Sulaiman Bah
CIS 3501
Fall 2020
Prof. John Baugh
*/

//Edge.cpp
//Desctiption: Implementation for Edge class functions.
//Version: 1.00

#include "Edge.h" //Edge class reference
#include <iostream> //Needed for error reporting

using namespace std; //Namespace definition

//Takes in a number and sets it as the edge's ID#
void Edge::setID(int x)
{
	edgeID = x; //Sets the edge ID# as the number passed in
}

//Gets the edge ID#
int Edge::getID() 
{
	return edgeID; //Returns edge ID#
}

//Takes in a true/false value and sets it as the dead end status
void Edge::setDeadEndStatus(bool x) 
{
	isDeadEnd = x; //Sets the dead end status as the value passed in
}

//Gets the dead end status attached to this edge
bool Edge::getDeadEndStatus() 
{
	return isDeadEnd; //Returns dead end status
}

//Adds a connected node ID# to the connected nodes list
void Edge::addConnectedNode(int x) 
{
	if (connectedNodes.size() < 2) //If there are less than 2 nodes in the list already
		connectedNodes.push_back(x); //add the connected node to the list
	else //If the list is full, and the program is attempting to add a third node to a full edge
	{
		cout << "ERROR: Cannot add connected vertex to a full edge (vertex added to edge with 2 connected nodes)." << endl;
		cout << "Closing program..." << endl;
		exit(-1); //Exit the program with an error code
	}
}

//Returns the connected node ID#s to an array of size 2 (DO NOT PASS IN AN ARRAY LARGER THAN A SIZE OF 2)
void Edge::getConnectedNodes(int x[]) 
{
	x[0] = connectedNodes[0]; //Return the first connected node
	x[1] = connectedNodes[1]; //Return the second connected node
}