#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimeter "\n--------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS  last_name, first_name, age
#define HUMAN_TAKE_RAND  std::string last_name, first_name;int age;
class Human
{
	static const int TYPE_WIDTH = 10;
	static const int LAST_NAME_WIDTH = 16;
	static const int FIRST_NAME_WIDTH = 10;
	static const int AGE_WIDTH = 3;
	static int count;
	std::string last_name;
	std::string first_name;
	int age;
public:
	static int get_count()
	{
		return count;
	}

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
		this->first_name = first_name;
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
		count++;
		cout << "HConstructor : \t" << this << endl;
	}
	virtual~Human()
	{
		count--;
		cout << "HDestructor : \t" << this << endl;
	}
	// Method
	virtual std::ostream& info(std::ostream& os)const
	{
		os.width(TYPE_WIDTH);
		os << std::left;

		os << std::string(typeid(*this).name() + 6) + ":";
		os.width(LAST_NAME_WIDTH);
		os << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}
	virtual std::istream& scan(std::istream& is)
	{
		return is >> last_name >> first_name >> age;
	}
};
int Human::count = 0;
std::ostream& operator << (std::ostream& os, const Human& obj)
{
	return obj.info(os);
	//return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age();
}
std::istream& operator >>(std::istream& is, Human& obj)
{
	return obj.scan(is);
}
#define STUDENT_TAKE_PERAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_TAKE_RAND std::string speciality, group; double rating; double attendance;
#define STUDENT_GIVE_PERAMETERS speciality, group, rating, attendance

class Student :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 5;
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
	(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PERAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_group(group);
		set_attendance(attendance);
		set_raitng(rating);
		set_speciality(speciality);
		cout << "SConstructor : \t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor : \t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RATING_WIDTH);
		os << rating;
		os.width(RATING_WIDTH);
		os << attendance;
		return os;

		//return os << speciality << " " << group << " " << rating << " " << attendance ;
	}
	std::istream& scan(std::istream& is)override
	{
		char* buffer = new char[SPECIALITY_WIDTH + 2];

		return Human::scan(is) >> speciality >> group >> rating >> attendance;
	}
};

#define TEACHER_TAKE_PARAMETRS const std::string& speciality, int experience
#define TEACHER_TAKE_RAND std::string speciality; int experience;
#define TEACHER_GIVE_PARAMETRS speciality, experience


class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int EXPERIENCE_WIDTH = 3;
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality() const
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
		cout << "TConstructor : \t" << this << endl;
	}

	~Teacher()
	{
		cout << "TDestructor : \t" << this << endl;
	}

	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(EXPERIENCE_WIDTH);
		os << experience;
		return os;
		// return os << speciality << " " << experience ;
	}
	std::istream& scan(std::istream& is)override
	{
		char* buffer = new char[SPECIALITY_WIDTH + 1];
		is.read(buffer, SPECIALITY_WIDTH);
		buffer[SPECIALITY_WIDTH] = '\0'; // завершаем строку
		speciality = std::string(buffer);
		delete[] buffer;
		return is;
		
	}
};
class Graduate :public Student
{
	std::string subject;
public:
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
	std::ostream& info(std::ostream& os)const override
	{
		Student::info(os) << " ";
		return os << subject;
	}
	std::istream& scan(std::istream& is)override
	{
		return std::getline(Student::scan(is), subject);
	}
};
void Print(Human* group[], const int n)
{
	cout << delimeter << endl;
	cout << typeid(group).name() << endl;
	for (int i = 0; i < n; i++)
	{
		cout << (*group[i]) << endl;
	}
	cout << delimeter << endl;
	cout << " Колличество людей :" << group[0]->get_count() << endl;
}

