#include "Int.h"

Int::Int() {
	sign = false;
}

Int::Int(string s) {
	sign = (s[0] == '-');
	val.resize(s.size() - (sign ? 1 : 0));
	for (int i = s.size() - (sign ? 1 : 0) - 1; i > -1; i--)
		val[i] = s[s.size() - 1 - i] - '0';
	while (val.size() && val.back() == 0) val.pop_back();
	if (val.size() == 0) val.push_back(0);
}

Int::Int(int n) {
	sign = false;
	if (n == 0)
		val.push_back(0);
	else {
		if (n < 0) {
			sign = true;
			n = -n;
		}

		while (n > 0) {
			val.push_back(n % 10);
			n = n / 10;
		}
	}
}

//Toan tu +
Int Int::operator + (const Int& n) const {
	Int a = (*this);
	Int b = n;
	Int c;
	//Neu a khac dau voi b
	if (a.sign ^ b.sign) {
		//Tinh hieu so lon - so be
		if (!a > !b) {
			c = !a - !b;
			c.sign = a.sign;
		}
		else {
			c = !b - !a;
			c.sign = b.sign;
		}
	}
	// Neu a b cung dau thi thuc hien phep cong. Lay dau chung
	else {
		if (a.val.size() > b.val.size()) {
			b.val.resize(a.val.size());
			c.val.resize(a.val.size());
		}
		else {
			a.val.resize(b.val.size());
			c.val.resize(b.val.size());
		}

		int leftover = 0;
		for (int i = 0; i < c.val.size(); i++) {
			leftover = leftover + a.val[i] + b.val[i];
			c.val[i] = (leftover % 10);
			leftover = leftover / 10;
		}

		if (leftover > 0)
			c.val.push_back(leftover);
		c.sign = a.sign;
	}
	return c;
}

// Toan tu -
Int Int::operator - (const Int& n) const {
	Int a = !(*this); bool s1 = this->isNegative();
	Int b = !n; bool s2 = n.isNegative();
	Int c;

	// a>=b thi tra ve a-b
	if (a >= b) {
		b.val.resize(a.val.size());
		c.val.resize(a.val.size());
		int leftover = 0;
		for (int i = 0; i < c.val.size(); i++) {
			leftover = a.val[i] - b.val[i] - leftover;
			if (leftover < 0) {
				c.val[i] = leftover + 10;
				leftover = 1;
			}
			else {
				c.val[i] = leftover;
				leftover = 0;
			}
		}
		while (c.val.size() >= 2 && c.val.back() == 0)
			c.val.pop_back();
	}
	// -(b-a)
	else {
		c = b - a;
		c.sign = ~c.sign;
	}
	return c;
}

// Gap doi len
Int Int::doubled() const {
	return (*this) + (*this);
}

// Dich phai
Int Int::operator <<(int k) const {
	Int s = (*this);
	while (k--)
		s = s.doubled();
	return s;
}

// Giam 1 nua
Int Int::halved(int& rem) const {
	Int c;
	int leftover = 0;
	for (int i = val.size() - 1; i > -1; i--) {
		c.val.push_back((10 * leftover + val[i]) >> 1);
		leftover = (10 * leftover + val[i]) % 2;
	}
	rem = leftover;
	int l = 0, r = c.val.size() - 1;
	while (l < r) {
		swap(c.val[l], c.val[r]);
		l++; r--;
	}
	if (c.val.back() == 0 && c.val.size() > 1) c.val.pop_back();
	c.sign = sign;
	return c;
}

// Gap 10 lan
Int Int::tenfold(int k) const {
	if (k <= 0) return *this;
	Int s = *this;
	s.val.resize(s.val.size() + k);
	int r = s.val.size() - 1;
	while (r > k - 1) {
		s.val[r] = s.val[r - k];
		r--;
	}
	while (r >= 0) {
		s.val[r] = 0;
		r--;
	}
	return s;
}

// Giam 10 lan
Int Int::tenth(int k) const {
	if (k <= 0) return *this;
	Int s = *this;
	s.val.erase(s.val.begin(), s.val.begin() + k);
	if (s.val.size() == 0) s.val.push_back(0);
	return s;
}

// Lay gia tri tuyet doi
Int Int::operator !() const {
	Int s = *this;
	s.sign = false;
	return s;
}

// Lay so doi
Int Int::operator ~() const {
	Int s = *this;
	s.sign = ~s.sign;
	return s;
}


//Ham so sanh
bool Int::operator == (const Int& n) const {
	if (n.sign != sign && val[0] != 0) return false;
	if (n.val.size() != val.size()) return false;
	for (int i = 0; i < val.size(); i++)
		if (val[i] != n.val[i]) return false;
	return true;
}

bool Int::operator != (const Int& n) const {
	return !(*this == n);
}

bool Int::operator > (const Int& n) const {
	if (!sign && n.sign) return true;
	if (sign && !n.sign) return false;

	if (val.size() > n.val.size()) return !sign;
	if (val.size() < n.val.size()) return sign;

	for (int i = val.size() - 1; i > -1; i--) {
		if (val[i] > n.val[i]) return !sign;
		if (val[i] < n.val[i]) return sign;
	}
	return false;
}

bool Int::operator < (const Int& n) const {
	return !(*this > n) && !(*this == n);
}

bool Int::operator >= (const Int& n) const {
	return (*this > n) || (*this == n);
}

bool Int::operator <= (const Int& n) const {
	return !(*this > n);
}

//Ham ho tro
// So am
bool Int::isNegative() const {
	return sign;
}

// SO le
bool Int::isOdd() const {
	return val[0] % 2 != 0;
}

// Do dai
int Int::length() const {
	return val.size();
}


// Lay ky tu thu i
int Int::operator[](int i) const {
	return val[i];
}

// Ep kieu string
Int::operator string() const {
	string s;
	if (sign) s += "-";
	for (int i = val.size() - 1; i > -1; i--)
		s += (val[i] + '0');
	return s;
}