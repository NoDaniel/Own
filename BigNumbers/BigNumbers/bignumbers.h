#pragma once
#ifndef _BIGNUMBERS_H_
#define _BIGNUMBERS_H_
#include <deque>

using namespace std;

class BigNumber{
public:
	//Costructors and destructor
	BigNumber(string nr); //General constructor
	BigNumber();	//Default constructor
	BigNumber(int nr);	//Type conversion constructor int->BigNumber
	BigNumber(char ch);	//Type conversion constructor char->BigNumber
	BigNumber(BigNumber &n1);	//Copy constructor
	~BigNumber() {};		//Destructor

	//Utility
	void print_normal() const;
	void print_scientific() const;
	void to_scientific();

	//Getters and setters
	const deque<int> &getnumber() const;
	deque<int> &setnumber();
	char getsign() const;
	void setsign(char sgn);

	//Operations
	BigNumber &addition(BigNumber& nr1, BigNumber& nr2);

	//Operators
	friend BigNumber operator+(BigNumber const &nr1, BigNumber const &nr2);
private:
	deque <int> number;
	deque <int> mantis;
	char sign;
	int exp;
	bool valid;
};


#endif _BIGNUMBERS_H_