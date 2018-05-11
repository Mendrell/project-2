#pragma once

// CSCI 115 - Spring 2018

using namespace std;
#include <iostream>
#include<vector>

#define INT_MAX 10e6

class MyGraph // Simple class to do basic functions, it is based on the adjacency graph
{
public:
	MyGraph();
	MyGraph(int n1);
	~MyGraph();

	// Warning: we consider the vertices between 1 and n
	// so in the code we decrement by 1 to be in 0..n-1 for the arrays
	void DeleteAllEdges();
	void DeleteEdge(int i,int j);
	void SetEdge(int i, int j, int w);
	void SetEdge(char a, char b, int w);
	void PrintEdges();

	bool BFS(int s1, int** E1);
	void MSTKruskal();

	int minKey(int* key, bool* mstSet);
	void printMST(int* parent);
	void MSTPrim();

	int* V; // information related to the vertices (it can represent the colors)
	// 0=white
	// 1=gray
	// 2=black
	int** E; // information related to the edges: Adjacency matrix
	int* pi; // used to get the predecessors
	int* distance; // used to get the distance from s

	int n; // number of vertices
	int s; // current source

};

