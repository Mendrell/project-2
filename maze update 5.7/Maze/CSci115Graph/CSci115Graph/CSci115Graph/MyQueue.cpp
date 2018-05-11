#include "stdafx.h"
#include "MyQueue.h"

// CSCI 115 - Spring 2018

using namespace std;
#include <iostream>

MyQueue::MyQueue() {
	capacity = 0;
	front=size=0;
	rear=capacity-1;
	a=NULL;
}

MyQueue::~MyQueue() {
	delete[] a;
}

// Create a queue of given capacity, initializes size of queue as 0
MyQueue::MyQueue(int capacity1) {
	capacity=capacity1;
	front=size=0;
	rear=capacity-1;  // This is important, see the enqueue
	a=new int[capacity];
}

// Queue is full when size gets equal to the capacity 
bool MyQueue::isFull() {
	return (size==capacity);
}

// Queue is empty when size is 0
bool MyQueue::isEmpty() {
	return (size==0);
}

// Add an item to the queue, change rear and size
void MyQueue::Enqueue(int item) {
	if (isFull())
		return;
	rear=(rear+1)%capacity;
	a[rear]=item;
	size=size+1;
}

// Remove an item from queue, it changes front and size
int MyQueue::Dequeue() {
	if (isEmpty())
		return INT_MIN;
	int item = a[front];
	front=(front+1)%capacity;
	size=size-1;
	return item;
}

// Get front of queue
int MyQueue::Front() {
	if (isEmpty())
		return INT_MIN;
	return a[front];
}

// Get rear of queue
int MyQueue::Rear() {
	if (isEmpty())
		return INT_MIN;
	return a[rear];
}

void MyQueue::Display() { 
	for (int i = 0; i < capacity; i++)
		cout << a[i] << " " << endl;
		cout << endl;

}
