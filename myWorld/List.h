#include <iostream>
using namespace std;

// NodeBase.
template<typename T, class N>
class NodeBase
{
public:
	N* next;
public:
	NodeBase() { next = nullptr; };
	NodeBase(N* nextNode) { next = nextNode; };
	virtual ~NodeBase() {
		if (next) delete next;		// aberration.
	};
	void linkNext(N*);
	N* excludeNext();
};

template<typename T, class N>
void NodeBase<T, N>::linkNext(N* nextNode)
{
	next = nextNode;
}

template<typename T, class N>
N* NodeBase<T, N>::excludeNext()
{
	N* pointer = next;
	next = nullptr;
	return pointer;
}


// rNode for List Structure.
template<typename T>
class rNode :public NodeBase<T,rNode<T>>
{
public:
	T info;
public:
	rNode() :NodeBase<T, rNode<T>>() {};
	rNode(T& data) :NodeBase<T, rNode<T>>() { info = data; };
	rNode(T& data, rNode<T>* nextNode):NodeBase<T, rNode<T>>(rNode<T>* nextNode) {
		info = data;
	};
	virtual ~rNode() {
		cout << endl << " - Regular: Destructor Class rNode." << endl;
		if (this->next) delete this->next;
	};
};


// pNode for List Structure.
template<typename T>
class pNode :public NodeBase<T, pNode<T>>
{
public:
	T* info;
public:
	pNode() :NodeBase<T, pNode<T>>() { info = nullptr; };
	pNode(T& data) :NodeBase<T, pNode<T>>() {
		T* pdata = &data;
		info = pdata;
	};
	pNode(T& data, pNode<T>* nextNode) :NodeBase<T, pNode<T>>(pNode<T>* nextNode) {
		T* pdata = &data;
		info = pdata;
	};
	pNode(T* data) :NodeBase<T, pNode<T>>() { info = data; };
	pNode(T* data, pNode<T>* nextNode) :NodeBase<T, pNode<T>>(pNode<T>* nextNode) {
		info = data;
	};
	virtual ~pNode() {
		cout << endl << " - Regular: Destructor Class pNode." << endl;
		if (this->next) delete this->next;
	};
};


///////////////////////////////////////////////////////////////////////////////
// List Structure.
template<typename T, class N>
class List
{
	int len;
	N *head, *tail;
public:
	List();
	List(const List<T,N>&);
	~List() {
		cout << endl << " - Regular: Destructor Class List." << endl;
		empty();
		if (head) delete head;
	}
	void empty();
	int  getLen();
	void operator=(const List<T,N>&);	//
	N* getHead() { return head; };
	void insertFront(N*);				// insert a node at the head.
	void insertRear(N*);				// insert a node at the tail.
	void insertOrder(N*);				// insert a node in ascending order.
	void excludeFront();
	void excludeRear();
	void excludeIndex(int);

	//overload.
	void insertFront(T& data) {
		N* p(data);
		insertFront(p);
	};
	void insertFront(T* data) {
		N* p(data);
		insertFront(p);
	};
	void insertRear(T& data) {
		N* p(data);
		insertRear(p);
	};
	void insertRear(T* data) {
		N* p(data);
		insertRear(p);
	};
	void insertOrder(T& data) {
		N* p(data);
		insertOrder(p);
	};
	void insertOrder(T* data) {
		N* p(data);
		insertOrder(p);
	};
};

template<typename T, class N>
List<T, N>::List()
{
	len = 0;
	head = new N;
	tail = head;
}

template<typename T, class N>
List<T, N>::List(const List<T,N>& list)
{
	len = list.len;
	head = list.head;
	tail = list.tail;
}

template<typename T, class N>
void List<T, N>::empty()
{
	//cout << "len = " << len << endl;
	while (len > 0)
		excludeRear();
}

template<typename T, class N>
int List<T, N>::getLen()
{
	return len;
}

template<typename T, class N>
void List<T, N>::operator=(const List<T,N>& list)
{
	len = list.len;
	head = list.head;
	tail = list.tail;
}

template<typename T, class N>
void List<T, N>::insertFront(N* p)
{
	p->next = head->next;
	head->next = p;
	++len;
}

template<typename T, class N>
void List<T, N>::insertRear(N* p)
{
	p->next = tail->next;
	tail->next = p;
	tail = p;
	++len;
}

template<typename T, class N>
void List<T, N>::insertOrder(N* p)
{
	N* pointer = head;
	while (p->info > pointer->next->info && pointer->next)
		pointer = pointer->next;
	p->next = pointer->next;
	pointer->next = p;
	if (pointer == tail) tail = p;
	++len;
}

template<typename T, class N>
void List<T, N>::excludeFront()
{
	if (len > 0)
	{
		N* pointer = head->next;
		head->next = pointer->next;
		delete pointer;
		--len;
	}
}

template<typename T, class N>
void List<T, N>::excludeRear()
{
	if (len > 0)
	{
		N* pointer = head;
		while (pointer->next->next) pointer = pointer->next;
		delete tail;
		tail = pointer;
		--len;
	}
}

template<typename T, class N>
void List<T, N>::excludeIndex(int index)
{
	if (index >= 0 && index < len)
	{
		if (index == len - 1) excludeRear();
		else
		{
			N* pointer = head->next;
			N* pointerPre = head;
			while (index > 0)
			{
				pointerPre = pointer;
				pointer = pointer->next;
				--index;
			}
			pointerPre->next = pointer->next;
			delete pointer;
			--len;
		}
	}
}

////////////////////////////////////////////////////////////////////////
template<typename T> using rList = List<T, rNode<T>>;
template<typename T> using pList = List<T, pNode<T>>;