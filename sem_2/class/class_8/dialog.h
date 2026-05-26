#include "group.h"
class Dialog : public Group {
public:
    void handleEvents() {
        char command = ' ';
        while (command != 'q') {
            cout << "Enter command (+/-/s/z/q): ";
            cin >> command;
            switch (command) {
            case '+': {
                Abiturient* a = new Abiturient();
                a->read();
                add(a);
                break;
            }
            case '-': {
                int index;
                cout << "Enter index: ";
                cin >> index;
                remove(index);
                break;
            }
            case 's': {
                print();
                break;
            }
            case 'z': {
                int sum = 0;
                for (auto& p : group) {
                    sum += p->getAge();
                }
                if (group.size() > 0) {
                    cout << "Average age: " << (sum / group.size()) << endl;
                }
                break;
            }
            }
        }
    };
};