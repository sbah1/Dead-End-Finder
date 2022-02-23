/*
Sulaiman Bah
CIS 3501
Fall 2020
Prof. John Baugh
*/

//Main.cpp
//Description: Main driver file.
//Version 1.1

#include <iostream> //Needed to output to screen
#include "Functions.h" //Functions implementation

using namespace std; //Namespace definition

//Define all functions
class Functions operate; //Function operations definition

//Main driver
//Runs the entire program by calling all necessary functions
//Version: 1.3
//Debugged: YES! (v1.0->v1.1->v1.2)
//Changelog:
	//v1.1:
		//Made driver check if any nodes were not yet visited
	//v1.2:
		//Made program stop checking the wrong list when looking for order in which to print dead ends (should have been !nodeList when it was actually set to !edgeList)
	//v1.3:
		//Made program remove redundant dead ends
	//v1.3.1:
		//Made driver compatible with functions defined in separate file
int main()
{
	vector<class Node> nodeList; //Node list
	vector<class Edge> edgeList; //Edge list
	int connectedNodes[2]; //Array of connected nodes to a given edge
	bool checkedAll = false; //Bool to report if the entire graph has been checked
	int nextNode; //Next node to read
	int totalSigns = 0; //Total number of dead end signs

	//Get nodes and edges, and create the graph
	operate.readIn(nodeList, edgeList);

	//Get the dead ends in the graph, starting from the root node
	operate.searchDeadEnds(nodeList, edgeList, 0);

	//Check for unvisited nodes
	while (!checkedAll) //While the entire graph hasn't been looked at
	{
		nextNode = operate.getUnvisited(nodeList); //Read the graph for unchecked nodes

		if (nextNode == -1) //If entire graph is checked
			checkedAll = true; //Raise flag, break loop
		else //If not
			operate.searchDeadEnds(nodeList, edgeList, nextNode);
	}

	//Remove redundant dead ends
	operate.elimReduncancy(nodeList, edgeList);

	for (int i = 0; i < edgeList.size(); i++) //Get number of dead end signs
	{
		if (edgeList[i].getDeadEndStatus()) //If the edge is a dead end
			totalSigns++; //Increment the number of dead end signs
	}

	cout << "Total number of dead end signs installed: " << totalSigns << endl;

	for (int i = 0; i < edgeList.size(); i++) //Read out the dead ends in the graph
	{
		if (edgeList[i].getDeadEndStatus()) //If the edge is marked as leading to a dead end
		{
			edgeList[i].getConnectedNodes(connectedNodes); //Get the connected nodes for this edge

			if (!nodeList[connectedNodes[0] - 1].getDeadEndStatus()) //If the dead end status of this node is false
				cout << "Dead end at node " << connectedNodes[1] << " coming from node " << connectedNodes[0] << endl;
			else if (!nodeList[connectedNodes[1] - 1].getDeadEndStatus()) //If the dead end status of the opposing node is false
				cout << "Dead end at node " << connectedNodes[0] << " coming from node " << connectedNodes[1] << endl;
			else //If both nodes have a dead end status
				cout << "Dead end going both ways between nodes " << connectedNodes[0] << " and " << connectedNodes[1] << endl;
		}
	}

	//exit program
	system("pause");
	return 0;
}