#pragma once
#include <vector>
class Group {
public:
    vector<Person*> group;
    Group() {};
    ~Group() {
        for (auto& p : group) {
            delete p;
        }
    };

    void add(Person* p) {
        group.push_back(p);
    };

    void remove(int index) {
        if (index >= 0 && index < group.size()) {
            delete group[index];
            group.erase(group.begin() + index);
        }
    };

    void print() const {
        for (auto& p : group) {
            p->print();
        }
    };

    int getSize() const {
        return group.size();
    };
};