
#include<iostream>
#include<Windows.h>
#include <cmath>

#define M_PI 3.14159265358979323846

using namespace std;



namespace Geometry
{
	enum Color	//Enumeration (Перечисление)
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Violet = 0x00FF00FF
	};
#define SHAPE_TAKE_PARAMETERS int start_x,int start_y,int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

	class Shape
	{
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 800;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 800;


	protected:
	
		int start_x;
		int start_y;
		int line_width;
		Color color;	//цвет фигуры
	public:
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				 start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		double get_start_x()const
		{
			return start_x;
		}
		double get_start_y()const
		{
			return start_y;
		}
		double get_line_width()const
		{
			return line_width;
		}
		Color get_color()const
		{
			return color;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}

		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
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
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Квадрат" << endl;
			cout << "Сторона квадрата: " << get_side() << endl;
			Shape::info();
		}
	};*/
	class Rectangle:public Shape
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
		double get_area()const override
		{
			return side_1 * side_2;
		}

		double get_perimeter()const override
		{
			return (side_1 + side_2) * 2;

		}
		void draw()const override
		{//получаем окно консоли
			HWND hwnd = GetConsoleWindow();
		//получаем на чем будем рисовать
			HDC hdc = GetDC(hwnd);
		// сoздаем карандаш
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + side_1, start_y + side_2);
		// удаляем карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);			
		}
		Rectangle(double side_1, double side_2, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side_1(side_1);
			set_side_2(side_2);
		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1: " << get_side_1() << endl;
			cout << "Сторона 2: " << get_side_2() << endl;
			Shape::info();
		}
	};
	class Triangle :public Shape
	{
			double side_1;
			double side_2;
			double angleDeg; // угол между сторонами в градусах

		public:
			void set_side_1(double side_1) { this->side_1 = side_1; }
			void set_side_2(double side_2) { this->side_2 = side_2; }
			void set_angleDeg(double angleDeg) { this->angleDeg = angleDeg; }

			double get_side_1() const { return side_1; }
			double get_side_2() const { return side_2; }
			double get_angleDeg() const { return angleDeg; }

			// Метод для вычисления площади по двум сторонам и углу
			double get_area() const override
			{
				double angleRad = angleDeg * M_PI / 180;
				return 0.5 * side_1 * side_2 * sin(angleRad);
			}

			double get_side_3() const
			{
				return sqrt(pow(side_1, 2) + pow(side_2, 2) - 2 * side_1 * side_2 * cos(angleDeg * M_PI / 180));
			}
			double get_perimeter()const override { return side_1 + side_2 + get_side_3();}

			void draw() const override
			{
				HWND hwnd = GetConsoleWindow();
				HDC hdc = GetDC(hwnd);
				HPEN hPen = CreatePen(PS_SOLID, line_width, color);
				HBRUSH hBrush = CreateSolidBrush(color);
				SelectObject(hdc, hPen);
				SelectObject(hdc, hBrush);

				POINT A = { start_x, start_y };
				POINT B = { start_x + side_1, start_y };
				double angleRad = get_angleDeg() * M_PI / 180;
				POINT C;
				C.x = start_x + side_2 * cos(angleRad);
				C.y = start_y - side_2 * sin(angleRad); 
				POINT points[3] = { A, B, C };
				Polygon(hdc, points, 3);

				DeleteObject(hPen);
				DeleteObject(hBrush);
				ReleaseDC(hwnd, hdc);
			}

			Triangle(double side_1, double side_2, double angleDeg, SHAPE_TAKE_PARAMETERS)
				:Shape(SHAPE_GIVE_PARAMETERS)
			{
				set_side_1(side_1);
				set_side_2(side_2);
				set_angleDeg(angleDeg);

			}
			void info() const override
			{
				cout << typeid(*this).name() << endl;
				cout << "Сторона 1: " << get_side_1() << endl;
				cout << "Сторона 2: " << get_side_2() << endl;
				cout << "Угол между сторонами : " << get_angleDeg() << endl;
				cout << "Сторона 3 : " << get_side_3() << endl;
				cout << "Площадь по двум сторонам и углу: " << get_area() << endl;
				Shape::info();
			}

	};
	 

		class Square :public Rectangle
		{
		public:
			Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		};

}
void main()
{
	setlocale(LC_ALL, "");

	Geometry::Square square(50, 650, 50, 5, Geometry::Color::Red);
	square.info();
	square.draw();
	cout << "\n";
	
	Geometry::Rectangle rectangle(200, 150, 750, 50, 1, Geometry::Color::Blue);
	rectangle.info();
	rectangle.draw();
	cout << "\n";
	
	Geometry::Triangle triangle(150, 200, 35,750,50, 1, Geometry::Color::Green);
	triangle.info();
	triangle.draw();

	HWND hwnd = GetConsoleWindow();
	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);
	Sleep(5000);
}
