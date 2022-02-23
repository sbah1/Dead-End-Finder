/*
Sulaiman Bah
CIS 3501
Fall 2020
Prof. John Baugh
*/

//Functions.h
//Description: Header file for function implementation.
//Version 1.0

#pragma once

#include <vector> //Needed for vector implementation
#include "Node.h" //Needed for node class
#include "Edge.h" //Needed for edge class

class Functions
{
public:
	void readIn(vector<class Node> &, vector<class Edge> &);
	int getUnvisited(vector<class Node> &);
	void searchDeadEnds(vector<class Node> &, vector<class Edge> &, int);
	void elimReduncancy(vector<class Node> &n, vector<class Edge> &);
};