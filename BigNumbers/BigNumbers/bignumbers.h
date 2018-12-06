#pragma once
#ifndef _BIGNUMBERS_H_
#define _BIGNUMBERS_H_
#include <deque>

using namespace std;

class BigNumber{
public:
	BigNumber(string nr);
	BigNumber();
	~BigNumber() {};
	int get_valid();
	void print_normal();
	void print_scientific();
	const deque<int> &getnumber() const;
	deque<int> &setnumber();
	char getsign() const;
	void setsign(char sgn);
	BigNumber &addition(BigNumber& nr1, BigNumber& nr2);
	friend BigNumber operator+(BigNumber const &nr1, BigNumber const &nr2);
private:
	std::deque <int> number;
	std::deque <int> mantis;
	char sign;
	int exp;
	bool valid;
};


#endif _BIGNUMBERS_H_