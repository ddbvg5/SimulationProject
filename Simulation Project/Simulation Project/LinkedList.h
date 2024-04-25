using namespace std;

struct listType {
	int cartId;
	int itemCount;
	int enterQTime;
};

struct Node {
	listType data;
	Node* nextPtr;
};

class LinkedList {
public:
	LinkedList();
	void addElement(listType);
	listType peek();
	void delElement();
	void printList();
	bool listIsEmpty();
	static int listCount;
private:
	Node* headPtr;
};