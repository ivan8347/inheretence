#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS  last_name, first_name, age
#define STUDENT_TAKE_PERAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PERAMETERS speciality, group, rating,  attendance
class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const string& first_name)
	{
		this-> first_name = first_name;
	}

	void set_age(int age)
	{
		this->age = age;
	}
	// Construcror
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HDestructor: \t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor : \t" << this << endl;
	}

	// Method
	void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}






};
class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double  get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	 }
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;

	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_raitng(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}




	// constructor

	Student
	(
		HUMAN_TAKE_PARAMETERS,
		STUDENT_TAKE_PERAMETERS
	) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_group(group);
		set_attendance(attendance);
		set_raitng(rating);
		set_speciality(speciality);
		cout << "SConstructor : \t" << this << endl;

	}
	~Student()
	{
		cout << "SDestructor \t" << this << endl;
	}
	void info()const
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}

//public:
//	void info()const
//	{
//		this->
//	}

};
//class Teacher :public Human
//{
//	std::string speciality;
//	int experience;
//public:
//	const std::string& get_speciality ()const
//	{
//		return speciality;
//	}
//	int experience(exception)
//	{
//		return experience;
//	}
//	void  set_speciality(const std::string& speciality)
//	{
//		this->speciality = speciality;
//	}
//	void set_experience(int experience)
//	{
//		this->experience = experience;
//	}
//
//
//
//
//
//
//
//};
//





void main()
{
	setlocale(LC_ALL, " ");

	Human human("Montana", "Antonio", 25);
	human.info();
	Student student("Pinkman", "Jesse", 22, "Chimestry", "WW_220", 95, 99);
	student.info();

}