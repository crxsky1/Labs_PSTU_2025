#include <iostream>
#include <vector>
#include "vector.h"

int main() {
    try {
        Vector v(3);
        v[0] = 1;
        v[1] = 2;
        v[2] = 3;

        v.push_back(4);

        v.push_front(0);

        for (size_t i = 0; i < v.m_size; ++i) {
            std::cout << v[i] << " ";
        }
        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
    system("pause");
    return 0;
}