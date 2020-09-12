#include "classes.h"
#include <stdexcept>
#include<iostream>
using namespace std;
RandomGenerator::RandomGenerator(const string& name, int N)
{
	if (N <= 0) 
		throw invalid_argument("недопустимое значение N");
	this->name = name;
	this->N = N;
}

int RandomGenerator::NextNumber()
{
	double res = this->getRand();
	sequence.push_back(res);

	return res;
}

int RandomGenerator::getPrevious() const
{
	if (sequence.empty())
	{
		return 0;
	}
	
	return sequence[sequence.size() - 1];
}

void RandomGenerator::setPrevious(int number)
{
	sequence.clear();
	sequence.push_back(number);
	srand(number);
}

string RandomGenerator::getName() const
{
	return this->name;
}

int RandomGenerator::AverageNumbers() const
{
	int sum = 0;
	if (N > sequence.size())
		throw out_of_range("выход за пределы значений");

	for (int i = sequence.size() - 1; i + 1 > sequence.size()  - N; i--)
	{
		sum += sequence[i];
	}
	return sum / N;
}

double RandomGenerator::getRand() const
{
	// TODO: написать формулу
	return rand();
}

GeneratorWithStep::GeneratorWithStep(const string& name,double first_number, double step, int N)
{
	if (N <= 0) 
		throw invalid_argument("недопустимое значение N");
	sequence.push_back(first_number);
	this->name = name;
	this->step = step;

	this->N = N;

}

double GeneratorWithStep::NextNumber()
{
	double res = this->getPrevious() + this->step;
	sequence.push_back(res);

	return res;
}

double GeneratorWithStep::getPrevious() const
{
	if (sequence.empty())
	{
		return 0.0;
	}

	return sequence[sequence.size() - 1];
}

void GeneratorWithStep::setPrevious(double number)
{
	sequence.clear();
	sequence.push_back(number);
}

string GeneratorWithStep::getName() const
{
	return this->name;
}

double GeneratorWithStep::AverageNumbers() const
{
	if (N > sequence.size()) 
		throw out_of_range("выход за пределы значений");
	double sum = 0.0;

	for (int i = sequence.size() - 1; i + 1 > sequence.size() - N; i--)
	{
		sum += sequence[i];
		cout << sum << endl;
	}
	return  sum / N;
}