#include <iostream>
#include <string>
#include <vector>
#include "bignumbers.h"

using namespace std;

int main() {

	string nr, nr2;
	int option;

	//cout << "1.Let's try and put any number you want\n\t";
	//cin >> nr;
	//{
	//	BigNumber n1(nr);
	//	cout << "\t";
	//	n1.print_normal();
	//}
	//
	//cout << "2.Now, let's try a scientific number (A scientific number of the form\n\t";
	//cin >> nr;
	//{
	//	BigNumber n1(nr);
	//	cout << "\t";
	//	n1.print_normal();
	//}
	//
	//cout << "3.Using the addition function\n";
	//cout << "\tLet's read first number\n\t";
	//cin >> nr;
	//cout << "\tLet's read second number\n\t";
	//cin >> nr2;
	//{
	//	BigNumber n1(nr);
	//	BigNumber n2(nr2);
	//	BigNumber n3;
	//	n3.addition(n1, n2);
	//	cout << "\t";
	//	n3.print_normal();
	//}

	//cout << "4.Using the overloaded operator+\n";
	//cout << "\tLet's read first number\n\t";
	//cin >> nr;
	//cout << "\tLet's read second number\n\t";
	//cin >> nr2;
	//{
	//	BigNumber n1(nr);
	//	BigNumber n2(nr2);
	//	BigNumber n3;
	//	n3 = n1 + n2;
	//	cout << "\t";
	//	n3.print_normal();
	//}


	//cout << "5.Using the conversion constructor from int to BigNumber (Ex: int 15 is gonna be 15 in BigNumber):\n\t";
	//{
	//	int n;
	//	cin >> n;
	//	BigNumber n1(n);
	//	cout << "\t";
	//	n1.print_normal();
	//}

	//cout << "6.Using the conversion constructor from char to BigNumber (Ex: char 'a' is gonna be 97(ASCII));\n\t";
	//{
	//	char n;
	//	cin >> n;
	//	BigNumber n1(n);
	//	cout << "\t";
	//	n1.print_normal();
	//}

	//cout << "7.Using the copy constructor, let's create a number and then copy it to another number\n\t";
	//cin >> nr;
	//{
	//	BigNumber n1(nr);
	//	BigNumber n2(n1);
	//	cout << "\tThe number you created is:\n\t";
	//	n1.print_normal();
	//	cout << "\tThe number copied by our copy constructor is:\n\t";
	//	n2.print_normal();
	//}
	
	cout << "Let's try some diferent number for both scientific and normal\n\t";
	{
		cout << "Number with general constructor\n\t";
		cin >> nr;
		BigNumber n1(nr);
		cout << "\tNormal:\n";
		cout << "\t";
		n1.print_normal();
		cout << "\tScientific\n";
		cout << "\t";
		n1.print_scientific();


		cout << "\nNumber with conversion int->BigNumber constructor\n\t";
		int n;
		cin >> n;
		BigNumber n2(n);
		cout << "\tNormal:\n";
		cout << "\t";
		n2.print_normal();
		cout << "\tScientific\n";
		cout << "\t";
		n2.print_scientific();


		cout << "\nNumber with conversion char->BigNumber constructor\n\t";
		char ch;
		cin >> ch;
		BigNumber n3(ch);
		cout << "\tNormal:\n";
		cout << "\t";
		n3.print_normal();
		cout << "\tScientific\n";
		cout << "\t";
		n3.print_scientific();
	}


	//cout << endl;
	//n3.print_scientific();
}