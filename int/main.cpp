#include<iostream>
#include<fstream>
#include <string>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimeter "\n--------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS  last_name, first_name, age
#define HUMAN_OS_PARAMETERS(human)  (human).get_last_name()<< " "<< (human).get_first_name()<<" "<<(human).get_age()
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


	
		virtual std::string toString() const
		{
			return last_name + " " + first_name + " " + std::to_string(age);
		}
	
};

#define STUDENT_TAKE_PERAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PERAMETERS speciality, group, rating,  attendance
#define STUDENT_OS_PERAMETERS(student)  (student).get_speciality() << " " << (student).get_group() << " " << (student).get_rating() << " " << (student).get_attendance()

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

#define TEACHER_TAKE_PARAMETRS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETRS speciality, experience
#define TEACHER_OS_PARAMETRS(teacher)  (teacher).get_speciality()<< " " << (teacher).get_experience()

class Teacher :public Human
{
	std::string speciality;
	int experience;
 public:
	const std::string& get_speciality () const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void  set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	Teacher
	   (HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETRS)
		:Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
	    set_experience(experience);
		cout << "TConstructor : \t" << this <<  endl;
	}

	~Teacher()
	{
    cout << "TDestructor : \t" << this << endl;
     }
    
   void info()const override
    {
    Human::info();
    cout << speciality << " " << experience << " " << endl;
    }
};

#define GRADUATE_OS_PARAMETRS(graduate) (graduate).get_subject()
class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PERAMETERS, const std::string& subject)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PERAMETERS)
	{
		this->subject = subject;
		cout << "GConstructor : \t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor : \t " << this << endl;
	}
	void info()const override
	{
		Student::info();
		cout << subject << endl;
	}
};

std::ostream& operator<<(std::ostream& os, const Student& student)
{
	os << HUMAN_OS_PARAMETERS(student) << " " << STUDENT_OS_PERAMETERS(student);
	return os;
}
//std::ostream& operator<<(std::ostream& os, const Human& human)
//{
//	os << HUMAN_OS_PARAMETERS(human) ;
//	return os;		
//}
std::ostream& operator<<(std::ostream& os, const Teacher& teacher)
{
	os << HUMAN_OS_PARAMETERS(teacher) << " " << TEACHER_OS_PARAMETRS(teacher);
	return os;
}
std::ostream& operator<<(std::ostream& os, const Graduate& graduate)
{
	os << HUMAN_OS_PARAMETERS(graduate) << " " << STUDENT_OS_PERAMETERS(graduate) << " " << GRADUATE_OS_PARAMETRS(graduate);
	return os;
}
std::ostream& operator<<(std::ostream& os, const Human& human) {
	os << human.toString();
	return os;
}


//#define INHERITANCE
#define POLYMORPHISM
//#define OPERATOR<<
void main()
{
	setlocale(LC_ALL, " ");

#ifdef INHERITANCE
	Human human("Montana", "Antonio", 25);
	human.info();
	cout << delimeter << endl;
	Student student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99);
	student.info();
	cout << delimeter << endl;
	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.info();
	cout << delimeter << endl;
	Graduate graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg");
	graduate.info();
	cout << delimeter << endl;

#endif // INHERITANCE

#ifdef POLYMORPHISM
	Human *group[] =
	{
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Student("Vercetty","Tommy",30,"Theft","vice",98,99),
		new Teacher ("White", "Walter", 50, "Chemistry", 25),
		new Graduate ("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg"),
        new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};
	cout << delimeter << endl;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->info();
		cout << delimeter << endl;
	}

#endif // POLYMORPHISM
#ifdef OPERATOR<<
	cout << human << endl;
	cout << delimeter << endl;
	cout << student << endl;
	cout << delimeter << endl;
	cout << teacher << endl;
	cout << delimeter << endl;
	cout << graduate << endl;
	cout << delimeter << endl;

#endif // OPERATOR<<

	std::ofstream fout;
	
	
	fout.open("File.txt");
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//group[i]->info();
		cout <<  group[i] << std::endl;
		fout <<  *group[i]<< endl;
	}
	fout.close(); 

	system("notepad File.txt");

	std::ifstream fin("File.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			//fin >> sz_buffer;
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
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];

	}

}