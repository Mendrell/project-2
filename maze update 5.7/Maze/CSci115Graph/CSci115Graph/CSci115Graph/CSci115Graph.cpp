// CSCI 115 - Spring 2018
#include "stdafx.h"
#include "MyGraph.h"

using namespace std;
#include <iostream>

int main()
{
	// Creation of a Graph
	int n = 9;
	MyGraph* G = new MyGraph(n);

	// Set the edges for the graph (same graph as the example in the class and in the book Intro to algorithms)
	// slides 13 in the pdf csci15_minspanningtree.pdf
	G->SetEdge(1, 2, 4); // a->b = 4
	G->SetEdge(1, 8, 8); // a->h = 8
	G->SetEdge(2, 8, 11); // b->h = 11
	G->SetEdge(2, 3, 8); // b->c = 8
	G->SetEdge(8, 9, 7); // h->i = 7
	G->SetEdge(3, 9, 2); // c->i = 2
	G->SetEdge(7, 9, 6); // g->i = 6 
	G->SetEdge(3, 4, 7); // c->d = 7
	G->SetEdge(3, 6, 4); // c->f = 4
	G->SetEdge(4, 6, 14); // d->f = 14
	G->SetEdge(4, 5, 9); // d->e = 9
	G->SetEdge(5, 6, 10); // e->f = 10
	G->SetEdge(7, 8, 1); // g->h = 1
	G->SetEdge(6, 7, 2); // f->g = 2

	// Breadth Frist Search
	G->BFS(1,G->E);

	for (int i = 0; i < n; i++) {
		char c = char(97 + i);
		char p= char(97 + G->pi[i]);
		cout << "Color of " << c << "=" << G->V[i] << " Distance=" << G->distance[i] << " Predecssor=" << G->pi[i] << endl;
	}
	cout << endl;

	G->MSTKruskal();
	G->MSTPrim();

    return 0;
}

