/*
Sulaiman Bah
CIS 3501
Fall 2020
Prof. John Baugh
*/

//Functions.cpp
//Description: Implementation for all globally utilized functions.
//Version 1.01
//Changelog:
	//Moved all functions to a separate file

#include <iostream>
#include <fstream>
#include "Functions.h"

//readIn Function
//Takes in two vector lists by address as arguments, one defined for node classes, one defined for edge classes
//Adds data to these two lists, read in by a specified file
//Version: 1.1
//Debugged: YES! (v1.0->v1.1)
//Changelog:
	//Offset node.addEdge() function command by -1 to prevent vector out of range crash (v1.1)
void Functions::readIn(vector<class Node> &n, vector<class Edge> &e)
{
	//Variable init
	ifstream data; //File to read data from
	int numNodes; //Number of nodes to insert
	int numEdges; //Number of edges to insert
	class Node nCreate; //Node used for reference to push into vector
	class Edge eCreate; //Edge used for reference to push into vector
	int node1; //First connecting node
	int node2; //Second connecting node
	int c = 0; //Counter
	int id; //Edge ID

			//Read from file
	data.open("Input\\Data.txt");

	if (!data) //If data file didn't open
	{
		cout << "A fatal error has occurred and the program needs to quit." << endl;
		cout << "Error: No data input found." << endl << endl;

		system("pause");
		exit(-1);
	}

	//Get number of nodes and edges
	data >> numNodes; //Get number of Nodes
	data >> numEdges; //Get number of edges

	for (int i = 0; i < numNodes; i++) //Create nodes
	{
		n.push_back(nCreate); //Create a new node
		n[i].setID(i + 1); //Update ID# of new node
	}

	for (int i = 0; i < numEdges; i++) //Create edges
	{
		e.push_back(eCreate); //Create a new edge
		e[i].setID(i + 1);
	}

	while (!data.eof())
	{
		//Get data
		data >> node1; //Get first connecting node
		data >> node2; //Get second connecting node
		id = e[c].getID(); //Get the ID# of this selected edge

						   //Create connection on an edge
		e[c].addConnectedNode(node1); //Add the first connected node
		e[c].addConnectedNode(node2); //Add the second connected node

									  //Note connection in respective nodes
		n[node1 - 1].addEdge(id); //Input edge into first node
		n[node2 - 1].addEdge(id); //Input edge into second node

								  //Increase counter
		c++;
	}
}

//getUnvisited Function
//Finds the last unvisited node in the node list, n
//If all nodes are visited, function will return -1 to let program know all nodes have been visited
//Function primarily used to find a new node to begin from if all nodes on one path have been visited and only lead back to the starting node
//Version: 1.1
//Debugged: YES! (v1.0->v1.1)
//Changelog:
		//Added counter incrementer in while loop
int Functions::getUnvisited(vector<class Node> &n)
{
	int c = 0; //Counter

	while (c < n.size()) //While the counter is less than the size of the vector, and the unvisited flag is not raised
	{
		if (!n[c].getVisited()) //If the node has not been visited yet
			return c; //return the position of the node that has not yet been visited

		c++; //Increase counter
	}

	return -1; //Return -1 to let program know all nodes have been visited
}

//checkDeadEnds Function
//Finds and marks all dead ends between nodes in a list n, marked on edges in a list e
//Version: 1.0
//Debugged: YES! (v1.0->v1.0)
//Changelog:
	//None, function was operating fine; needed to modify getEdge() function in Node.cpp (Offset to return correct edge and prevent vector out of range crash) (v1.0)
