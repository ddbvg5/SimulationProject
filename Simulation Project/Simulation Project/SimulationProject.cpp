#include <iostream>
#include <cstdlib>
#include <vector>
#include "LinkedList.h"
#include "Queue.h"
#include <cmath>

using namespace std;

//initiate counters
static int customerID = 1;
int LinkedList::listCount = 0;

int main() {

	//vars
	int minimum = 1000, checkoutLines = 0, newTime = 720, selector = 0, increment = 0, iterator = 0;
	int customersEntered, items;
	float minutes = 0;
	double checkOutTime = 0;
	LinkedList inStore;
	vector<Queue> queues;
	vector<queueData> data;
	queueNodeData checkingOut;

	//random initiation
	srand(time(NULL));

	//verifies correct input
	while (checkoutLines < 1 || checkoutLines > 11) {
		cout << "Enter the amount of checkout lines" << endl;
		cin >> checkoutLines;
	}

	//adds queues and queue data based on input
	for (int i = 0; i < checkoutLines; i++) {
		Queue newQueue;
		queueData newData;

		queues.push_back(newQueue);
		data.push_back(newData);
	}

	//time span of 720 minutes from store open to close
	for (int totalTime = 0; totalTime < 720; totalTime++) {

		//customer initialization
		customersEntered = rand() % 3 + 1;

		//item initialization
		for (int i = 0; i < customersEntered; i++) {
			int percentile = rand() % 101;

			if (percentile <= 40) {
				items = rand() % 11 + 1;
			}
			else if (percentile <= 70) {
				items = rand() % 21 + 11;
			}
			else if (percentile <= 90) {
				items = rand() % 31 + 21;
			}
			else if (percentile <= 100) {
				items = rand() % 61 + 31;
			}

			//how long they are shopping for
			for (int i = 0; i < items; i++) {
				minutes += (static_cast<float>(rand() % 60 + 30) / 60);
			}

			listType newCustomer = { customerID, items, static_cast<int>(minutes + totalTime) };
			customerID++;
			inStore.addElement(newCustomer);

			minutes = 0;
		}

		//empties checkouts based on time
		for (int totalQueues = 0; totalQueues < queues.size(); totalQueues++) {
			while (!queues.at(totalQueues).queueEmpty() && queues.at(totalQueues).peek().timeAvailable == totalTime) {
				
				//adjust max queue length based on max length
				if (data.at(totalQueues).maxQueueLength < queues.at(totalQueues).queueLength()) {
					data.at(totalQueues).maxQueueLength = queues.at(totalQueues).queueLength();
				}

				//adjusts parameters
				data.at(totalQueues).currItems -= queues.at(totalQueues).peek().itemCount;
				queues.at(totalQueues).deQueue();
			}

			//adjusts parameters
			if (queues.at(totalQueues).queueEmpty()) {
				data.at(totalQueues).totalIdleTime++;
			}
		}

		//when customer is done shopping
		while (inStore.peek().enterQTime == totalTime) {
			//how long to checkout
			for (int j = 0; j < inStore.peek().itemCount; j++) {
				checkOutTime += .15;
			}
			
			//creates check out customer
			checkingOut = { (static_cast<int>(ceil(checkOutTime)) + inStore.peek().enterQTime), inStore.peek().itemCount };

			//resets minimum for queue optimization
			minimum = 100000;

			//goes through all queues
			for (int i = 0; i < checkoutLines; i++) {
				
				//pushes if empty
				if (queues.at(i).queueEmpty()) {
					selector = i;
					break;
				}

				//optimizes queues
				else if (data.at(i).currItems < minimum) {
					selector = i;
					minimum = data.at(i).currItems;
				}
			}

			//checks if queue isn't empty and adjusts times to allow customer to wait for prior customer
			if (!queues.at(selector).queueEmpty()) {
				increment = queues.at(selector).accrue(checkingOut.timeAvailable);
				checkingOut.timeAvailable = increment;
			}

			//checkout
			queues.at(selector).enQueue(checkingOut);

			//parameters adjusted
			data.at(selector).queueCount++;
			data.at(selector).currItems += inStore.peek().itemCount;
			data.at(selector).totalItems += inStore.peek().itemCount;
			inStore.delElement();

			selector = 0;
			checkOutTime = 0;
			increment = 0;
		}
	}

	//statement gets to the very last customer in store
	do {
		//when customer is done shopping after store close
		while (inStore.peek().enterQTime == newTime) {
			//how long to checkout
			for (int j = 0; j < inStore.peek().itemCount; j++) {
				checkOutTime += .15;
			}
			//creates check out customer
			checkingOut = { (static_cast<int>(ceil(checkOutTime)) + inStore.peek().enterQTime), inStore.peek().itemCount };

			//resets minimum for queue optimization
			minimum = 100000;

			//goes through all queues
			for (int i = 0; i < checkoutLines; i++) {

				//pushes if empty
				if (queues.at(i).queueEmpty()) {
					selector = i;
					break;
				}

				//optimizes
				else if (data.at(i).currItems < minimum) {
					selector = i;
					minimum = data.at(i).currItems;
				}
			}

			//increments idle times
			for (int i = 0; i < checkoutLines; i++) {
				if (queues.at(i).queueEmpty()) {
					data.at(i).totalIdleTime++;
				}
			}

			//checks if queue is empty and adjusts time for customer to checkout
			if (!queues.at(selector).queueEmpty()) {
				increment = queues.at(selector).accrue(checkingOut.timeAvailable);
				checkingOut.timeAvailable = increment;
			}

			//goes to checkout
			queues.at(selector).enQueue(checkingOut);


			//adjust parameters
			data.at(selector).queueCount++;
			data.at(selector).currItems += inStore.peek().itemCount;
			data.at(selector).totalItems += inStore.peek().itemCount;
			inStore.delElement();
			selector = 0;
			checkOutTime = 0;
			increment = 0;
		}

		//checks out customer based on time
		for (int totalQueues = 0; totalQueues < queues.size(); totalQueues++) {

			//checks if queue isn't empty and time matches
			while (!queues.at(totalQueues).queueEmpty() && queues.at(totalQueues).peek().timeAvailable == newTime) {
				//adjusts max length parameter
				if (data.at(totalQueues).maxQueueLength < queues.at(totalQueues).queueLength()) {
					data.at(totalQueues).maxQueueLength = queues.at(totalQueues).queueLength();
				}

				//dequeues and adjusts parameters
				data.at(totalQueues).currItems -= queues.at(totalQueues).peek().itemCount;
				queues.at(totalQueues).deQueue();
				data.at(totalQueues).totalOverTime++;
			}

			//increments idle time
			if (queues.at(totalQueues).queueEmpty()) {
				data.at(totalQueues).totalIdleTime++;
			}
		}
		//increments time
		newTime++;
	} while (inStore.listCount != 1);

	//these statement cover the last customer in store prior to checkout
	while (inStore.peek().enterQTime >= newTime) {
		for (int j = 0; j < inStore.peek().itemCount; j++) {
			checkOutTime += .15;
		}
		checkingOut = { (static_cast<int>(ceil(checkOutTime)) + inStore.peek().enterQTime), inStore.peek().itemCount };
		minimum = 100000;

		for (int i = 0; i < checkoutLines; i++) {
			if (queues.at(i).queueEmpty()) {
				selector = i;
				break;
			}
			else if (data.at(i).currItems < minimum) {
				selector = i;
				minimum = data.at(i).currItems;
			}
		}
		for (int i = 0; i < checkoutLines; i++) {
			if (queues.at(i).queueEmpty()) {
				data.at(i).totalIdleTime++;
			}
		}
		if (!queues.at(selector).queueEmpty()) {
			increment = queues.at(selector).accrue(checkingOut.timeAvailable);
			checkingOut.timeAvailable = increment;
		}
		queues.at(selector).enQueue(checkingOut);

		data.at(selector).queueCount++;
		data.at(selector).currItems += inStore.peek().itemCount;
		data.at(selector).totalItems += inStore.peek().itemCount;
		inStore.delElement();
		selector = 0;
		checkOutTime = 0;
		increment = 0;

		for (int totalQueues = 0; totalQueues < queues.size(); totalQueues++) {
			while (!queues.at(totalQueues).queueEmpty() && queues.at(totalQueues).peek().timeAvailable == newTime) {
				data.at(totalQueues).currItems -= queues.at(totalQueues).peek().itemCount;
				queues.at(totalQueues).deQueue();
				data.at(totalQueues).totalOverTime++;
			}
			if (queues.at(totalQueues).queueEmpty()) {
				data.at(totalQueues).totalIdleTime++;
			}
		}

		newTime++;
	}
	
	//these statements checkout remaining customers
	while (iterator != queues.size()) {

		//iterator used to check if all queues are empty
		iterator = 0;
		for (int i = 0; i < queues.size(); i++) {
			while (!queues.at(i).queueEmpty() && queues.at(i).peek().timeAvailable == newTime) {
				data.at(i).currItems -= queues.at(i).peek().itemCount;
				queues.at(i).deQueue();
				data.at(i).totalOverTime++;
			}
			if (queues.at(i).queueEmpty()) {
				data.at(i).totalIdleTime++;
				iterator++;
			}
		}
		newTime++;
	}

	//output
	for (int i = 0; i < checkoutLines; i++) {
		cout << "CHECKOUT LINE:\t\t" << i << endl;
		cout << "\tTotal Customers Helped:\t" << data.at(i).queueCount << endl;
		cout << "\tTotal Number of Items:\t" << data.at(i).totalItems << endl;
		cout << "\tMax Line Length:\t" << data.at(i).maxQueueLength << endl;
		cout << "\tTotal Idle Time:\t" << data.at(i).totalIdleTime << endl;
		cout << "\tTotal Over Time:\t" << data.at(i).totalOverTime << endl;
	}

	return 0;
}