#pragma once
#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Int {
public:
	vector<int> val;
	bool sign;
public:
	//Khoi tao
	Int();
	Int(string s);
	Int(int n);

	//Ham ho tro

	Int doubled() const;
	Int halved(int&) const;
	Int tenfold(int k) const;
	Int tenth(int k) const;
	bool isNegative() const;
	bool isOdd() const;
	int length() const;

	//Toan tu
	Int operator +(const Int&) const;
	Int operator -(const Int&) const;
	operator string() const;
	Int operator <<(int k) const;
	Int operator !() const;
	Int operator ~() const;
	bool operator == (const Int& n) const;
	bool operator != (const Int& n) const;
	bool operator > (const Int& n) const;
	bool operator < (const Int& n) const;
	bool operator >= (const Int& n) const;
	bool operator <= (const Int& n) const;
	int operator[](int i) const;
};