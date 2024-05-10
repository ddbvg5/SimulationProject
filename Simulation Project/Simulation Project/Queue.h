struct queueData {
	int queueCount = 0;		//current queue length (set to 0 initially)
	int totalIdleTime = 0;  // if queueCount == 0; this is incremented
	int totalOverTime = 0;  //increment if current time > 720 & there are people in line
	int maxQueueLength = 0; //if current queueCount>maxQueueLength, reset
	int currItems = 0;		//update as customers are added/removed from queue
	int totalItems = 0;		//running count of items purchased
};

struct queueNodeData {
	int timeAvailable;		// clock time when current customer is dequeued
	int itemCount;			//the number of items for current customer
};

struct queueNode {
	queueNodeData data;
	queueNode* nextPtr;
};

class Queue {
public:
	Queue();
	void enQueue(queueNodeData); //add the queueNodeData item to the end of the queue
	queueNodeData deQueue();	 //remove a queueNodeData item from the front of the queue
	queueNodeData peek();		 //return the contents of the front of the queue (but do not remove)
	bool queueEmpty();			 //return true if the queue is empty (front = nullptr?), false otherwise
	void printQueue();
	int accrue(int checkingOut); // returns total increment adjustment
	int queueLength();			 // returns total queue length
private:
	queueNode* front;
	queueNode* rear;
};