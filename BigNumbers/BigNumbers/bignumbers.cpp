#include <iostream>
#include <string>
//#include <vector>
#include "bignumbers.h"

using namespace std;

//Default constructor
BigNumber::BigNumber() {
	//General Presets
	sign = '+';
	exp = 0;
	valid = 1;
}

//General Constructor
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
	int counter = 0;
	for (; i < nr.length(); i++) {
		//check if the number is valid
		if ((nr[i] > '9' || nr[i] < '0') && nr[i] != 'e') {
			valid = 0;
		}

		//check if the number type is scientific, and it got to the exponent
		if (nr[i] == 'e'){
			exponent = 1;
			int j = i - 1;
			i++;
			//Check how many zeroes there are before e
			while (nr[j] == '0') {
				counter++;
				j--;
			}
		}

		//register the number, or the exponent 
		if (exponent == 0) {
			mantis.push_back(nr[i] - '0');
		}
		else { 
			exp = exp * 10 + (nr[i] - '0');
		}
	}
	//Add the number of 0's from the mantis to the exp
	//Pop mantis 0's

	if (exponent == 0) {
		i = nr.length() - 1;
		while (nr[i] == '0') {
			mantis.pop_back();
			exp++;
			i--;
		}
	}
	else {
		exp += counter;
		//Pop mantis 0's
		while (counter) {
			mantis.pop_back();
			counter--;
		}
	}

	//Construct the number from mantis and exponent for normal representation
	//We add to the number all the elements of the mantis
	for (auto it = mantis.begin(); it != mantis.end(); it++) {
		number.push_back(*it);
	}

	//And we add 0's acordingly to the exponent
	for (int i = 0; i < exp; i++) {
		number.push_back(0);
	}

}

//Type conversion constructor
BigNumber::BigNumber(int nr) {
	//Get the sign
	if (nr >= 0) {
		sign = '+';
	}
	else {
		sign = '-';
	}

	//Construct the std::vector from the int number
	while (nr != 0) {
		int c = nr % 10;
		number.push_front(c);
		nr /= 10;
	}

	exp = 0;
	valid = 1;

	to_scientific();

}

BigNumber::BigNumber(char ch) {
	//For a char, the sign is always +
	sign = '+';

	//Convert from char to int
	int nr = static_cast<int>(ch);
	
	//Construct
	while (nr != 0) {
		int c = nr % 10;
		number.push_front(c);
		nr /= 10;
	}

	exp = 0;
	valid = 1;

	to_scientific();

}

//Copy constructor
BigNumber::BigNumber(BigNumber &n1) {
	//Copy all the data
	number = n1.number;
	mantis = n1.mantis;
	sign = n1.sign;
	exp = n1.exp;
	valid = n1.valid;

}

