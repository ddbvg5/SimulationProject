#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue() {
	front = nullptr;
	rear = nullptr;
}

void Queue::enQueue(queueNodeData d) {
	queueNode* newNode = new queueNode;
	newNode->data = d;
	newNode->nextPtr = nullptr;

	if (queueEmpty()) {
		front = newNode;
		rear = newNode;
	}
	else {
		rear->nextPtr = newNode;
		rear = newNode;
	}
}

queueNodeData Queue::deQueue() {
	queueNodeData tempData;

	if (!queueEmpty()) {
		queueNode* tempNode = front;
		tempData = front->data;
		front = front->nextPtr;

		if (queueEmpty()) {
			rear = nullptr;
		}

		delete tempNode;
		tempNode = nullptr;
	}
	return tempData;
}

queueNodeData Queue::peek() {
	queueNodeData tempData;
	if (!queueEmpty()) {
		tempData = front->data;
	}
	return tempData;
}

bool Queue::queueEmpty() {
	return front == nullptr;
}

void Queue::printQueue() {
	queueNode* tempNode = front;
	while (tempNode != nullptr) {
		cout << tempNode->data.itemCount << " " << tempNode->data.timeAvailable << endl;
		tempNode = tempNode->nextPtr;
	}
}