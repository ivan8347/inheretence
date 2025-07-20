#include<iostream>
#include<fstream>
#include <string>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
#define delimeter "\n-----------------------------------\n"
#define HUMAN_TAKE_PARAMETERS const std::string& Last_name, const std::string& First_name, int age
#define HUMAN_GIVE_PARAMETERS Last_name,First_name, age


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
	void set_Last_name(const std::string& Last_name) { this->Last_name = Last_name; }
	void set_age(int age) { this->age = age; }
	// Constructor
	Human(const std::string& Last_name, const std::string& First_name, int age)
	{
		set_Last_name(Last_name);
		set_First_name(First_name);
		set_age(age);
		cout << "HConstructor :\t" << this << endl;
	}
	virtual ~Human() { cout << "HDestructor :\t" << this << endl; }
	// Method
	virtual void info()const { cout << Last_name << " " << First_name << " " << age<< " " << "лет" << endl; }

	virtual std::string get_ClassName() const { return "Human"; }
	virtual std::string toString() const
	{
		return get_ClassName() + " " + Last_name + " " + First_name + " " + std::to_string(age) + " " + "лет";
	}


};
#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, int rating
#define STUDENT_GIVE_PARAMETERS speciality,group,rating
class Student :public Human
{
	std::string speciality;
	std::string group;
	int rating;
public:
	const std::string& get_speciality() const { return speciality; }
	const std::string& get_group()const{ return group; }
	int get_rating()const { return rating; }
	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_group(const std::string& group) { this->group = group; }
	void set_rating(int rating) { this->rating = rating; }
	
	// Constructor
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		cout << "SConstructor :\t" << this << endl;
	}
		~Student() { cout << "SDestructor :\t" << this << endl; }

		// Method
		void info()const override { Human::info();  cout << speciality << " " << group << " " << rating << "%"<< endl; }
		 std::string get_ClassName() const override { return "Student"; }
		 std::string toString() const override
		{
			return Human::toString() + " " + speciality + " " + group + " " + std::to_string(rating) + "%";
		}

};
#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience
class Teacher :public Human
{ 
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality() const { return speciality; }
	int get_experience()const { return experience; }
	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_experience(int experience) { this->experience = experience; }
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor :\t" << this << endl;
	}
	~Teacher() { cout << "TDestructor :\t" << this << endl; }

	void info()const override { Human::info(); cout << speciality << " " << experience << " " << "лет" << endl; }
	std::string get_ClassName() const override { return "Teacher"; }
	std::string toString() const override
	{
		return Human::toString() + " " + speciality + " " + std::to_string(experience) + " " + "лет";
	}
};



std::ostream& operator<<(std::ostream& os, const Human& human) {
	os << human.toString();
	return os;
}




void main()
{
	setlocale(LC_ALL, "");

	cout << delimeter << endl;
	Human human("Иванов", "Иван", 30);
	human.info();
	cout << delimeter << endl;
	Student student("Петров", "Степан", 45, "Токарь", "БД18", 90);
	student.info();
	cout << delimeter << endl;
	Teacher teacher("Ковтун", "Олег" ,40, "Програмист", 10);
	teacher.info();
	cout << delimeter << endl;

	std::ofstream fout;
	fout.open("File.txt");
	fout << human << endl;
	fout << student << endl;
	fout << teacher << endl;
	fout.close();
	system("notepad File.txt");

	std::ifstream fin("File.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};

			fin.getline(sz_buffer, SIZE);
			cout << delimeter << endl;
			cout << sz_buffer << endl;
		}
		fin.close();
	}
	else
	{
		cout << delimeter << endl;
		std::cerr << "error" << endl;
	}
}