#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct Node {
    string key;
    int value;
    Node* next;
};

struct HashTable {
    Node** buckets;
    int size;
};

HashTable* createTable(int size) {
    HashTable* ht = new HashTable;
    ht->size = size;
    ht->buckets = new Node * [size];
    for (int i = 0; i < size; i++)
        ht->buckets[i] = nullptr;
    return ht;
}

int hashFunc(const string& key, int size) {
    int sum = 0;
    for (char c : key)
        sum += c;
    return sum % size;
}

void put(HashTable* ht, const string& key, int value) {
    int index = hashFunc(key, ht->size);
    Node* curr = ht->buckets[index];
    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            cout << "Обновлён: " << key << " -> " << value << endl;
            return;
        }
        curr = curr->next;
    }
    Node* newNode = new Node{ key, value, ht->buckets[index] };
    ht->buckets[index] = newNode;
    cout << "Вставлен: " << key << " -> " << value << endl;
}

int get(HashTable* ht, const string& key) {
    int index = hashFunc(key, ht->size);
    Node* curr = ht->buckets[index];
    while (curr) {
        if (curr->key == key)
            return curr->value;
        curr = curr->next;
    }
    return -1;
}

bool remove(HashTable* ht, const string& key) {
    int index = hashFunc(key, ht->size);
    Node* curr = ht->buckets[index];
    Node* prev = nullptr;
    while (curr) {
        if (curr->key == key) {
            if (prev == nullptr)
                ht->buckets[index] = curr->next;
            else
                prev->next = curr->next;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void print(HashTable* ht) {
    cout << "----- Хэш-таблица ------";
    cout << endl;
    for (int i = 0; i < ht->size; i++) {
        cout << i << ": ";
        Node* curr = ht->buckets[i];
        if (!curr)
            cout << "(пусто)";
        while (curr) {
            cout << "[" << curr->key << ":" << curr->value << "] ";
            curr = curr->next;
        }
        cout << endl;
    }
    cout << "------------------------";
    cout << endl;
}

void destroy(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* curr = ht->buckets[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
    delete[] ht->buckets;
    delete ht;
}
int main() {
    setlocale(LC_ALL, "ru");

    HashTable* table = createTable(5);

    put(table, "cat", 10);
    put(table, "dog", 20);
    put(table, "bird", 30);
    put(table, "fish", 40);
    put(table, "ant", 50);
    put(table, "cat", 99);

    print(table);

    cout << "Значение 'dog': " << get(table, "dog") << endl;
    cout << "Значение 'cow': " << get(table, "cow") << " (не найдено)" << endl;

    cout << "Удаляем 'bird': " << (remove(table, "bird") ? "успешно" : "нет") << endl;
    print(table);

    destroy(table);
    return 0;
}
