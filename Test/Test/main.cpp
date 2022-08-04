#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	char* A = new char{'A'};
	char* B = new char{'B'};
	char* C = new char{'C'};
	char* D = new char{'D'};

	std::vector<char*> copy1 = {A, B, C, D};
	std::vector<char*> copy2;

	for(std::vector<char*>::iterator iter = copy1.begin(); iter < copy1.end(); iter++){
		std::cout << **iter << std::endl;
	}

	std::cout << std::endl;
	copy2.assign(copy1.begin(), copy1.end());
	for (std::vector<char*>::iterator iter = copy2.begin(); iter < copy2.end(); iter++) {
		std::cout << **iter << std::endl;
	}

	return 0;
}