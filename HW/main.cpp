#include<iostream>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
#define delimeter "\n-----------------------------------\n"



class Human
{
	std::string First_name;
	std::string Last_name;
	int  age;
public:

	const std::string& get_First_name() const { return First_name; }
	const std::string& get_Last_name()const { return Last_name; }
	int get_age() const { return age; }
	void set_First_name(const std::string& First_name) { this->First_name = First_name; }
	void set_Last_name(const std::string& Last_name) { this->Last_name = Last_name;  }
	void set_age(int age) { this->age = age; }
	// Constructor
	Human(const std::string& Last_name, const std::string& First_name, int age)
	{
		set_Last_name(Last_name);
		set_First_name(First_name);
		set_age(age);
		cout << "HConstructor :\t" << this << endl;
	}
	~Human(){cout << "HDestructor :\t" << this << endl;}
	// Method
	void info()const { cout << Last_name << " " << First_name << " " << "Возраст" << " " <<age << endl; }

};
class Student
{





};









void main()
{
	setlocale(LC_ALL, " ");


	Human human("Иванов","Иван", 30);
		human.info();



}