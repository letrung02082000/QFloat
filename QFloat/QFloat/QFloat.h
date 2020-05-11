#pragma once
#include<iostream>
#include<string>
#include"Float.h"

using namespace std;
class QFloat
{
	int data[4];
public:
	// Khoi tao
	QFloat();
	void ScanQFloat(QFloat& x );
	void PrintQFloat(QFloat x);

	// Ham ho tro
	void setBit(int& x, int i);
	int getBit(int x, int i);
	string toBit(string s, int& exp);
	string strDiv2(string s);
	string toBin(string s);
	string mulFracByTwo(string s);
};

