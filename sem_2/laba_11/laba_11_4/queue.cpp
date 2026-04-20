#include <iostream>
#include <stdexcept>

// Структура узла очереди
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Структура очереди
struct Queue {
private:
    Node* front;  // указатель на первый элемент
    Node* rear;   // указатель на последний элемент
    int count;    // количество элементов

public:
    // Конструктор
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    // Деструктор
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Добавление элемента в очередь
    void enqueue(int value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
        std::cout << "Добавлен элемент: " << value << std::endl;
    }

    // Удаление элемента из очереди
    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Ошибка: очередь пуста!");
        }

        Node* temp = front;
        int removedValue = front->data;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        count--;
        std::cout << "Удален элемент: " << removedValue << std::endl;
    }

    // Просмотр первого элемента
    int peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Ошибка: очередь пуста!");
        }
        return front->data;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return front == nullptr;
    }

    // Получение размера очереди
    int size() const {
        return count;
    }

    // Очистка очереди
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
        std::cout << "Очередь очищена" << std::endl;
    }

    // Вывод всех элементов очереди
    void display() const {
        if (isEmpty()) {
            std::cout << "Очередь пуста" << std::endl;
            return;
        }

        std::cout << "Очередь (front -> rear): ";
        Node* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// Простая версия очереди (только основные операции)
struct SimpleQueue {
    Node* front;
    Node* rear;

    // Конструктор
    SimpleQueue() : front(nullptr), rear(nullptr) {}

    // Добавление элемента
    void push(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Удаление элемента
    void pop() {
        if (front == nullptr) return;

        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
    }

    // Просмотр первого элемента
    int frontValue() {
        if (front == nullptr) {
            throw std::runtime_error("Очередь пуста");
        }
        return front->data;
    }

    // Проверка на пустоту
    bool empty() {
        return front == nullptr;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    std::cout << "=== Демонстрация работы очереди ===\n" << std::endl;

    // Создаем очередь
    Queue queue;

    // Добавляем элементы
    std::cout << "Добавление элементов:" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);

    std::cout << "\nТекущее состояние:" << std::endl;
    queue.display();
    std::cout << "Размер очереди: " << queue.size() << std::endl;
    std::cout << "Первый элемент: " << queue.peek() << std::endl;

    std::cout << "\nУдаление элементов:" << std::endl;
    queue.dequeue();
    queue.dequeue();

    std::cout << "\nСостояние после удаления:" << std::endl;
    queue.display();
    std::cout << "Размер очереди: " << queue.size() << std::endl;
    std::cout << "Первый элемент: " << queue.peek() << std::endl;

    // Добавляем еще элементы
    std::cout << "\nДобавление новых элементов:" << std::endl;
    queue.enqueue(60);
    queue.enqueue(70);
    queue.display();

    // Очищаем очередь
    std::cout << "\nОчистка очереди:" << std::endl;
    queue.clear();
    queue.display();

    // Демонстрация SimpleQueue
    std::cout << "\n=== Простая очередь ===\n" << std::endl;
    SimpleQueue simpleQueue;

    simpleQueue.push(100);
    simpleQueue.push(200);
    simpleQueue.push(300);

    std::cout << "Элементы простой очереди: ";
    while (!simpleQueue.empty()) {
        std::cout << simpleQueue.frontValue() << " ";
        simpleQueue.pop();
    }
    std::cout << std::endl;

    return 0;
}