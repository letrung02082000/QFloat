#include "QFloat.h"

QFloat::QFloat() {
	for (int i = 0; i < 4; ++i) {
		this->data[i] = 0;
	}
}

//Nhap so thap phan tu ban phim vao x
void QFloat::ScanQFloat(QFloat& x) {
	string s;
	cin >> s;
	x.stringToQFloat(s);
}

//Xuat so thap phan ra man hinh
void QFloat::PrintQFloat(QFloat x) {
	cout << x.QFloatToStrDec();
}

//Chuyen chuoi so thap phan ve chuoi nhi phan
string QFloat::decToBin(string s) {
	QFloat x;
	x.stringToQFloat(s);
	string dec;
	for (int i = 0; i < 128; ++i) {
		dec += to_string(x.getBit(x.data[i / 32], i % 32));
	}
	return dec;
}

//Chuyen chuoi nhi phan ve chuoi thap phan
string QFloat::binToDec(string s) {
	QFloat x;
	for (int i = 0; i < 128; ++i) {
		if (s[i] == '1') {
			x.setBit(x.data[i / 32], i % 32);
		}
	}
	return x.QFloatToStrDec();
}

//Nhap so thap phan tu chuoi s vao x
void QFloat::stringToQFloat(string s) {
	if (s == "Inf" || s=="-Inf") {
		for (int i = 1; i < 16; ++i) {
			setBit(data[0], i % 32);
		}
		if (s[0] == 'I') {
			setBit(data[0], 0);
		}
	}
	else if (s == "NaN") {
		for (int i = 1; i < 16; ++i) {
			setBit(data[0], i % 32);
		}
		if (s[0] == 'I') {
			setBit(data[0], 0);
		}
		setBit(data[3], 15);
	}
	else if (isZeroStr(s)) {
		*this = QFloat();
	}

	int exp = 0;
	//Set phan dau
	if (s[0] == '-') {
		setBit(data[0], 0);
		s.erase(0, 1);
	}
	string res = toBit(s, exp);

	//Set phan mu
	for (int i = 1; i <= 15; ++i) {
		if (getBit(exp, 31 - 15 + i))
			setBit(data[0], i);
	}
	//Set phan tri
	for (int i = 16; i < 128; ++i) {
		if (res[i - 15] - '0') {
			setBit(data[i / 32], i % 32);
		}
	}
}

string QFloat::QFloatToStrDec() {
	if (isInf()) {
		return "Inf";
	}
	if (isNaN())
		return "NaN";
	if (isZero())
		return "0";
	
	//Lay dau
	bool sign = getBit(data[0], 0);
	//Lay phan mu
	int exp = 0;
	for (int i = 15; i >= 1; i--) {
		exp += getBit(data[0], i) * (1 << (15 - i));
	}
	exp -= (1 << 14) - 1;
	int i = 0;
	//Lay phan tri
	//Kiem tra so khong chuan
	if (exp == -(1 << 14) + 1) {
		exp = -(1 << 14) + 2;
		return "DenormalizedNumber";
	}
	//Tim 2^i dau tien
	int d = exp - i;
	Float t(1);
	if (d < 0) t = t << -d;
	else t = t << d;
	Float s(0);
	s = s + t;
	cout << "a";
	++i;
	while (i < 113) {
		t = t >> 1;
		if (getBit(data[(i+15) / 32], (i+15) % 32)) s = s + t;
		++i;
	}
	if (sign) s = ~s;
	string res = string(s);
	return res;
}

// Ham ho tro

void QFloat::setBit(int& x, int i) {
	x = x | (1 << (31 - i));
}

int QFloat::getBit(int x, int i) {
	return (x >> (31 - i)) & 1;
}


//Chuyen chuoi thap phan ve chuoi nhi phan va luu so mu o dang so qua K vao exp
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
	//Chuyen phan nguyen ve chuoi nhi phan
	in = toBin(in);
	//So qua K =  2^14 - 1
	int k = (1 << 14) - 1;
	//Chuyen phan thap phan ve chuoi nhi phan
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

//Chia chuoi thap phan cho 2
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

//Chuyen chuoi so nguyen ve chuoi nhi phan
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

//Nhan phan thap phan cho 2
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
	else {
		for (int i = len - 1; i >= 0; --i) {
			temp = (s[i] - 48) * 2 + carry;
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

// So 0
bool QFloat::isZero() {
	for (int i = 0; i < 4; ++i)
		if (data[i] != 0)
			return false;
	return true;
}

// So vo cung
bool QFloat::isInf() {
	for (int i = 1; i <= 15; ++i)
		if (getBit(data[0], i%32) != 1)
			return false;
	for (int i = 16; i<128; ++i)
		if (getBit(data[i/32],i%32) != 0)
			return false;
	return true;
}

// So NaN
bool QFloat::isNaN() {
	for (int i = 1; i <= 15; i++)
		if (getBit(data[0], i%32) != 1)
			return false;
	for (int i = 16; i < 128; i++)
		if (getBit(data[i/32],i%32) != 0)
			return true;
	return false;
}

bool QFloat::isZeroStr(string s) {
	int pos = s.find('.');
	int len = s.length();
	if (pos != string::npos) {
		for (int i = 0; i < pos; ++i)
			if (s[i] != '0') return false;
		for (int i = pos + 1; i < len; ++i)
			if (s[i] != '0') return false;
	}
	else {
		for (int i = 0; i < len; ++i)
			if (s[i] != '0') return false;
	}
	return true;
}