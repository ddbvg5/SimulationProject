#include "Customer.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Customer::Customer() {
	id = 0;
	items = 0;
	minutes = 0;

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
	
}

Customer::Customer(int i) {
	id = i;
	items = 0;
	minutes = 0;

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
}

int Customer::getItems() {
	return items;
}

double Customer::getTimeSpent() {
	return minutes;
}

void Customer::setItems(int i) {
	items = i;
}

void Customer::setTimeSpent(double t) {
	minutes = t;
}