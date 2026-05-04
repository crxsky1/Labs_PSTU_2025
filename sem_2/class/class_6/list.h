#pragma once

template <typename T>
class List {
private:
	struct Node {
		T data;
		Node* nextElementAddress = nullptr;
		Node* prevElementAddress = nullptr;

		Node(T d, Node* nea, Node* pea) : data(d), nextElementAddress(nea), prevElementAddress(pea) {};
	};
	const Node* foundNode(int node_i) const {
		if (node_i > size || node_i < 0) throw runtime_error("Index out of range");

		if (node_i == size) return nullptr;

		Node* node;
		if (node_i < size / 2) {
			node = firstElementAddress;
			for (int i = 0; i < node_i; i++) {
				node = node->nextElementAddress;
			}
		}
		else {
			node = endElementAddress;
			for (int i = size - 1; i > node_i; i--) {
				node = node->prevElementAddress;
			}
		}
		return node;
	}
	Node* foundNode(int node_i) {
		if (node_i > size || node_i < 0) throw runtime_error("Index out of range");

		if (node_i == size) return nullptr;

		Node* node;
		if (node_i < size / 2) {
			node = firstElementAddress;
			for (int i = 0; i < node_i; i++) {
				node = node->nextElementAddress;
			}
		}
		else {
			node = endElementAddress;
			for (int i = size - 1; i > node_i; i--) {
				node = node->prevElementAddress;
			}
		}
		return node;
	}


	int size = 0;

	Node* firstElementAddress = nullptr;
	Node* endElementAddress = nullptr;

public:
	void print() {
		Node* node = firstElementAddress;
		if (size == 0) {
			cout << " ������ ������" << endl;
		}
		else {
			for (int i = 0; i < size; i++) {
				cout << " " << i << ": \t" << node->data /* << "    \t" << node->prevElementAddress << "\t" << node << "\t" << node->nextElementAddress*/ << endl;
				node = node->nextElementAddress;
			}
		}
		cout << endl;
	}

	List() {};
	List(initializer_list<T> init) { // ��� ������ list = { 1, 2, 3 }
		for (const T& value : init) {
			push_back(value);
		}
	}
	List(const List& newList) : size(0), firstElementAddress(nullptr), endElementAddress(nullptr) {
		//					  |_________________________���_newList______________________________|

		Node* node = newList.firstElementAddress;
		while (node != nullptr) {
			push_back(node->data);
			node = node->nextElementAddress;
		}
	}

	List& operator=(initializer_list<T> init) {
		deleteList();

		for (const T& value : init) {
			push_back(value);
		}

		return *this;
	}
	List& operator=(const List& newList) {
		if (this == &newList) return *this;

		deleteList();
		Node* node = newList.firstElementAddress;
		while (node != nullptr) {
			push_back(node->data);
			node = node->nextElementAddress;
		}
		return *this;
	}


	void add(T data, int node_i) {
		if (node_i > size || node_i < 0) throw runtime_error("Index out of range");

		if (firstElementAddress == nullptr) {
			firstElementAddress = new Node{ data, nullptr, nullptr };
			endElementAddress = firstElementAddress;
		}
		else if (node_i == 0) {
			Node* newNode = new Node{ data, firstElementAddress, nullptr };
			firstElementAddress->prevElementAddress = newNode;
			firstElementAddress = newNode;
		}
		else if (node_i == size) {
			Node* newNode = new Node{ data, nullptr, endElementAddress };

			endElementAddress->nextElementAddress = newNode;
			endElementAddress = newNode;
		}
		else {
			Node* node = foundNode(node_i);
			Node* newNode = new Node{ data, node, node->prevElementAddress };

			node->prevElementAddress->nextElementAddress = newNode;
			node->prevElementAddress = newNode;
		}
		size++;
	}
	void push_back(T data) {
		add(data, size);
	}

