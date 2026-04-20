#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

void invertSort(int* arr, int size) {
	int tmp;
	for (int j = 0; j < size - 1; j++) {
		for (int i = 0; i < size - j - 1; i++) {
			if (arr[i] < arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
}

// Стек
struct Stack {
private:
	struct Node {
		string data;
		Node* nextElementAddress = nullptr;
	};

public:
	int size = 0;
	Node* firstElementAddress = nullptr;
	Node* endElementAddress = nullptr;

	void print() {
		Node* node = firstElementAddress;
		if (size == 0) {
			cout << " список пустой" << endl;
		}
		else {
			for (int i = 0; i < size; i++) {
				// cout << " " << i << ": \t" << node->data << "\t" << node << "\t" << node->nextElementAddress << endl;
				cout << " " << i << ": \t" << node->data << endl;
				node = node->nextElementAddress;
			}
		}
		cout << endl;
	}

	//////////////// commands ////////////////
	void push(string data) {
		Node* newNode = new Node{ data };
		if (size == 0) {
			endElementAddress = newNode;
			firstElementAddress = newNode;
		}
		else {
			endElementAddress->nextElementAddress = newNode;
			endElementAddress = newNode;
		}
		size++;
	}
	string pop() {
		if (size == 0) return "";

		string data = endElementAddress->data;

		if (size == 1) {
			delete firstElementAddress;
			firstElementAddress = nullptr;
			endElementAddress = nullptr;
		}
		else {
			Node* node = firstElementAddress;
			// Находим предпоследний элемент
			for (int i = 0; i < size - 2; i++) {
				node = node->nextElementAddress;
			}
			delete endElementAddress;
			endElementAddress = node;
			endElementAddress->nextElementAddress = nullptr;
		}

		size--;
		return data;
	}
	//////////////////////////////////////////

	void add(string data, int node_i) {
		if (node_i == size) {
			push(data);
			return;
		}
		else if (node_i > size) {
			cout << endl << "номер добавляемого элемента больше чем размер стека, элемент буде добавлен в конец  " << node_i << " > " << size << endl;
			node_i = size;
		}


		int arrSize = size - node_i;
		string* arr = new string[arrSize];

		for (int i = 0; i < arrSize; i++) {
			arr[i] = pop();
		}

		push(data);

		for (int i = 0; i < arrSize; i++) {
			push(arr[arrSize - i - 1]);
		}

		delete[] arr;
	}
	void del(int node_i) {
		if (node_i > size) {
			cout << endl << "номер удаляемого элемента больше чем размер стека, будет удален последний элемент  " << node_i << " > " << size << endl;
			node_i = size - 1;
		}


		int arrSize = size - node_i - 1;
		string* arr = new string[arrSize];

		for (int i = 0; i < arrSize; i++) {
			arr[i] = pop();
		}

		pop();

		for (int i = 0; i < arrSize; i++) {
			push(arr[arrSize - i - 1]);
		}

		delete[] arr;
	}

	void addKElements(int k, ...) {
		// addKElements(int k, "data1", index1, "data2", index2, ...)
		//					   |____k = 1____|   |____k = 2____|	

		va_list args;
		va_start(args, k);

		const char* data; // string не работает
		int index;

		for (int i = 0; i < k; i++) {
			data = va_arg(args, const char*);
			index = va_arg(args, int);

			add(data, index);
		}

		va_end(args);
	}
	void delKElements(int k, ...) {
		va_list args;
		va_start(args, k);

		int* arr = new int[k];


		for (int i = 0; i < k; i++) {
			arr[i] = va_arg(args, int);
		}
		invertSort(arr, k); // нужно удалять начиная с наибольшего
		// индекса, чтобы сохранить индексацию

		for (int i = 0; i < k; i++) {
			del(arr[i]);
		}

		delete[] arr;
		va_end(args);
	}

	Stack() {}
	Stack(int k, ...) {
		// тоже самое что и addKElements()

		va_list args;
		va_start(args, k);

		const char* data; // string не работает
		int index;

		for (int i = 0; i < k; i++) {
			data = va_arg(args, const char*);
			index = va_arg(args, int);

			add(data, index);
		}

		va_end(args);

	}

	////////////////// file //////////////////
	void saveInFile(string name) {
		ofstream file(name);

		Node* node = firstElementAddress;
		for (int i = 0; i < size; i++) {
			file << node->data << "\n";
			node = node->nextElementAddress;
		}
		cout << " список сохранен в файл: " << name << endl;
		file.close();
	}

	void loadFromFileAddInEnd(string name) {
		ifstream file(name);
		string str = " ";
		while (getline(file, str)) {
			push(str);
		}
		file.close();
		cout << " список загружен из файла: " << name << endl;
	}
	void loadFromFileOverwriting(string name) {
		deleteStack();
		loadFromFileAddInEnd(name);
	}
	/////////////////////////////////////////

	void deleteStack() {
		for (int i = 0; i < size; i++) {
			pop();
		}
		size = 0;
		cout << " список удален" << endl;
	}
	~Stack() {
		if (size > 0) deleteStack();
	}
};


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "ru");





	////////////////// 	1  //////////////////
	Stack stack(5,
		"data0", 0,
		"data1", 1,
		"data2", 2,
		"data3", 3,
		"data4", 4
	);


	cout << "\n ------------------  2  ------------------" << endl;

	Stack emptyList;
	cout << "  emptyStack:" << endl;
	emptyList.print();

	cout << "    stack:" << endl;
	stack.print();

	emptyList.deleteStack(); // лист удаляется автоматически, и без этого


	cout << "\n ------------------  3  ------------------" << endl;
	cout << " добавление элементов на позиции 2, 6, 4" << endl;
	stack.addKElements(3,
		"newData1", 2,
		"newData2", 6,
		"newData3", 4
	);
	stack.print();

	cout << " удаление элементов на позициях 3, 1, 5" << endl;
	stack.delKElements(3, 3, 1, 5);
	stack.print();

	cout << " ------------------  7  ------------------" << endl;
	stack.saveInFile("myStack.txt");
	cout << "     stack:" << endl;
	stack.deleteStack();
	stack.print();

	cout << " ------------------  9  ------------------" << endl;
	stack.loadFromFileOverwriting("myStack.txt");
	cout << "     stack:" << endl;
	stack.print();


	cout << " ------------------ 1 0 ------------------" << endl;
	stack.deleteStack();

}