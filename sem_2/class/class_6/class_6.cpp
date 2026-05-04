#include <iostream>
#include <string>

using namespace std;

#include "list.h"

int main() {
	List<int> listI = { 1, 2, 3, 4 };

	for (auto it = listI.rbegin(); it != listI.rend(); it++) {
		cout << *it << " ";
	}
}