	void del(int node_i) {
		if (node_i > size || node_i < 0) throw runtime_error("Index out of range");

		Node* node = foundNode(node_i);

		if (node_i == 0) {
			firstElementAddress = node->nextElementAddress;
			if (firstElementAddress != nullptr) firstElementAddress->prevElementAddress = nullptr;
			if (size == 1) endElementAddress = nullptr;

			delete node;
		}
		else if (node_i == size - 1) {
			endElementAddress = node->prevElementAddress;
			if (endElementAddress) endElementAddress->nextElementAddress = nullptr;
			else firstElementAddress = nullptr;
			delete node;
		}
		else {
			node->nextElementAddress->prevElementAddress = node->prevElementAddress;
			node->prevElementAddress->nextElementAddress = node->nextElementAddress;

			delete node;
		}

		size--;
	}

	void deleteList() {
		while (size > 0) del(0);
		size = 0;
	}
	~List() {
		if (size > 0) deleteList();
	}

	int operator()() const {
		return size;
	}

	T& operator[](int node_i) {
		if (node_i >= size || node_i < 0) throw runtime_error("Index out of range");
		return foundNode(node_i)->data;
	}
	const T& operator[](int node_i) const {
		if (node_i >= size || node_i < 0) throw runtime_error("Index out of range");
		return foundNode(node_i)->data;
	}

	List<T> operator+(const T& value) const {
		List<T> newList;
		Node* node = firstElementAddress;
		for (int i = 0; i < size; i++) {
			newList.push_back(node->data + value);
			node = node->nextElementAddress;
		}
		return newList;
	}
	friend List<T> operator+(const T& value, const List<T>& list) {
		List<T> newList;
		Node* node = list.firstElementAddress;
		while (node) {
			newList.push_back(value + node->data);
			node = node->nextElementAddress;
		}
		return newList;
	}

	List<T> operator*(const T& value) const {
		List<T> newList;
		Node* node = firstElementAddress;
		while (node) {
			newList.push_back(node->data * value);
			node = node->nextElementAddress;
		}
		return newList;
	}
	friend List<T> operator*(const T& value, const List<T>& list) {
		return list * value;  // ������������ ������
	}


	class Iterator {
	private:
		Node* ptr;

	public:
		Iterator(Node* p) : ptr(p) {}


		Iterator& operator++() {
			if (ptr != nullptr) ptr = ptr->nextElementAddress;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			ptr = ptr->nextElementAddress;
			return tmp;
		}

		Iterator& operator--() {
			if (ptr != nullptr) ptr = ptr->prevElementAddress;
			return *this;
		}
		Iterator operator--(int) {
			Iterator tmp = *this;
			ptr = ptr->prevElementAddress;
			return tmp;
		}



		Iterator operator+(const int& value) const {
			Iterator iter = *this;
			for (int i = 0; i < value && iter.ptr != nullptr; ++i) {
				iter.ptr = iter.ptr->nextElementAddress;
			}
			return iter;
		}
		friend Iterator operator+(const int& value, const Iterator& iter) {
			return iter + value;
		}
		Iterator& operator+=(int n) {
			for (int i = 0; i < n && ptr; ++i) ptr = ptr->nextElementAddress;
			return *this;
		}

		Iterator operator-(const int& value) const {
			Iterator iter = *this;
			for (int i = 0; i < value && iter.ptr != nullptr; ++i) {
				iter.ptr = iter.ptr->prevElementAddress;
			}
			return iter;
		}
		friend Iterator operator-(const int& value, const Iterator& iter) {
			return iter - value;
		}
		Iterator& operator-=(int n) {
			for (int i = 0; i < n && ptr; ++i) ptr = ptr->prevElementAddress;
			return *this;
		}



		bool operator==(const Iterator& other) const {
			return ptr == other.ptr;
		}
		bool operator!=(const Iterator& other) const {
			return ptr != other.ptr;
		}

		T& operator*() {
			return ptr->data;
		}
		const T& operator*() const {
			return ptr->data;
		}
	};

	Iterator begin() { return Iterator(firstElementAddress); }
	Iterator end() { return Iterator(nullptr); };
	Iterator rbegin() { return Iterator(endElementAddress); }
	Iterator rend() { return Iterator(nullptr); }

	Iterator begin() const { return Iterator(firstElementAddress); }
	Iterator end() const { return Iterator(nullptr); }
	Iterator rbegin() const { return Iterator(endElementAddress); }
	Iterator rend() const { return Iterator(nullptr); }
}
