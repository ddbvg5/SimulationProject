#pragma once
class Customer {
public:
	Customer();
	int getItems();
	void setItems(int i);
	double getTimeSpent();
	void setTimeSpent(double t);
private:
	int items;
	double minutes;
};