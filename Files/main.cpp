#include<iostream>
#include<fstream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimetr "\n--------------------------------\n"

//#define WRITE_TO_FILE
//#define READ_FROM_FILE



void main()
{
	setlocale(LC_ALL, " ");


#ifdef WRITE_TO_FILE

	std::ofstream fout;
	fout.open("File.txt", std::fstream::app);
	fout << "Hello Files!" << endl;
	fout.close();

	system("notepad Files.txt");

#endif // WRITE_TO_FILE

	//std::ifstream fin("File.txt");
	//if (fin.is_open())
	//{
	//	while (!fin.eof())
	//	{
	//		const int SIZE = 256;
	//		char sz_buffer[SIZE] = {};
	//		fin >> sz_buffer;
	//		fin.getline(sz_buffer, SIZE);
	//		cout << sz_buffer << endl;
	//	}
	//	fin.close();
	//}
	//else
	//{
	//	std::cerr << "error" << endl;
	//}


	char str[] = "Hello World";
	cin.read(str, 5);
	cout << str;

}