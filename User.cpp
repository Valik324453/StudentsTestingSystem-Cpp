#include "User.h"
#include <iostream>
#include <string>

User::User()
{
	this->login = "no login";
	this->password = "no password";
	this->name = "no name";
	this->surname = "no surname";
	this->address = "no address";
	this->phone = "no phone";
	this->mail = "no mail";
}
User::User(string login, string password, string name, string surname, string address, string phone, string mail)
{
	this->login = login;
	this->password = password;
	this->name = name;
	this->surname = surname;
	this->address = address;
	this->phone = phone;
	this->mail = mail;
}


ostream& operator<<(ostream& out, const User& user)
{
	out << "Логин: " << user.login << endl;
	//out << "Пароль: " << user.password << endl;
	out << "Имя: " << user.name << endl;
	out << "Фамилия: " << user.surname << endl;
	out << "Адрес: " << user.address << endl;
	out << "Телефон: " << user.phone << endl;
	out << "Имэйл: " << user.mail << endl;
	
	return out;
}

istream& operator>>(istream& in, User& user)
{
	cout << "Логин: ";
	getline(in, user.login);
	cout << "Пароль: ";
	getline(in, user.password);
	cout << "Имя: ";
	getline(in, user.name);
	cout << "Фамилия: ";
	getline(in, user.surname);
	cout << "Адрес: ";
	getline(in, user.address);
	cout << "Телефон: ";
	getline(in, user.phone);
	cout << "Имэйл: ";
	getline(in, user.mail);

	return in;
}

void User::init(const string& login)
{
	this->login = login;
	cout << "Пароль: ";
	cin.get();
	getline(cin, password);
	cout << "Имя: ";
	getline(cin, name);
	cout << "Фамилия: ";
	getline(cin, surname);
	cout << "Адрес: ";
	getline(cin, address);
	cout << "Телефон: ";
	getline(cin, phone);
	cout << "Имэйл: ";
	getline(cin, mail);
}

bool User::operator<(const User& user)const
{
	return this->login < user.login;
}

string User::get_login()const
{
	return this->login;
}

string User::get_password()const
{
	return this->password;
}

string User::get_name()const
{
	return this->name;
}
ofstream& operator<<(ofstream& os, const User& user)
{
	os << user.login << user.password << user.name << user.surname << user.address << user.phone << user.mail;
	return os;
}
ifstream& operator>>(ifstream& is, User& user)
{
	is >> user.login >> user.password >> user.name >> user.surname >> user.address >> user.phone >> user.mail;
	return is;
}
