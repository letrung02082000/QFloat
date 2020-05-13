#include"QFloat.h"
#include<fstream>
vector<int> position(string s);
vector<string> whichCase(string s);
int main(int argc, char* argv[]) {
	ifstream inFile(argv[1], ifstream::in);
	ofstream outFile(argv[2], ofstream::out);

	if (!inFile.is_open()) {
		cout << "can't open file!!!" << endl;
		return 0;
	}
	string s;
	while (!inFile.eof()) {
		getline(inFile, s);
		if (s[0] == '\n') {
			s.erase(0, 1);
		}
		vector<string> a = whichCase(s);
		if (a[0] == "10") {
			QFloat x;
			string output;
			output = x.decToBin(a[2]) + "\n";
			outFile << output;
		}
		else if (a[0] == "2") {
			QFloat x;
			string output;
			output = x.binToDec(a[2]) + "\n";
			outFile << output;
		}
	}
}

vector<int> position(string s) {
	int count = 0, idx = 0;
	vector<int> a;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			count++;
			a.push_back(i);
		}
	}
	a.push_back(count);
	return a;

}

vector<string> whichCase(string s) {
	vector<int> b = position(s);
	if (b[b.size() - 1] == 2) {
		vector<string> a;
		a.push_back(s.substr(0, b[0]));
		a.push_back(s.substr(b[0], b[1] - 1));
		a.push_back(s.substr(b[1], s.length()));
		for (int i = 0; i < a.size(); i++) {
			if (a[i][0] == ' ')
				a[i].erase(0, 1);
			if (a[i][a[i].length() - 1] == ' ')
				a[i].erase(a[i].length() - 1);
		}
		return a;
	}
	else {
		vector<string> a;
		a.push_back(s.substr(0, b[0]));
		a.push_back(s.substr(b[0], b[1] - 1));
		a.push_back(s.substr(b[1], b[2] - b[1]));
		a.push_back(s.substr(b[2], s.length()));
		for (int i = 0; i < a.size(); i++) {
			if (a[i][0] == ' ')
				a[i].erase(0, 1);
			if (a[i][a[i].length() - 1] == ' ')
				a[i].erase(a[i].length() - 1);
		}
		return a;
	}
}