#include <iostream>
#include <string>

using namespace std;


class Person {
protected:
    string name;
    int age;

public:

    virtual int getAge() const = 0;
    virtual void setAge(int) = 0;

    virtual string getName() const  = 0;
    virtual void setName(string) = 0;



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



    int getAge() const override {
        return age;
    }
    void setAge(int a) override {
        if (a > 0) age = a;
        else age = 0;
    }

    string getName() const override {
        return name;
    }
    void setName(string n) override {
        name = n;
    }
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
