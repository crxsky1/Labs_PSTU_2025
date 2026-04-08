#include <iostream>
#include <string>
#include <cstring>
#include<windows.h>

using namespace std;

const int MAX_PEOPLE = 100; // максимальное количество людей

// Структура "Человек"
struct Human {
    string lastName;   // фамилия
    string firstName;  // имя
    string patronymic; // отчество
    string homeAddress; // домашний адрес
    string phoneNumber; // номер телефона
    int age;           // возраст
};

// Функция для ввода данных о человеке
void inputHuman(Human& h) {
    cout << "Введите фамилию: ";
    getline(cin, h.lastName);

    cout << "Введите имя: ";
    getline(cin, h.firstName);

    cout << "Введите отчество: ";
    getline(cin, h.patronymic);

    cout << "Введите домашний адрес: ";
    getline(cin, h.homeAddress);

    cout << "Введите номер телефона: ";
    getline(cin, h.phoneNumber);

    cout << "Введите возраст: ";
    cin >> h.age;
    cin.ignore(); // очищаем буфер после ввода числа
}

// Функция для вывода данных о человеке
void printHuman(const Human& h) {
    cout << "\n--- Данные о человеке ---" << endl;
    cout << "ФИО: " << h.lastName << " " << h.firstName << " " << h.patronymic << endl;
    cout << "Адрес: " << h.homeAddress << endl;
    cout << "Телефон: " << h.phoneNumber << endl;
    cout << "Возраст: " << h.age << " лет" << endl;
}

// Функция для поиска человека по фамилии
int findByLastName(const Human humans[], int count, const string& lastName) {
    for (int i = 0; i < count; i++) {
        if (humans[i].lastName == lastName) {
            return i;
        }
    }
    return -1;
}

// Функция для вывода всех людей
void printAllHumans(const Human humans[], int count) {
    if (count == 0) {
        cout << "Список пуст!" << endl;
        return;
    }

    cout << "\n=== Список всех людей (всего: " << count << ") ===" << endl;
    for (int i = 0; i < count; i++) {
        cout << "\n[" << i + 1 << "]";
        printHuman(humans[i]);
    }
}

// Функция для редактирования данных человека
void editHuman(Human& h) {
    cout << "\n--- Редактирование данных ---" << endl;
    cout << "Оставьте поле пустым, чтобы не изменять" << endl;

    string temp;

    cout << "Фамилия (" << h.lastName << "): ";
    getline(cin, temp);
    if (!temp.empty()) h.lastName = temp;

    cout << "Имя (" << h.firstName << "): ";
    getline(cin, temp);
    if (!temp.empty()) h.firstName = temp;

    cout << "Отчество (" << h.patronymic << "): ";
    getline(cin, temp);
    if (!temp.empty()) h.patronymic = temp;

    cout << "Адрес (" << h.homeAddress << "): ";
    getline(cin, temp);
    if (!temp.empty()) h.homeAddress = temp;

    cout << "Телефон (" << h.phoneNumber << "): ";
    getline(cin, temp);
    if (!temp.empty()) h.phoneNumber = temp;

    cout << "Возраст (" << h.age << "): ";
    getline(cin, temp);
    if (!temp.empty()) h.age = stoi(temp);

    cout << "Данные обновлены!" << endl;
}

// Функция для удаления человека по индексу
void deleteHuman(Human humans[], int& count, int index) {
    if (index < 0 || index >= count) {
        cout << "Неверный индекс!" << endl;
        return;
    }

    for (int i = index; i < count - 1; i++) {
        humans[i] = humans[i + 1];
    }
    count--;
    cout << "Запись удалена!" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Human humans[MAX_PEOPLE];
    int count = 0; // текущее количество людей
    int choice;

    do {
        cout << "\n======================" << endl;
        cout << "        МЕНЮ         " << endl;
        cout << "======================" << endl;
        cout << "1. Добавить человека" << endl;
        cout << "2. Показать всех людей" << endl;
        cout << "3. Найти человека по фамилии" << endl;
        cout << "4. Редактировать данные" << endl;
        cout << "5. Удалить человека" << endl;
        cout << "6. Выйти" << endl;
        cout << "======================" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            if (count >= MAX_PEOPLE) {
                cout << "Достигнут максимум (" << MAX_PEOPLE << ") человек!" << endl;
                break;
            }

            cout << "\n--- Добавление нового человека ---" << endl;
            inputHuman(humans[count]);
            count++;
            cout << "Человек успешно добавлен!" << endl;
            break;
        }

        case 2: {
            printAllHumans(humans, count);
            break;
        }

        case 3: {
            if (count == 0) {
                cout << "Список пуст. Сначала добавьте людей." << endl;
                break;
            }

            string searchLastName;
            cout << "\nВведите фамилию для поиска: ";
            getline(cin, searchLastName);

            int index = findByLastName(humans, count, searchLastName);
            if (index != -1) {
                cout << "\nЧеловек найден:" << endl;
                printHuman(humans[index]);
            }
            else {
                cout << "Человек с фамилией \"" << searchLastName << "\" не найден." << endl;
            }
            break;
        }

        case 4: {
            if (count == 0) {
                cout << "Список пуст. Сначала добавьте людей." << endl;
                break;
            }

            string searchLastName;
            cout << "\nВведите фамилию человека для редактирования: ";
            getline(cin, searchLastName);

            int index = findByLastName(humans, count, searchLastName);
            if (index != -1) {
                cout << "\nНайден:";
                printHuman(humans[index]);
                editHuman(humans[index]);
            }
            else {
                cout << "Человек с фамилией \"" << searchLastName << "\" не найден." << endl;
            }
            break;
        }

        case 5: {
            if (count == 0) {
                cout << "Список пуст. Нечего удалять." << endl;
                break;
            }

            string searchLastName;
            cout << "\nВведите фамилию человека для удаления: ";
            getline(cin, searchLastName);

            int index = findByLastName(humans, count, searchLastName);
            if (index != -1) {
                cout << "\nНайден:";
                printHuman(humans[index]);
                cout << "\nВы уверены, что хотите удалить? (y/n): ";
                char confirm;
                cin >> confirm;
                cin.ignore();
                if (confirm == 'y' || confirm == 'Y') {
                    deleteHuman(humans, count, index);
                }
                else {
                    cout << "Удаление отменено." << endl;
                }
            }
            else {
                cout << "Человек с фамилией \"" << searchLastName << "\" не найден." << endl;
            }
            break;
        }

        case 6: {
            cout << "\nПрограмма завершена. До свидания!" << endl;
            break;
        }

        default: {
            cout << "Неверный выбор. Попробуйте снова (1-6)." << endl;
            break;
        }
        }
    } while (choice != 6);

    return 0;
}