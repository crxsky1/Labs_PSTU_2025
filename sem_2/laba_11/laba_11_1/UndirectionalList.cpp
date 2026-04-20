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

// однонаправленный список
struct UnidirectionalList {
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
				cout << " " << i << ": \t" << node->data << endl;
				node = node->nextElementAddress;
			}
		}
		cout << endl;
	}
	string getData(int node_i) {
		if (node_i < size) {
			Node* node = firstElementAddress;
			for (int i = 0; i < node_i; i++) {
				node = node->nextElementAddress;
			}
			return node->data;
		}
		else {
			cout << "элемента с номером " << node_i << " не существует, так как " << node_i << " >= " << size;
			return "";
		}
	}

	UnidirectionalList() {};
	UnidirectionalList(int k, ...) {
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

	/////////////////// add ///////////////////
	void add(string data, int node_i) {
		if (node_i > size) {
			cout << "номер больше размера списка, элемент будет добавлен в конец " << node_i << " > " << size << endl << endl;
			node_i = size;
		}


		if (node_i == 0) {
			Node* newNode = new Node{ data, firstElementAddress };
			firstElementAddress = newNode;

			if (node_i == size) endElementAddress = newNode;
		}
		else {
			Node* node = firstElementAddress;

			for (int i = 0; i < node_i - 1; i++) {
				node = node->nextElementAddress;
			}

			Node* newNode = new Node{ data, node->nextElementAddress };
			node->nextElementAddress = newNode;

			if (node_i == size) endElementAddress = newNode;
		}
		size++;


	}
	void addInEnd(string data) {
		add(data, size);
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
	///////////////////////////////////////////


	/////////////////// del ///////////////////
	void del(int node_i) {
		if (node_i >= size) {
			cout << "номер больше размера списка, будет удален последний элемент " << node_i << " > " << size << endl << endl;
			node_i = size - 1;
		}

		Node* node = firstElementAddress;
		Node* tmp;
		for (int i = 0; i < node_i - 1; i++) {
			node = node->nextElementAddress;
		}
		tmp = node->nextElementAddress->nextElementAddress;
		delete node->nextElementAddress;

		node->nextElementAddress = tmp;

		size--;
	}
	void delEndElement() {
		del(size);
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
	//////////////////////////////////////////

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
			addInEnd(str);
		}
		file.close();
		cout << " список загружен из файла: " << name << endl;
	}
	void loadFromFileOverwriting(string name) {
		deleteList();
		loadFromFileAddInEnd(name);
	}
	/////////////////////////////////////////

	void deleteList() {
		for (int i = 0; i < size; i++) {
			del(0);
		}
		size = 0;
		cout << " список удален" << endl;
	}
	~UnidirectionalList() {
		if (size > 0) deleteList();
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "ru");


	////////////////// 	1  //////////////////
	UnidirectionalList list(5,
		"data0", 0,
		"data1", 1,
		"data2", 2,
		"data3", 3,
		"data4", 4
	);


	cout << "\n ------------------  2  ------------------" << endl;

	UnidirectionalList emptyList;
	cout << "  emptyList:" << endl;
	emptyList.print();

	cout << "     list:" << endl;
	list.print();

	emptyList.deleteList(); // лист удаляется автоматически, и без этого


	cout << " ------------------  3  ------------------" << endl;
	cout << " добавление элементов на позиции 2, 6, 4" << endl;
	list.addKElements(3,
		"newData1", 2,
		"newData2", 6,
		"newData3", 4
	);
	list.print();

	cout << " удаление элементов на позициях 3, 1, 5" << endl;
	list.delKElements(3, 3, 1, 5);
	list.print();

	cout << " ------------------  7  ------------------" << endl;
	list.saveInFile("myList.txt");
	cout << "     list:" << endl;
	list.deleteList();
	list.print();

	cout << " ------------------  9  ------------------" << endl;
	list.loadFromFileOverwriting("myList.txt");
	cout << "     list:" << endl;
	list.print();


	cout << " ------------------ 1 0 ------------------" << endl;
	list.deleteList();

}