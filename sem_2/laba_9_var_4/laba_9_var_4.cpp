#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

bool isPunctuation(char ch) {
    return (ch == '.' || ch == ',' || ch == ';' || ch == ':' ||
        ch == '!' || ch == '?' || ch == '-' || ch == '(' ||
        ch == ')' || ch == '"' || ch == '\'' || ch == '[' ||
        ch == ']' || ch == '{' || ch == '}');
}

bool isSpace(char ch) {
    return (ch == ' ' || ch == '\t');
}

void copyFromLine4(const string& fileIn, const string& fileOut) {
    ifstream fin(fileIn);
    ofstream fout(fileOut);

    if (!fin.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << fileIn << " для чтения!" << endl;
        return;
    }

    if (!fout.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << fileOut << " для записи!" << endl;
        fin.close();
        return;
    }

    string line;
    int lineCount = 0;

    while (getline(fin, line)) {
        lineCount++;
        if (lineCount >= 4) {
            fout << line << endl;
        }
    }

    cout << "Строки из файла " << fileIn << " (начиная с 4-й) скопированы в файл " << fileOut << endl;

    fin.close();
    fout.close();
}

int countCharsInLastWord(const string& line) {
    if (line.empty()) {
        return 0;
    }

    size_t lastSpace = string::npos;
    for (int i = line.length() - 1; i >= 0; i--) {
        if (isSpace(line[i])) {
            lastSpace = i;
            break;
        }
    }

    string lastWord;
    if (lastSpace == string::npos) {
        lastWord = line;
    }
    else {
        lastWord = line.substr(lastSpace + 1);
    }

    while (!lastWord.empty() && isPunctuation(lastWord.back())) {
        lastWord.pop_back();
    }

    return lastWord.length();
}

string getLastWord(const string& line) {
    if (line.empty()) return "";

    size_t lastSpace = string::npos;
    for (int i = line.length() - 1; i >= 0; i--) {
        if (isSpace(line[i])) {
            lastSpace = i;
            break;
        }
    }

    string word;
    if (lastSpace == string::npos) {
        word = line;
    }
    else {
        word = line.substr(lastSpace + 1);
    }

    while (!word.empty() && isPunctuation(word.back())) {
        word.pop_back();
    }

    return word;
}

int countCharsInLastWordOfFile(const string& filename) {
    ifstream fin(filename);

    if (!fin.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << " для чтения!" << endl;
        return -1;
    }

    string line;
    string lastLine;

    while (getline(fin, line)) {
        if (!line.empty()) {
            lastLine = line;
        }
    }

    fin.close();

    if (lastLine.empty()) {
        cout << "Файл " << filename << " пуст или не содержит строк!" << endl;
        return 0;
    }

    string lastWord = getLastWord(lastLine);
    int charCount = lastWord.length();

    cout << "Последняя строка файла: \"" << lastLine << "\"" << endl;
    cout << "Последнее слово: \"" << lastWord << "\"" << endl;

    return charCount;
}

void createTestFile(const string& filename) {
    ofstream fout(filename);

    if (!fout.is_open()) {
        cout << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }

    fout << "Программирование на C++" << endl;
    fout << "Объектно-ориентированное программирование" << endl;
    fout << "Структуры данных и алгоритмы" << endl;
    fout << "Разработка программного обеспечения" << endl;
    fout << "Компьютерные науки" << endl;
    fout << "Искусственный интеллект" << endl;
    fout << "Машинное обучение" << endl;
    fout << "Базы данных" << endl;
    fout << "Сетевые технологии" << endl;
    fout << "Веб-разработка" << endl;

    fout.close();
    cout << "Тестовый файл " << filename << " создан." << endl;
}

void displayFile(const string& filename, const string& title) {
    ifstream fin(filename);

    if (!fin.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    cout << "\n=== " << title << " ===" << endl;
    string line;
    int lineNum = 1;

    while (getline(fin, line)) {
        cout << lineNum << ": " << line << endl;
        lineNum++;
    }

    fin.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string fileF1 = "F1.txt";
    const string fileF2 = "F2.txt";

    cout << "=== РАБОТА С ФАЙЛАМИ ===" << endl;
    cout << endl;

    createTestFile(fileF1);

    displayFile(fileF1, "СОДЕРЖИМОЕ ФАЙЛА F1");

    cout << "\n--- Копирование строк, начиная с 4-й ---" << endl;
    copyFromLine4(fileF1, fileF2);

    displayFile(fileF2, "СОДЕРЖИМОЕ ФАЙЛА F2 (после копирования)");

    cout << "\n--- Подсчет символов в последнем слове F2 ---" << endl;
    int charCount = countCharsInLastWordOfFile(fileF2);

    if (charCount >= 0) {
        cout << "Количество символов в последнем слове: " << charCount << endl;
    }

    system("pause");
    return 0;
}