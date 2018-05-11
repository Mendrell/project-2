#pragma once

#define INT_MIN -10e6

// CSCI 115 - Spring 2018
// A simple circular queue

class MyQueue
{
public:
	MyQueue();
	MyQueue(int capacity1);
	~MyQueue();

	bool isFull();
	bool isEmpty();
	void Enqueue(int item);
	int Dequeue();
	int Front();
	int Rear();
	void Display();

	int front, rear, size;
	int capacity;
	int* a;
};





