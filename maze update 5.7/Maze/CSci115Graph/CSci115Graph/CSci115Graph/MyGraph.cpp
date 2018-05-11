#include "stdafx.h"
#include "MyGraph.h"
#include "MyQueue.h"

// CSCI 115 - Spring 2018

using namespace std;
#include <iostream>
#include <tuple>

MyGraph::MyGraph()
{
	n = 0;
	E = NULL;
	V = NULL;
	distance = NULL;
	pi = NULL;
}

MyGraph::MyGraph(int n1)
{
	n = n1;
	V = new int[n]; // color
	distance = new int[n];
	pi = new int[n];
	E = new int*[n];
	for (int i = 0; i < n; i++) {
		E[i] = new int[n];
		for (int j = 0; j < n; j++)
			E[i][j] = 0;
	}
}

MyGraph::~MyGraph()
{
	for (int i = 0; i < n; i++) 
		delete [] E;
	delete[] E;
	delete[] V;
	delete[] pi;
	delete[] distance;
}

void MyGraph::DeleteAllEdges() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			E[i][j] = 0;
}
void MyGraph::DeleteEdge(int i, int j) {
	if ((i > 0) && (i <= n) && (j > 0) && (j <= n)) {
		E[i - 1][j - 1] = 0;
		E[j - 1][i - 1] = 0;
	}
	else
		cout << "Wrong Edge (" << i << "," << j << ")" << endl;
}

void MyGraph::SetEdge(int i, int j, int w) {
	if ((i > 0) && (i <= n) && (j > 0) && (j <= n)) {
		E[i - 1][j - 1] = w;
		E[j - 1][i - 1] = w;
	}
	else
		cout << "Wrong Edge (" << i << "," << j << ")" << endl;
}

void MyGraph::SetEdge(char a, char b, int w) {
	int i = int(a) - 96;
	int j = int(b) - 96;
	if ((i > 0) && (i <= n) && (j > 0) && (j <= n)) {
		E[i - 1][j - 1] = w;
		E[j - 1][i - 1] = w;
	}
	else
		cout << "Wrong Edge (" << i << "," << j << ")" << endl;
}

void PrintMatrix(int** X,int n) {
	// Display Adjacency matrix
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << X[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void MyGraph::PrintEdges() {
	PrintMatrix(E,n);
}

bool MyGraph::BFS(int s1,int** E1) {
	bool acyclic = true;
	if (!((s1 > 0) && (s1 <= n)))
		cout << "Bad source !";
	else {
		s = s1;
		MyQueue* Q = new MyQueue(n);
		// initialization
		for (int i = 0; i < n; i++) {
			V[i] = 0;
			distance[i] = 0;
			pi[i] = 0;
		}
		// init s
		V[s - 1] = 1;
		distance[s - 1] = 0;
		pi[s - 1] = -1;
		Q->Enqueue(s-1);
		while (!Q->isEmpty()) {
			int u=Q->Dequeue();
			for (int v = 0; v < n; v++) {
				if (E1[u][v] > 0) { // adjancent to u
					if (V[v] == 0) { // white (not visited before)
						V[v] = 1;
						distance[v] = distance[u] + 1;
						pi[v] = u;
						Q->Enqueue(v);
					}
					else
						acyclic = false; // not white --> already visited through some edge
				}
				V[u] = 2; // black
			}
		}
		delete Q;
	}
	return acyclic;
}

tuple<int,int,int> GetMin(int** M,int n)
{
	int minvalue = INT_MAX;
	int argi = 0;
	int argj = 0;
	for (int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			if ((M[i][j] < minvalue) && (M[i][j] > 0)) {
				minvalue = M[i][j];
				argi = i;
				argj = j;
			}
		}
	M[argi][argj]=0; // set the min to 0
	return make_tuple(minvalue,argi,argj);
}

void MyGraph::MSTKruskal()
{
	// Remark: it is better to use ajacency lists to sort the edges
	// the proposed implementation is not efficient but it fits with the description of the class

	int** A = new int*[n]; // matrix that contains the edges we will keep
	for (int i = 0; i < n; i++) {
		A[i] = new int[n];
		for (int j = 0; j < n; j++)
			A[i][j] = 0;
	}

	// copy the edges in S
	int** S = new int*[n];
	for (int i = 0; i < n; i++) {
		S[i] = new int[n];
		for (int j = 0; j < n; j++)
			S[i][j] = 0;
	}
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			S[i][j] = E[i][j];

	int total = 0; // number of edges
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (S[i][j] != 0)
				total++;

	int edgecount = 0;
	int* edgew = new int[total]; // the sequence of weights from edges that are added in the MST
	for (int i = 0; i < total; i++)
		edgew[i] = 0;

	int argi, argj, v;
	tie(v, argi, argj) = GetMin(S,n);
	A[argi][argj]=1;

	edgew[0] = v;
	edgecount++;

	for (int i=0;i<total;i++) { // for each edge
		tie(v,argi,argj)=GetMin(S,n); // Not efficient but it works, given the current class
		// check if argi argj can lead to a cycle
		A[argi][argj]=1;
		if (!BFS(argi+1,A)) // Not efficient but it works, given the current class, pick one vertex from the potential edge to check if it leads to a cycle
			A[argi][argj]=0;
		else
		{
			edgew[edgecount] = v;
			edgecount++;
		}
	}

	for (int i = 0; i < total; i++)
		cout << edgew[i] << " ";
	cout << endl;

	delete[] edgew;
	PrintMatrix(A, n);

	for (int i = 0; i < n; i++) {
		delete[] A[i];
		delete[] S[i];
	}
	delete[] A;
	delete[] S;
}

int MyGraph::minKey(int* key,bool* mstSet) {
	// Initialize min value
	int min = INT_MAX;
	int min_index= INT_MAX;
	for (int v=0;v<n;v++)
		if ((mstSet[v] == false) && (key[v] < min)) {
			min=key[v];
			min_index=v;
		}
	return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void MyGraph::printMST(int* parent)
{
	cout << "Edge Weight" << endl;
	for (int i=1;i<n;i++)
		cout << parent[i] << " " << i << " " << E[i][parent[i]] << endl;
}

void	MyGraph::MSTPrim() {
	int* parent = new int[n];		// Array to store constructed MST
	int* key = new int[n];		// Key values used to pick minimum weight edge in cut
	bool* mstSet = new bool[n];   // To represent set of vertices not yet included in MST

	for (int i = 0; i < n; i++) {
		key[i] = INT_MAX; // infinite value
		mstSet[i] = false;
	}
	// Include first 1st vertex in MST
	key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // 1st node is root of MST 
	for (int i=0;i<n-1;i++) {
		int u = minKey(key, mstSet);
		mstSet[u] = true; 
	    //Consider only those vertices which are not yet included in MST
		for (int v = 0; v < n; v++)
			if ((E[u][v]!=0) && (mstSet[v]==false) && (E[u][v]<key[v])) {
				parent[v]=u;
				key[v]=E[u][v];
			}
	}
	printMST(parent);
	delete[] parent;
	delete[] key;
	delete[] mstSet;
}