#include <iostream>
#include <queue>
#include <string>
#include <array>

using namespace std;

void dinoFunc(int argNum, char* args[]);

int main(int argc, char * argv[]) {
	dinoFunc(argc, argv);
	//cout << "Number of argumetns: " << argc << endl;

	return 0;
}

void dinoFunc(int argNum, char* args[]) {
	queue<int> dinoQ;
	//cout << dinoQ.front() << endl;

	for (unsigned int i{1}; i < argNum; i++) {
		string dinoNum = static_cast<string> (args[i]);
		dinoQ.push(stoi(dinoNum));

	}
	int dinoSize = dinoQ.size();
	for (unsigned int j{0}; j < dinoSize; j++) {
		cout << dinoQ.front() << endl;
		dinoQ.pop();
	}
}
