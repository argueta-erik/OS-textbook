#include <iostream>
#include <string>
#include <sstream>


void prompt(std::string& name);
void printName(std::string name);

int main() {
	std::string input{};
	prompt(input);
	printName(input);
	return 0;
}

void prompt(std::string& name) {
	std::cout << "Enter your name: ";
	std::getline(std::cin, name);
	//cout << "Name: " << input << endl;

}

void printName(std::string name) {
	std::cout << "Name: " << name << std::endl;
}
