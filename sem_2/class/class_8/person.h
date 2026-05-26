#pragma once
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person() {};
    Person(const string& name_, int age_) : name(name_), age(age_) {};
    virtual ~Person() {};

    virtual void print() const = 0;

    virtual void read() {
        cout << "Name: ";
        cin >> name;
        cout << "Age: ";
        cin >> age;
    };

    const string& getName() const {
        return name;
    };

    void setName(const string& name_) {
        name = name_;
    };

    int getAge() const {
        return age;
    };

    void setAge(int age_) {
        age = age_;
    };
};