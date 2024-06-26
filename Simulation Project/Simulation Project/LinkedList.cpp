#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList() {
	headPtr = nullptr;
}

void LinkedList::addElement(listType newCustomer) {
	Node* tempPtr = new Node;
	tempPtr->data = newCustomer;
	tempPtr->nextPtr = nullptr;

	if (listIsEmpty()) {
		headPtr = tempPtr;
	}

	//organizes data based on qtimes
	else if (tempPtr->data.enterQTime < headPtr->data.enterQTime) {
		tempPtr->nextPtr = headPtr;
		headPtr = tempPtr;
	}
	else {
		Node* holdPtr = headPtr;

		//makes sure to organize based on qtimes
		while (holdPtr != nullptr 
				&& holdPtr->nextPtr != nullptr
				&& holdPtr->nextPtr->data.enterQTime < tempPtr->data.enterQTime) {
			holdPtr = holdPtr->nextPtr;
		}
		if (holdPtr != nullptr) {
			tempPtr->nextPtr = holdPtr->nextPtr;
			holdPtr->nextPtr = tempPtr;
		}
	}
	listCount++;
}

void LinkedList::delElement() {
	Node* tempPtr = headPtr;
	if (!listIsEmpty()) {
		headPtr = headPtr->nextPtr;
		delete tempPtr;
		tempPtr = nullptr;

		//this is where static list count decrements
		--listCount;
	}
}

listType LinkedList::peek() {
	listType tempData;
	if (!listIsEmpty()) {
		tempData = headPtr->data;
	}

	return tempData;
}


bool LinkedList::listIsEmpty() {
	return headPtr == nullptr;
}

void LinkedList::printList() {
	Node* tempPtr = headPtr;
	while (tempPtr != nullptr) {
		cout << tempPtr->data.cartId << " "
			 << tempPtr->data.enterQTime << " "
			 << tempPtr->data.itemCount << endl;
		tempPtr = tempPtr->nextPtr;
	}
}
