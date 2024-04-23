#include <iostream>
#include <cstdlib>
#include "Customer.h"

using namespace std;

int main() {
	int customersEntered;
	srand(time(NULL));

	for (int i = 0; i < 720; i++) {
		customersEntered = rand() % 3 + 1;
		switch (customersEntered) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			cout << "how ??????" << endl;
			break;
		}
	}

	return 0;
}