#pragma once
class Customer {
public:
	Customer();
	Customer(int i);
	int getItems();
	void setItems(int i);
	double getTimeSpent();
	void setTimeSpent(double t);
private:
	int id;
	int items;
	double minutes;
};