Human* FillRand(const std::string& type)
{
	Human* human = nullptr;
	if (type == "Human") 
	{
		HUMAN_TAKE_RAND;
		cout << "Введите фамилию, имя, возраст: " << endl;
		cin >> last_name  >> first_name >> age;
		return new Human(HUMAN_GIVE_PARAMETERS);
	}
	if (type == "Student")
	{
		HUMAN_TAKE_RAND; STUDENT_TAKE_RAND;
		cout << "Введите фамилию, имя, возраст, специальность, группу, рейтинг, посещаемость: " << endl;
		cin >> last_name >> first_name >> age >> speciality >> group >> rating >> attendance;
		return new Student(HUMAN_GIVE_PARAMETERS,STUDENT_GIVE_PERAMETERS);
	}
	
	if (type == "Teacher")
	{
		HUMAN_TAKE_RAND; TEACHER_TAKE_RAND;
		cout << "Введите фамилию, имя, возраст, специальность, опыт: " << endl;
		cin >> last_name >> first_name >> age >> speciality >> experience;
		return new Teacher(HUMAN_GIVE_PARAMETERS, TEACHER_GIVE_PARAMETRS);
	}
    if (type == "Graduate")
	{
		HUMAN_TAKE_RAND; STUDENT_TAKE_RAND;
		std::string subject;
		cout << "Введите фамилию, имя, возраст, специальность, группу, рейтинг, посещаемость, предмет диплома: " << endl;
		cin >> last_name >> first_name >> age >> speciality >> group >> rating >> attendance >> subject;
		return new Graduate(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PERAMETERS,subject);
	}
		return nullptr;
	
}

Human* HumanFactory(const std::string& type)
{
	Human* human = nullptr;
	if (strstr(type.c_str(), "Human")) human = new Human("", "", 0);
	if (strstr(type.c_str(), "Student")) human = new Student("", "", 0, "", "", 0, 0);
	if (strstr(type.c_str(), "Graduate")) human = new Graduate("", "", 0, "", "", 0, 0, "");
	if (strstr(type.c_str(), "Teacher"))human = new Teacher("", "", 0, "", 0);
	return human;
}

void EnterData(Human* group[], int& n, const int max_size)
{
	while (n < max_size)
	{
		std::string type;
		cout << "Введите тип объекта (Human, Student, Teacher, Graduate), или 'exit' для завершения: ";
		cin >> type;
		if (type == "exit")
			break;
		Human* obj = FillRand(type);
		if (obj)
		{
			group[n] = obj;
			n++;
		}
		else
		{
			cout << "Объект не создан, попробуйте снова.\n";
		}
		char choice;
		cout << "Добавить еще? (y/n): ";
		cin >> choice;
		if (choice != 'y' && choice != 'Y') break;
	}
}

void Save(Human** group, const int n, const char filename[])
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	char cmd[FILENAME_MAX] = "notepad ";
	system((std::string(" start notepad ") + filename).c_str());
}

void PrintFile(const char* filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Не удалось открыть файл " << filename << endl;
		return;
	}
	std::string line;
	while (std::getline(fin, line))
	{
		cout << line << endl;
	}
	fin.close();
}

void Clear(Human** group, const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}



//#define INHERITANCE
//#define POLYMORPHISM
#define WRITH_TO_FILE
//#define LOAD_TO_FILE
void main()
{
	setlocale(LC_ALL, "");

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
	Human* group[] =
	{
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Student("Vercetty","Tommy",30,"Theft","vice",98,99),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg"),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20),
		new Graduate("Targarian", "Daineris", 22, "Flight", "GoT", 91, 92, "How to make smoke"),
		new Teacher("Schwartzneger", "Arnold", 85, "Heavy Metal", 60)
	};
	char filename[] = "group.txt";
	std::ofstream fout(filename);
	cout << delimeter << endl;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
		fout << *group[i] << endl;
		cout << delimeter << endl;
	}
	fout.close();
	char cmd[FILENAME_MAX] = "notepad ";
	system((std::string(" start notepad ") + filename).c_str());
	cout << " Колличество людей :" << group[0]->get_count() << endl;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
	cout << " Колличество людей :" << group[0]->get_count() << endl;

#endif // POLYMORPHISM

#ifdef WRITH_TO_FILE

	const int MAX_GROUP_SIZE = 20;
	Human* group[MAX_GROUP_SIZE] = {};
	int n = 0;
	EnterData(group, n, MAX_GROUP_SIZE);
	Save(group, n, "group.txt");
	Print(group, n);
	Clear(group, n);

#endif // WRITH_TO_FILE

#ifdef LOAD_TO_FILE

	PrintFile("group.txt");
	cout << "\n=================================\n" << endl;

#endif // LOAD_TO_FILE

	}
	