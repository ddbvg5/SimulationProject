#include <iostream>
#include <cstdlib>
#include "Customer.h"
#include <vector>
#include "LinkedList.h"
#include "Queue.h"

using namespace std;

static int customerID = 1;
int LinkedList::listCount = 0;

int main() {
	int checkoutLines = 0;
	//vector<Customer> customers;
	int customersEntered, items;
	float minutes = 0;
	LinkedList inStore;
	vector<Queue> queues;
	
	//(time(NULL));

	while (checkoutLines < 1 || checkoutLines > 11) {
		cout << "Enter the amount of checkout lines" << endl;
		cin >> checkoutLines;
	}
	for (int i = 0; i < checkoutLines; i++) {
		Queue newQueue;
		queues.push_back(newQueue);
	}

	for (int time = 0; time < 720; time++) {
		customersEntered = rand() % 3 + 1;

		for (int i = 0; i < customersEntered; i++) {
			int percentile = rand() % 100 + 1;

			if (percentile <= 10) {
				items = rand() % 11 + 1;
			}
			else if (percentile <= 30) {
				items = rand() % 21 + 11;
			}
			else if (percentile <= 60) {
				items = rand() % 31 + 21;
			}
			else if (percentile <= 100) {
				items = rand() % 61 + 31;
			}

			for (int i = 0; i < items; i++) {
				minutes += (static_cast<float>(rand() % 60 + 30) / 60);
			}

			listType newCustomer = { customerID, items, static_cast<int>(minutes + time) };
			inStore.addElement(newCustomer);
		}

		for (int customersShopping = 0; customersShopping <= inStore.listCount; customersShopping++) {
			if (inStore.peek().enterQTime == time) {
				for (int i = 0; i < checkoutLines; i++) {
					queueNodeData checkingOut = { inStore.peek().enterQTime + time, inStore.peek().itemCount };
					if (queues.at(i).queueEmpty()) {
						queues.at(i).enQueue(checkingOut);
						break;
					}
					else if (queues.at(i).)
				}
				inStore.delElement();
			}
		}
		
	}

	for (int i = 0; i < checkoutLines; i++) {
		cout << "CHECKOUT LINE:\t\t" << i << endl;
		cout << "\tTotal Customers Helped:\t" << endl;
		cout << "\tTotal Number of Items:\t" << endl;
		cout << "\tMax Line Length:\t\t\t\t" << endl;
		cout << "\tTotal Idle Time:\t\t\t\t" << endl;
		cout << "\tTotal Over Time:\t\t\t\t" << endl;
	}

	return 0;
}