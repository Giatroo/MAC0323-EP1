#ifndef MY_STRING_H
#define MY_STRING_H

#include <ostream>
#include <string>

class MyString {
  public:
	std::string s;

	MyString();
	MyString(std::string);

	bool operator<(const MyString &s1);
	bool operator<=(const MyString &s1);
	bool operator>(const MyString &s1);
	bool operator>=(const MyString &s1);
	bool operator==(const MyString &s1);
	bool operator!=(const MyString &s1);
	void operator=(const MyString &s1);
	friend std::ostream &operator<<(std::ostream &out, const MyString &s1);
	void operator++(int);
	void operator++();
};

MyString::MyString() : s("") {}
MyString::MyString(std::string s) : s(s) {}

bool MyString::operator<(const MyString &s1) { return this->s.compare(s1.s) < 0; }

bool MyString::operator<=(const MyString &s1) { return this->s.compare(s1.s) <= 0; }

bool MyString::operator>(const MyString &s1) { return this->s.compare(s1.s) > 0; }

bool MyString::operator>=(const MyString &s1) { return this->s.compare(s1.s) >= 0; }

bool MyString::operator==(const MyString &s1) { return this->s.compare(s1.s) == 0; }

bool MyString::operator!=(const MyString &s1) { return this->s.compare(s1.s) != 0; }

void MyString::operator=(const MyString &s1) { this->s = s1.s; }

std::ostream &operator<<(std::ostream &out, const MyString &s1) {
	out << s1.s;
	return out;
}

// Do nothing
void MyString::operator++(int) {}
void MyString::operator++() {}

#endif // !MY_STRING_H