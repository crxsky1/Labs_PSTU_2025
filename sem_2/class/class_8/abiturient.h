#include "person.h"
#include <string>
class Abiturient : public Person {
private:
    int score;
    string specialization;

public:
    Abiturient() {};
    Abiturient(const string& name_, int age_, int score_, const string& specialization_)
        : Person(name_, age_), score(score_), specialization(specialization_) {
    };
    ~Abiturient() {};

    void print() const override {
        cout << "Name: " << name << ", Age: " << age << ", Score: " << score << ", Specialization: " << specialization << endl;
    };

    void read() override {
        Person::read();
        cout << "Score: ";
        cin >> score;
        cout << "Specialization: ";
        cin >> specialization;
    };

    int getScore() const {
        return score;
    };

    void setScore(int score_) {
        score = score_;
    };

    const string& getSpecialization() const {
        return specialization;
    };

    void setSpecialization(const string& specialization_) {
        specialization = specialization_;
    };
};