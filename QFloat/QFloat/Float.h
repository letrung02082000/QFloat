#pragma once
#include <algorithm>
#include <cmath>
#include "Int.h"


class Float {
public:
	Int data;
	int exp;
public:
	//Ham khoi tao mac dinh
	Float() {
		data = Int();
		exp = 0;
	}
	//Khoi tao tu 1 so nguyen
	Float(int n) {
		data = Int(n);
		exp = 0;
	}
	
	//Ep kieu string
	operator string() {
		string s = string(data);

		bool sign = (s[0] == '-');

		if (sign)
			s.erase(0, 1);

		int n = s.size();
		while (exp > s.size())
			s = '0' + s;

		if (exp >= n)
			s = "0." + s;
		else if (exp > 0) {
			s.insert(s.begin() + n - exp, '.');
		}

		if (sign)
			s.insert(s.begin(), '-');

		return s;
	}

	//Cac toan tu = + << >> ~
	Float& operator = (const Float& num) {
		data = num.data;
		exp = num.exp;
		return (*this);
	}

	Float operator + (const Float& num) {
		Float a, b, s;
		s.exp = max(exp, num.exp);

		a.data = data.tenfold(s.exp - exp);
		b.data = num.data.tenfold(s.exp - num.exp);

		s.data = a.data + b.data;
		return s.normalize();
	}

	Float operator << (int k) {
		Float s = *this;
		while (k--) s = s.doubled();
		return s;
	}

	Float operator >> (int k) {
		Float s = *this;
		while (k--) s = s.halved();
		return s;
	}

	Float operator ~() const {
		Float s = *this;
		s.data = ~s.data;
		return s;
	}

	//Ham ho tro

	//Giam 1 nua
	Float halved() {
		Float s = *this;
		if (s.data.isOdd()) {
			s.data = s.data.tenfold(1);
			s.exp++;
		}
		int r;
		s.data = s.data.halved(r);
		return s.normalize();
	}

	//Gap doi len
	Float doubled() {
		Float s = *this;
		s.data = s.data.doubled();
		return s.normalize();
	}

	Float& normalize() {
		int l = 0;
		while (data[l] == 0 && l < exp) l++;

		int k = min(exp, l);
		data = data.tenth(k);
		exp -= k;

		return *this;
	}
};
