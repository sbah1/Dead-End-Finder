/*
Sulaiman Bah
CIS 3501
Fall 2020
Prof. John Baugh
*/

//Node.cpp
//Description: Implementation for Node class functions.
//Version: 1.01
//Changelog:
	//v1.01:
		//Debugged and fixed the getEdge function (see changelog above code there for details)

#include "Node.h" //Node class reference

using namespace std; //Namespace definition

//Takes in a number and sets it as the node's ID
void Node::setID(int x) 
{
	nodeID = x; //Set the node ID to X
}

//Gets and returns the node's ID
int Node::getID() 
{
	return nodeID; //Return the node's ID
}

//Takes in a true/false value and sets it as the visited status
void Node::setVisited(bool x) 
{
	visited = x; //Set the visited status to x
}

//Gets and returns the visited status of the node
bool Node::getVisited() 
{
	return visited; //Return the visisted status
}

//Takes a given edge ID and adds it as a connecting edge
void Node::addEdge(int x) 
{
	connectingEdge.push_back(x); //Add a connecting edge into the vector
}

//Returns an edge based on a position in a for loop, provided that an edge exists in the vector
//Version: 1.1
//Debugged: YES! (v1.0->v1.1)
//Changelog:
	//Offset return connectingEdge[] statement by -1 to prevent vector out of range crash later down the line (v1.1)
int Node::getEdge(int x) 
{
	if (x >= connectingEdge.size()) //if the position attempted to visit exceeds the number of edges in the vector
		return -1; //Return -1 as an error code, so the loop knows to break
	else
		return connectingEdge[x] - 1; //Return the edge
}

//Returns isolated status
bool Node::isIsolated()
{
	if (connectingEdge.size() > 0) //If there is a connecting edge attached to the node
		return false; //Node is not isolated, return false
	else //If no connecting edges
	{
		isolated = true; //Set isolated status to true
		return true; //Node is isolated, return true
	}
}

//Takes in a true/false value and sets it as the dead end status
void Node::setDeadEndStatus(bool x)
{
	isDeadEnd = x; //Set dead end status to input
}

//Gets and returns the dead end status of the node
bool Node::getDeadEndStatus()
{
	return isDeadEnd; //Return dead end status
}