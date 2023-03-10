#pragma once

#include "objects to file.h"

#include <fstream>
using namespace std;

class User
{
	string login;
	string password;
	string name;
	string surname;
	string address;
	string phone;
	string mail;

public:
	User();
	User(string login, string password, string name, string surname, string address, string phone, string mail);
	User(string login) : User(login, "unknown", "unknown", "unknown", "unknown", "unknown", "unknown") {}	//***Делегирующий конструктор


	string get_login()const;
	string get_password()const;
	string get_name()const;

	void set_login(string new_login) { login = new_login; }
	void set_password(string new_password) { password = new_password; }
	void set_name(string new_name) { name = new_name; }
	void set_surname(string new_surname) { surname = new_surname; }
	void set_address(string new_address) { address = new_address; }
	void set_phone(string new_phone) { phone = new_phone; }
	void set_mail(string new_mail) { mail = new_mail; }

	bool operator<(const User& user)const;

	void init(const string& login);

	friend ostream& operator<<(ostream& out, const User& user);
	friend istream& operator>>(istream& in, User& user);

	friend ofstream& operator<<(ofstream& os, const User& user);
	friend ifstream& operator>>(ifstream& is, User& user);
};