void BigNumber::print_normal() const {
	
	bool extra = true;

	//We check the validity of the number
	if (valid == 0) {
		cout << "Imposible to print an invalid number \n";
	}
	else {
		//Get the sign
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

void BigNumber::print_scientific() const{

	if (valid == 0) {
		cout << "Imposible to print an invalid number \n";
	}
	
	cout << sign;
	for (auto it = mantis.begin(); it != mantis.end(); it++) {
		cout << *it;
	}
	cout << "e" << exp;


	cout << endl;
}

void BigNumber::to_scientific() {

	if (exp == 0) { 
		mantis.clear();
		deque<int>::reverse_iterator end = number.rend();
		deque<int>::reverse_iterator it = number.rbegin();

		while (*it == 0 && it != end) {
			exp++;
			it++;
		}

		while (it != end) {
			mantis.push_front(*it);
			it++;
		}

	}

}

const deque<int> &BigNumber::getnumber() const{
	return number;
}

deque<int> &BigNumber::setnumber() {
	return number;
}

char BigNumber::getsign() const {
	return sign;
}

void BigNumber::setsign(char sgn) {
	sign = sgn;
}

BigNumber &BigNumber::addition(BigNumber& nr1, BigNumber& nr2) {

	//Value to store which number is bigger
	int bigger;

	//Get the bigger number, by checking, in order
	//	-the largest number
	if (nr1.number.size() > nr2.number.size()) {
		this->sign = nr1.sign;
		bigger = 1;
	}
	else if (nr1.number.size() < nr2.number.size()) {
		this->sign = nr1.sign;
		bigger = 2;
	}
	//	-which number has the biggest first
	else if (nr1.number.size() == nr2.number.size()) {
		if (nr1.number[0] > nr2.number[0]) {
			this->sign = nr1.sign;
			bigger = 1;
		}
		else if (nr1.number[0] < nr2.number[0]) {
			this->sign = nr2.sign;
			bigger = 2;
		}
		//	-if all of the above fails, the entire number
		else if (nr1.number[0] == nr2.number[0]) {
			auto it1 = nr1.number.begin();
			auto it2 = nr2.number.begin();
			while (it1!=nr1.number.end()) {
				if (*it1 > *it2) {
					this->sign = nr1.sign;
					bigger = 1;
					break;
				}
				else if(*it1 < *it2){
					this->sign = nr2.sign;
					bigger = 2;
					break;
				}
				it1++;
				it2++;
			}
		}
	}

	//We have three cases for adding two numbers
	//	-when we add two positives or two negatives, we just add the absolute value and the sign remains the same
	if ((nr1.sign == '+' && nr2.sign == '+') || (nr1.sign == '-' && nr2.sign == '-')) {
		auto it1 = nr1.number.rbegin();
		auto it2 = nr2.number.rbegin();
		int carry = 0;
		while (it1 != nr1.number.rend() && it2 != nr2.number.rend()) {

			this->number.push_front((*it1 + *it2 + carry) % 10);
			if ((*it1 + *it2 + carry) / 10 > 0) {
				carry = 1;
			}
			else {
				carry = 0;
			}


			it1++;
			it2++;
		}	
		if (nr1.number.size() > nr2.number.size()) {
			while (it1 != nr1.number.rend()) {
				this->number.push_front(*it1 + carry);
				carry = 0;
				it1++;
			}
		}else if (nr1.number.size() < nr2.number.size()) {
			while (it2 != nr2.number.rend()) {
				this->number.push_front(*it2 + carry);
				carry = 0;
				it2++;
			}
		}
		if (carry == 1) {
			this->number.push_front(1);
		}
	}
	//	-when the first one is bigger, substract from the first one the second one, and keep the first's sign
	else if (bigger == 1) {
		auto it1 = nr1.number.rbegin();
		auto it2 = nr2.number.rbegin();
		int borrow = 0;
		while (it1 != nr1.number.rend() && it2 != nr2.number.rend()) {

			if (*it1 - borrow >= *it2) {
				this->number.push_front(*it1 - *it2 - borrow);
				borrow = 0;
			}
			else if (*it1 - borrow < *it2) {
				this->number.push_front((*it1 + 10) - *it2 - borrow);
				borrow = 1;
			}

			it1++;
			it2++;
		}

		while (it1 != nr1.number.rend()) {
			this->number.push_front(*it1 - borrow);
			borrow = 0;
			it1++;
		}

	}
	//	-when the second one is bigger, substract from the second one the first one, and keep the second's sign
	else if (bigger == 2) {
		auto it1 = nr1.number.rbegin();
		auto it2 = nr2.number.rbegin();
		int borrow = 0;
		while (it1 != nr1.number.rend() && it2 != nr2.number.rend()) {

			if (*it2 - borrow >= *it1) {
				this->number.push_front(*it2 - *it1 - borrow);
				borrow = 0;
			}
			else if (*it2 - borrow < *it1) {
				this->number.push_front((*it2 + 10) - *it1 - borrow);
				borrow = 1;
			}

			it1++;
			it2++;
		}
		while (it2 != nr2.number.rend()) {
			this->number.push_front(*it2 - borrow);
			borrow = 0;
			it2++;
		}

	}

	return *this;
}

BigNumber operator+(BigNumber const& nr1, BigNumber const& nr2){

	int bigger;
	BigNumber nr;

	//For logic, see addition function
	if (nr1.getnumber().size() > nr2.getnumber().size()) {
		nr.setsign(nr1.getsign());
		bigger = 1;
	}
	else if (nr1.getnumber().size() < nr2.getnumber().size()) {
		nr.setsign(nr2.getsign());
		bigger = 2;
	}
	else if (nr1.getnumber().size() == nr2.getnumber().size()) {
		if (nr1.getnumber()[0] > nr2.getnumber()[0]) {
			nr.setsign(nr1.getsign());
			bigger = 1;
		}
		else if (nr1.getnumber()[0] < nr2.getnumber()[0]) {
			nr.setsign(nr2.getsign());
			bigger = 2;
		}
		else if (nr1.getnumber()[0] == nr2.getnumber()[0]) {
			auto it1 = nr1.getnumber().begin();
			auto it2 = nr2.getnumber().begin();
			while (it1 != nr1.getnumber().end()) {
				if (*it1 > *it2) {
					nr.setsign(nr1.getsign());
					bigger = 1;
				}
				else if (*it1 < *it2) {
					nr.setsign(nr2.getsign());
					bigger = 2;
				}
				it1++;
				it2++;
			}
		}
	}

	if ((nr1.getsign() == '+' && nr2.getsign() == '+') || (nr1.getsign() == '-' && nr2.getsign() == '-')) {
		auto it1 = nr1.getnumber().rbegin();
		auto it2 = nr2.getnumber().rbegin();
		int carry = 0;
		while (it1 != nr1.getnumber().rend() && it2 != nr2.getnumber().rend()) {

			nr.setnumber().push_front((*it1 + *it2 + carry) % 10);
			if ((*it1 + *it2 + carry) / 10 > 0) {
				carry = 1;
			}
			else {
				carry = 0;
			}


			it1++;
			it2++;
		}
		if (nr1.getnumber().size() > nr2.getnumber().size()) {
			while (it1 != nr1.getnumber().rend()) {
				nr.setnumber().push_front(*it1 + carry);
				carry = 0;
				it1++;
			}
		}
		else if (nr1.getnumber().size() < nr2.getnumber().size()) {
			while (it2 != nr2.getnumber().rend()) {
				nr.setnumber().push_front(*it2 + carry);
				carry = 0;
				it2++;
			}
		}
		if (carry == 1) {
			nr.setnumber().push_front(1);
		}
	}
	else if (bigger == 1) {
		auto it1 = nr1.getnumber().rbegin();
		auto it2 = nr2.getnumber().rbegin();
		int borrow = 0;
		while (it1 != nr1.getnumber().rend() && it2 != nr2.getnumber().rend()) {

			if (*it1 - borrow >= *it2) {
				nr.setnumber().push_front(*it1 - *it2 - borrow);
				borrow = 0;
			}
			else if (*it1 - borrow < *it2) {
				nr.setnumber().push_front((*it1 + 10) - *it2 - borrow);
				borrow = 1;
			}

			it1++;
			it2++;
		}

		while (it1 != nr1.getnumber().rend()) {
			nr.setnumber().push_front(*it1 - borrow);
			borrow = 0;
			it1++;
		}

	}
	else if (bigger == 2) {
		auto it1 = nr1.getnumber().rbegin();
		auto it2 = nr2.getnumber().rbegin();
		int borrow = 0;
		while (it1 != nr1.getnumber().rend() && it2 != nr2.getnumber().rend()) {

			if (*it2 - borrow >= *it1) {
				nr.setnumber().push_front(*it2 - *it1 - borrow);
				borrow = 0;
			}
			else if (*it2 - borrow < *it1) {
				nr.setnumber().push_front((*it2 + 10) - *it1 - borrow);
				borrow = 1;
			}

			it1++;
			it2++;
		}
		while (it2 != nr2.getnumber().rend()) {
			nr.setnumber().push_front(*it2 - borrow);
			borrow = 0;
			it2++;
		}

	}

	return nr;
}
