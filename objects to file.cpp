
#include <fstream>
#include "objects to file.h"

using namespace std;

//---------------------string-------------------------

ofstream& operator << (ofstream& out, const string& str)
{
	int len = str.length();

	//fout.write((const char*)&len, sizeof(len)); // Запись длины, приведение Си
	out.write(reinterpret_cast<char*>(&len), sizeof(len));// Запись длины, приведение С++
	out.write(str.c_str(), len);  // Запись данных

	return out;
}

ifstream& operator >> (ifstream& in, string& str)
{
	int len;								// Переменная для длины
	in.read((char*)&len, sizeof(len));		// Чтение длины записанной строки

	str.resize(len);
	in.read(const_cast<char*>(str.c_str()), len);// снятие const

	return in;
}

//---------------------vector-------------------------
ofstream& operator << (ofstream& out, const vector<int>& arr)
{
	int s = arr.size();

	out.write(reinterpret_cast<char*>(&s), sizeof(s));// Запись длины, приведение С++
	out.write((const char*)&arr[0], arr.size() * sizeof(arr[0]));

	return out;
}

ifstream& operator >> (ifstream& fin, vector<int>& arr)
{
	int s;
	fin.read((char*)&s, sizeof(s));
	arr.resize(s); // выделение памяти 
	fin.read((char*)&arr[0], arr.size() * sizeof(arr[0]));
	return fin;
}

//---------------------list-------------------------

ofstream& operator << (ofstream& fout, const list<string>& lst)
{
	int s = lst.size();
	fout.write((const char*)&s, sizeof(s));
	for (auto v : lst)
	{
		fout << v;
	}
	return fout;
}

ifstream& operator >> (ifstream& fin, list<string>& lst)
{
	int s;
	fin.read((char*)&s, sizeof(s));
	string tmp;
	for (int i = 0; i < s; i++)
	{
		fin >> tmp;
		lst.push_back(tmp);
	}
	return fin;
}