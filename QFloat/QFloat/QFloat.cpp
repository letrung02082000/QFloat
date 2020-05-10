#include "QFloat.h"


QFloat::QFloat() {
	for (int i = 0; i < 4; ++i) {
		this->data[i] = 0;
	}
}
//Nhập số thực
void QFloat::ScanQFloat(QFloat& x) {
	string s;
	int exp = 0;
	cin >> s;
	if (s[0] == '-') {
		setBit(x.data[0], 0);
		s.erase(0, 1);
	}
	string res = toBit(s, exp);
	//phần mũ
	for (int i = 1; i <= 15; ++i) {
		if (getBit(exp, 31 - 15 + i))
			setBit(x.data[0], i);
	}
	//phần trị
	for (int i = 16; i < 128; ++i) {
		if (res[i - 15] - '0') {
			setBit(x.data[i / 32], i % 32);
		}
	}

}

void QFloat::PrintQFloat(QFloat x) {

}

// Hàm hỗ trợ

void QFloat::setBit(int& x, int i) {
	x = x | (1 << (31 - i));
}

int QFloat::getBit(int x, int i) {
	return (x >> (31 - i)) & 1;
}

string QFloat::toBit(string s, int& exp) {
	string in, frac, fracBit;
	string res = "";
	
	int pos = s.find('.');
	if (pos == string::npos) {
		in = s;
		frac = "0";
	}
	else {
		in = s.substr(0, pos);
		frac = s.substr(pos);
		frac.insert(frac.begin(), '0');
	}
	in = toBin(in);
	int k = (1 << 14) - 1;
	if (in != "") {
		exp = in.size() + k - 1;
		for (int i = 0; i < (112 - int(in.size() - 1)); ++i) {
			frac = mulFracByTwo(frac);
			fracBit += frac[0];
			frac[0] = '0';
		}
	}
	else {
		int count = 0;
		while (count < k) {
			frac = mulFracByTwo(frac);
			fracBit += frac[0];
			frac[0] = '0';
			if (frac.back() == '1') {
				break;
			}
			++count;
		}
		exp = -(count + 1) + k;
		if (count + 1 < k) {
			for (int i = 0; i < 112; ++i) {
				frac = mulFracByTwo(frac);
				fracBit += frac[0];
				frac[0] = '0';
			}

		}
		else {
			fracBit = "";
			while (exp < 1) {
				frac = mulFracByTwo(frac);
				fracBit += frac[0];
				frac[0] = '0';
				++exp;
			}
		}
	}
	res = in + fracBit;
	while (res.size() < 113) {
		res += '0';
	}
	return res;
}

string QFloat::strDiv2(string s)
{
	string res = s;
	int len = s.length();
	int carry = 0, temp;
	for (int i = 0; i < len; ++i) {
		temp = carry * 10 + (s[i] - '0');
		res[i] = temp / 2 + '0';
		carry = temp % 2;
	}
	while (res[0] == '0') {
		res.erase(0, 1);
	}
	if (res == "") res = "0";
	return res;
}

string QFloat::toBin(string s)
{
	string res = "";
	string temp = s;
	while (temp != "0") {
		int bit = temp.back() % 2;
		if (bit == 1) res = "1" + res;
		else res = "0" + res;
		temp = strDiv2(temp);
	}
	return res;
}

string QFloat::mulFracByTwo(string s)
{
	int len = s.length();
	string res;
	int pos = s.find('.');
	int carry = 0, temp;

	if (pos != string::npos) {
		for (int i = len - 1; i > pos; --i) {
			temp = (s[i] - '0') * 2 + carry;
			if (temp >= 10) {
				res.insert(res.begin(), char(temp - 10 + '0'));
				carry = 1;
			}
			else {
				res.insert(res.begin(), char(temp + '0'));
				carry = 0;
			}
		}
		res.insert(res.begin(), '.');
		for (int i = pos - 1; i >= 0; --i) {
			temp = (s[i] - '0') * 2 + carry;
			if (temp >= 10) {
				res.insert(res.begin(), char(temp - 10 + '0'));
				carry = 1;
			}
			else {
				res.insert(res.begin(), char(temp + '0'));
				carry = 0;
			}
		}
	}
	if (carry == 1) res.insert(res.begin(), char(temp + '0'));
	return res;
}