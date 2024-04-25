using namespace std;

struct queueData {
	int queueCount = 0;
	int totalIdleTime = 0;
	int totalOverTime = 0;
	int maxQueueLength = 0;
	int currItems = 0;
	int totalItems = 0;
};

struct queueNodeData {
	int timeAvailable;
	int itemCount;
};

struct queueNode {
	queueNodeData data;
	queueNode* nextPtr;
};

class Queue {
public:
	Queue();
	void enQueue(queueNodeData);
	queueNodeData deQueue();
	queueNodeData peek();
	bool queueEmpty();
	void printQueue();
private:
	queueNode* front;
	queueNode* rear;
};