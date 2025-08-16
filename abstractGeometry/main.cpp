
#include<iostream>
using namespace std;

enum Color	//Enumeration (Перечисление)
{
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Violet = 0x00FF00FF
};

class Shape
{
	Color color;	//цвет фигуры
public:
	void set_color(Color color)
	{
		this->color = color;
	}
	Color get_color()const
	{
		return color;
	}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	Shape(Color color) :color(color) {}
	virtual void info()const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}
};

class Square :public Shape
{
	double side;
public:
	void set_side(double side)
	{
		this->side = side;
	}
	double get_side()const
	{
		return side;
	}
	double get_area()const override
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return side * 4;
	}
	void draw()const override
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	}
	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Сторона квадрата: " << get_side() << endl;
		Shape::info();
	}
};
class Rectangl :public Shape
{
	double side_1;
	double side_2;
public:
	void set_side_1(double side_1)
	{
		this->side_1 = side_1;
	}
	void set_side_2(double side_2)
	{
		this->side_2 = side_2;
	}
	double get_side_1()const
	{
		return side_1;
	}
	double get_side_2()const
	{
		return side_2;
	}


};
void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::Blue);
	Square square(5, Color::Red);
	square.info();
}