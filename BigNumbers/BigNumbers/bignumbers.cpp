#include <iostream>
#include <string>
//#include <vector>
#include "bignumbers.h"

using namespace std;

BigNumber::BigNumber() {
	sign = '+';
	exp = 0;
	valid = 1;
}

BigNumber::BigNumber(string nr) {

	//get the sign
	int i;
	if (nr[0] == '-') {
		sign = '-';
		i = 1;
	}
	else {
		sign = '+';
		i = 0;
	}

	//initialize the valid tag, the exponent, and the checker for exponent
	valid = 1;
	exp = 0;
	int exponent = 0;
	for ( ; i < nr.length(); i++) {
		//check if the number is valid
		if ((nr[i] > '9' || nr[i]  < '0') && nr[i] != 'e') {
			valid = 0;
		}

		//check if the number type is scientific, and it got to the exponent
		if (nr[i] == 'e') {
			exponent = 1;
			i++;
		}

		//register the number, or the exponent
		if (exponent == 0) {
			mantis.push_back(nr[i] - '0');
		}
		else {
			exp = exp * 10 + (nr[i] - '0');
		}
	}

	for (auto it = mantis.begin(); it != mantis.end(); it++) {
		number.push_back(*it);
	}

	for (int i = 0; i < exp; i++) {
		number.push_back(0);
	}

}

int BigNumber::get_valid() { return valid; }

void BigNumber::print_normal() {
	
	bool extra = true;

	if (valid == 0) {
		cout << "Imposible to print an invalid number \n";
	}
	else {
		if (sign == '-' || sign == '+') {
			cout << sign;
		}
		for (auto it = number.begin(); it != number.end(); it++) {
			if (*it != 0) {
				extra = false;
			}
			if (extra == false) {
				cout << *it;
			}
		}
	}

	cout << endl;
}

void BigNumber::print_scientific() {

	if (valid == 0) {
		cout << "Imposible to print an invalid number \n";
	}
	else {
		cout << sign;
		for (auto it = mantis.begin(); it != mantis.end(); it++) {
			cout << *it;
		}
		cout << "e" << exp;
	}

	cout << endl;
}


BigNumber &BigNumber::addition(BigNumber& nr1, BigNumber& nr2) {

	int bigger;

	if (nr1.number.size() > nr2.number.size()) {
		this->sign = nr1.sign;
		bigger = 1;
	}
	else if (nr1.number.size() < nr2.number.size()) {
		this->sign = nr1.sign;
		bigger = 2;
	}
	else if (nr1.number.size() == nr2.number.size()) {
		if (nr1.number[0] > nr2.number[0]) {
			this->sign = nr1.sign;
			bigger = 1;
		}
		else if (nr1.number[0] < nr2.number[0]) {
			this->sign = nr2.sign;
			bigger = 2;
		}
		else if (nr1.number[0] == nr2.number[0]) {
			auto it1 = nr1.number.begin();
			auto it2 = nr2.number.begin();
			while (it1!=nr1.number.end()) {
				if (*it1 > *it2) {
					this->sign = nr1.sign;
					bigger = 1;
				}
				else if(*it1 < *it2){
					this->sign = nr2.sign;
					bigger = 2;
				}
				it1++;
				it2++;
			}
		}
	}

	if ((nr1.sign == '+' && nr2.sign == '+') || (nr1.sign == '-' && nr2.sign == '-')) {
		auto it1 = nr1.number.end() - 1;
		auto it2 = nr2.number.end() - 1;
		int carry = 0;
		while (it1 != nr1.number.begin() && it2 != nr2.number.begin()) {

			this->number.push_front((*it1 + *it2 + carry) % 10);
			if ((*it1 + *it2 + carry) / 10 >= 0) {
				carry = 1;
			}
			else {
				carry = 0;
			}


			it1--;
			it2--;
		}	
		///////
		this->number.push_front((*it1 + *it2 + carry) % 10);
		if ((*it1 + *it2 + carry) / 10) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		///////
		if (nr1.number.size() > nr2.number.size()) {
			while (it1 != nr1.number.begin()) {
				it1--;
				this->number.push_front(*it1 + carry);
				carry = 0;
			}
		}else if (nr1.number.size() < nr2.number.size()) {
			while (it2 != nr2.number.begin()) {
				it2--;
				this->number.push_front(*it2 + carry);
				carry = 0;
			}
		}
	}
	else if (bigger == 1) {
		auto it1 = nr1.number.end() - 1;
		auto it2 = nr2.number.end() - 1;
		int borrow = 0;
		while (it1 != nr1.number.begin() && it2 != nr2.number.begin()) {

			if (*it1 - borrow >= *it2) {
				this->number.push_front(*it1 - *it2 - borrow);
				borrow = 0;
			}
			else if (*it1 - borrow < *it2) {
				this->number.push_front((*it1 + 10) - *it2 - borrow);
				borrow = 1;
			}

			it1--;
			it2--;
		}
		//////
		if (*it1 - borrow >= *it2) {
			this->number.push_front(*it1 - *it2 - borrow);
			borrow = 0;
		}
		else if (*it1 - borrow < *it2) {
			this->number.push_front((*it1 + 10) - *it2 - borrow);
			borrow = 1;
		}
		//////
		while (it1 != nr1.number.begin()) {
			it1--;
			this->number.push_front(*it1 - borrow);
			borrow = 0;
		}

	}
	else if (bigger == 2) {
		auto it1 = nr1.number.end() - 1;
		auto it2 = nr2.number.end() - 1;
		int borrow = 0;
		while (it1 != nr1.number.begin() && it2 != nr2.number.begin()) {

			if (*it2 - borrow >= *it1) {
				this->number.push_front(*it2 - *it1 - borrow);
				borrow = 0;
			}
			else if (*it2 - borrow < *it1) {
				this->number.push_front((*it2 + 10) - *it1 - borrow);
				borrow = 1;
			}

			it1--;
			it2--;
		}
		//////
		if (*it2 - borrow >= *it1) {
			this->number.push_front(*it2 - *it1 - borrow);
			borrow = 0;
		}
		else if (*it2 - borrow < *it1) {
			this->number.push_front((*it2 + 10) - *it1 - borrow);
			borrow = 1;
		}
		//////
		while (it2 != nr2.number.begin()) {
			it2--;
			this->number.push_front(*it2 - borrow);
			borrow = 0;
		}

	}

	return *this;
}

