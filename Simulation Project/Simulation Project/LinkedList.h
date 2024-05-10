struct listType {
	int cartId;		//unique id assigned for each cart
	int itemCount;  //amount of items the customer will get (randomly generated)
	int enterQTime; //current ‘time’ + shopping time
};

struct Node {
	listType data;
	Node* nextPtr;
};

class LinkedList {
public:
	LinkedList();
	void addElement(listType);	//add cart information to the list (list should probably be ordered)
	listType peek();			//return the contents of the front of the list (but do not remove)
	void delElement();			//remove a node item from the front of the list
	void printList();
	bool listIsEmpty();			//return true if the list is empty (headPtr = nullptr?), false otherwise
	static int listCount;		//number of carts currently in the list
private:
	Node* headPtr;
};