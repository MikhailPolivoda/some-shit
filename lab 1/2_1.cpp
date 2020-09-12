#include <iostream>
#include "classes.h"

using namespace std;

void TestRandomGenerators() {
	try {
		RandomGenerator generate("test", 3);

		if (generate.getName() == "test") {
			cout << "test 1 completed" << endl;
		}
		else {
			cout << "test 1 uncompleted" << endl;
		}

		if (generate.NextNumber() == generate.getPrevious()) {
			cout << "test 2 completed" << endl;
		}
		else {
			cout << "test 2 uncompleted" << endl;
		}
		int pi = 3;
		generate.setPrevious(pi);
		if (generate.getPrevious() == pi) {
			cout << "test 3 completed" << endl;
		}
		else {
			cout << "test 3 uncompleted" << endl;
		}
	}
	catch(exception& ex){
		cout << "Global test uncompleted";
	}
	
}

void TestGeneratorWithStep() {
	try {
		GeneratorWithStep generate("test", 5.7, 1.1, 3);
		if (generate.getName() == "test") {
			cout << "test 1 completed" << endl;
		}
		else {
			cout << "test 1 uncompleted" << endl;
		}

		if (generate.getPrevious()) {
			cout << "test 2 completed" << endl;
		}
		else {
			cout << "test 2 uncompleted" << endl;
		}
		double pi = 3.14;
		generate.setPrevious(pi);
		if (generate.getPrevious() == pi) {
			cout << "test 3 completed" << endl;
		}
		else {
			cout << "test 3 uncompleted" << endl;
		}
		generate.NextNumber();
		generate.NextNumber();
		if (generate.AverageNumbers() == 4.24) {
			cout << "test 4 completed" << endl;
		}
		else {
			cout << "test 4 uncompleted " << generate.AverageNumbers() << endl;
		}

	}
	catch (exception & ex) {
		cout << "Global test uncompleted";
	}
}

int main() {
	TestRandomGenerators();
	TestGeneratorWithStep();


	return 0;
}