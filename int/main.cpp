#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimetr "\n--------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS  last_name, first_name, age
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
	virtual~Human()
	{
		cout << "HDestructor : \t" << this << endl;
	}
	// Method
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
};

#define STUDENT_TAKE_PERAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PERAMETERS speciality, group, rating,  attendance

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
	(HUMAN_TAKE_PARAMETERS,STUDENT_TAKE_PERAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
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
	void info()const override
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
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
// Teacher(
//
//
//
//~Teacher()
// cout << "TDestructor : \t" << this << endl;
// 
//void info()const override
// {
// Human::info();
// cout << speciality << " " << experience << " " << endl;
// }
//};
//



//#define INHERITANCE
#define POLYMORPHISM
void main()
{
	setlocale(LC_ALL, " ");

#ifdef INHERITANCE
	Human human("Montana", "Antonio", 25);
	human.info();
	Student student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99);
	student.info();

#endif // INHERITANCE

	Human* group[] =
	{
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Student("Vercetty","Tommy",30,"Theft","vice",98,99)
	};
		cout << delimetr << endl;
		for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
		{
			group[i]->info();
			cout << delimetr << endl;
		}
		for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];

	}




}