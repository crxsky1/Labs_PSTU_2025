#include <iostream>

using namespace std;


class Person {
private:
    string name;
    int age;

public:
    Person() {
        name = "безымянный";
        age = 0;
    }
    Person(string n, int a) {
        name = n;
        age = a;
    }

    int getAge() const {
        return age;
    }
    void setAge(int a) {
        if (age > 0) age = a;
    }

    string getName() const {
        return name;
    }
    void setName(string n) {
        name = n;
    }



};

class Teacher : public Person {
private:
    string subject;
    int hours;

public:
    Teacher() {
        subject = "безработный";
        hours = 0;
    }
    Teacher(string s, int h, string n, int a) {
        subject = s;
        hours = h;

        setAge(a);
        setName(n);

    }

    string getSubject() const { return subject; }
    int getHours() const { return hours; }



};

ostream& operator<<(ostream& out, const Teacher& t) {
    out << "Teacher:\n"
        << "\tName: " << t.getName() << "\n"
        << "\tAge: " << t.getAge() << "\n"
        << "\tSubject: " << t.getSubject() << "\n"
        << "\tHours: " << t.getHours();
    return out;
}


int main() {
    Teacher t1("English language", 50, "Elena", 30);

    cout << t1;
}