void Functions::searchDeadEnds(vector<class Node> &n, vector<class Edge> &e, int thisNode)
{
	if (n[thisNode].getVisited()) return; //If the node has been visited already, no need to come here, just go back, as the node won't be marked as visited until all edges are checked

	vector<int> edges; //Edges to look for
	bool isolated = n[thisNode].isIsolated(); //Isolated status of the node
	int edge; //Edge to push into the vector above
	int nodes[2]; //Array of 2 for each connected node

	n[thisNode].setVisited(true); //Sets the visited status of this node to true

	if (!isolated) //If the node is not isolated
	{
		for (int i = 0; i < e.size(); i++) //Assuming the node is connected to all other nodes, so search for as many edges as exist
		{
			edge = n[thisNode].getEdge(i); //Get an edge

			if (edge == -1) //If no more edges to get
				break; //Break out of loop
			else
				edges.push_back(edge); //Add edge to the list
		}

		if (edges.size() == 1) //If there is only one edge connecting to the node
		{
			n[thisNode].setDeadEndStatus(true); //This node is indeed a dead end, so mark it as such
			e[edges[0]].setDeadEndStatus(true); //The edge leading to this node leads to a dead end, so mark it as such
		}

		for (int i = 0; i < edges.size(); i++) //Check all edges
		{
			for (int j = 0; j < 2; j++) //Get connected nodes on this edge
			{
				e[edges[i]].getConnectedNodes(nodes); //Get connected nodes to this currennt edge
			}

			if (nodes[0] == n[thisNode].getID()) //If the first connected node's ID is == that of the node about to be jumped to
				searchDeadEnds(n, e, nodes[1] - 1); //Go to the opposing end, if the node is already visited it'll just come back here
			else
				searchDeadEnds(n, e, nodes[0] - 1); //Go to the node as normal, if the node is already visited it'll just come back here
		}
	}
	else //If the node is isolated
	{
		thisNode = getUnvisited(n); //Get the next unvisited node

		if (thisNode == -1) //If all nodes have been visited in the graph, we're done
			return;
		else
			searchDeadEnds(n, e, thisNode); //Move on to the next available node that potentially has edges
	}
}

//elimRedundancy function
//Finds all nodes with multiple edges, of which all forward edges lead to a dead end, leaving the only option to go back
//If all forward edges lead to a dead end, then unmark those edges as dead ends, and mark the previous edge as a dead end
//Version: 1.1
//Debugged: YES! (v1.0->v1.1)
//Changelog:
	//v1.1:
		//Changed int i counter to a decrement (sort of useful if you're starting at the back end of the vector and moving to the front)
		//Gave program a means of clearing backwardEdges vector at the start of each loop
void Functions::elimReduncancy(vector<class Node> &n, vector<class Edge> &e)
{
	vector<int> edges; //vector to store the edges connected to a given node
	int edge; //Edge to push into vector
	int connectedNodes[2]; //Connected node list
	vector<int> consideredNode; //Node to consider
	bool allDeadEnds = true; //Flag for if all nodes are dead ends
	vector<int> backwardEdges; //List of backward edges

							   //Reset visited status
	for (int i = 0; i < n.size(); i++)
	{
		n[i].setVisited(false); //Reset the visited status of the node
	}

	for (int i = n.size() - 1; i >= 0; i--) //Check the entire graph, starting from the top down
	{
		//Reset backwards edges
		backwardEdges.clear();

		n[i].setVisited(true); //Set visited status on this node to true

		for (int j = 0; i < e.size(); j++) //Check for all possible edges connected to this node
		{
			edge = n[i].getEdge(j); //Get an edge

			if (edge == -1) //If no more edges
				break; //Break out of loop
			else
				edges.push_back(edge); //Place edge into list
		}

		//Eliminate all backward edges
		for (int j = 0; j < edges.size(); j++)
		{
			e[edges[j]].getConnectedNodes(connectedNodes); //Get the connected nodes for this edge

			if (!n[connectedNodes[0] - 1].getVisited() || !n[connectedNodes[1] - 1].getVisited()) //If either of the considerable nodes on the given edge has not been visited yet, implying that the node leads to the root
			{
				backwardEdges.push_back(edges[j]); //Add the backward edge to the list of backward edges
				edges.erase(edges.begin() + j); //Remove that edge from the list
			}
		}

		if (edges.size() > 1) //If there are multiple connecting edges left after getting rid of backward edges
		{
			for (int j = 0; j < edges.size(); j++) //Get a list of all connected nodes to determine if any are not a dead end
			{
				e[edges[j]].getConnectedNodes(connectedNodes); //Get the connected nodes of this edge

				if (n[i].getID() == connectedNodes[0]) //If the first of two considerable nodes is the same as the node being sat on
					consideredNode.push_back(connectedNodes[1]); //Consider the other node
				else
					consideredNode.push_back(connectedNodes[0]); //Consider the first node
			}

			for (int j = 0; j < edges.size(); j++) //Look at all considerable nodes
			{
				if (!n[consideredNode[j] - 1].getDeadEndStatus()) //If the node being looked at is not a dead end
				{
					allDeadEnds = false; //lower flag, as we can't mark this node as 
					break; //Break out of loop
				}
			}

			if (allDeadEnds && backwardEdges.size() == 1) //If all edges lead to a dead end, and there is ONLY ONE backward edge
			{
				e[backwardEdges[0]].setDeadEndStatus(true); //Set the dead end status of that edge to true

				for (int j = 0; j < edges.size(); j++) //Mark all other forward edges that were considered as non-dead end, as it's now redundant
				{
					e[edges[j]].setDeadEndStatus(false);
				}
			}
		}
	}
}