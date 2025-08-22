#include<iostream>
#include<Windows.h>
#include <cmath>
#include<gdiplus.h>
#include <shellapi.h>
#pragma comment(lib, "gdiplus.lib")

using namespace std;
using namespace Gdiplus;
using std::cin;
using std::cout;
using std::endl;
#define M_PI 3.14

ULONG_PTR gdiplusToken;

void InitGDIPlus() {
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void ShutdownGDIPlus() {
    GdiplusShutdown(gdiplusToken);
}

// Функция для получения CLSID кодека
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0, size = 0;
    GetImageEncodersSize(&num, &size);
    if (size == 0) return -1;
    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    GetImageEncoders(num, size, pImageCodecInfo);
    for (UINT i = 0; i < num; ++i) {
        if (wcscmp(pImageCodecInfo[i].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[i].Clsid;
            free(pImageCodecInfo);
            return i;
        }
    }
    free(pImageCodecInfo);
    return -1;
}

namespace Geometry
{
   enum Color
    {
        Red = 0x000000FF,
        Green = 0x0000FF00,
        Blue = 0x00FF0000,
        Yellow = 0xFFFF00,
        Violet = 0x00FF00FF,
        Black = 0x000000
   };  
    
#define SHAPE_TAKE_PARAMETERS int start_x,int start_y,int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
#define FILLCOLOR  255, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF
    class Shape
    {
        static const int MIN_START_X = 100;
        static const int MIN_START_Y = 100;
        static const int MAX_START_X = 800;
        static const int MAX_START_Y = 600;
        static const int MIN_LINE_WIDTH = 1;
        static const int MAX_LINE_WIDTH = 32;

    protected:
        int start_x;
        int start_y;
        int line_width;
        Color color;

    public:
        void set_start_x(int start_x) 
        {
            this->start_x = (start_x < MIN_START_X) ? MIN_START_X :
                (start_x > MAX_START_X) ? MAX_START_X : start_x;
        }
        void set_start_y(int start_y) 
        {
            this->start_y = (start_y < MIN_START_Y) ? MIN_START_Y :
                (start_y > MAX_START_Y) ? MAX_START_Y : start_y;
        }
        void set_line_width(int line_width) 
        {
            this->line_width = (line_width < MIN_LINE_WIDTH) ? MIN_LINE_WIDTH :
                (line_width > MAX_LINE_WIDTH) ? MAX_LINE_WIDTH : line_width;
        }
        void set_color(Color color) 
        {
            this->color = color;
        }
        double get_start_x() const { return start_x; }
        double get_start_y() const { return start_y; }
        double get_line_width() const { return line_width; }
        Color get_color() const { return color; }

        virtual double get_area() const = 0;
        virtual double get_perimeter() const = 0;
        virtual void fill(Graphics* g) const = 0;

        Shape(SHAPE_TAKE_PARAMETERS) : color(color)
        {
            set_start_x(start_x);
            set_start_y(start_y);
            set_line_width(line_width);
        }

        virtual void info() const {
            cout << "Площадь фигуры: " << get_area() << endl;
            cout << "Периметр фигуры: " << get_perimeter() << endl;
        }
    };

    class Rectangle :public Shape {
        double side_1;
        double side_2;
    public:
        void set_side_1(double side_1) { this->side_1 = side_1; }
        void set_side_2(double side_2) { this->side_2 = side_2; }
        double get_side_1() const { return side_1; }
        double get_side_2() const { return side_2; }
        double get_area() const override { return side_1 * side_2; }
        double get_perimeter() const override { return (side_1 + side_2) * 2; }
       
        void fill(Graphics* g) const 
        {
             Gdiplus::Color fillColor(FILLCOLOR);
            SolidBrush brush(fillColor);
            g->FillRectangle(&brush, start_x, start_y, (int)side_1, (int)side_2);
        }
       void draw(Graphics* g) const 
        {
            Gdiplus::Color penColor(FILLCOLOR);
            Pen pen(penColor, line_width);
            g->DrawRectangle(&pen, start_x, start_y, (int)side_1, (int)side_2);
        }
       
        Rectangle(double side_1, double side_2, SHAPE_TAKE_PARAMETERS)
            :Shape(SHAPE_GIVE_PARAMETERS) {
            set_side_1(side_1);
            set_side_2(side_2);
        }

        void info() const override {
            cout << "Rectangle:" << endl;
            cout << "Сторона 1: " << get_side_1() << endl;
            cout << "Сторона 2: " << get_side_2() << endl;
            Shape::info();
           
        }
    };

    class Triangle :public Shape {
        double side_1;
        double side_2;
        double angleDeg; 

    public:
        void set_side_1(double side_1) { this->side_1 = side_1; }
        void set_side_2(double side_2) { this->side_2 = side_2; }
        void set_angleDeg(double angleDeg) { this->angleDeg = angleDeg; }

        double get_side_1() const { return side_1; }
        double get_side_2() const { return side_2; }
        double get_angleDeg() const { return angleDeg; }

        double get_side_3() const 
        {
            return sqrt((side_1 * side_1) + (side_2 * side_2) - 2 * side_1 * side_2 * cos(angleDeg * M_PI / 180));
        }
        double get_area() const override  { return 0.5 * side_1 * side_2 * sin(angleDeg * M_PI / 180); }
        double get_perimeter() const override {return side_1 + side_2 + get_side_3();  }
        void fill(Graphics* g) const 
        {
            Gdiplus::Color fillColor(FILLCOLOR);
            SolidBrush brush(fillColor);
            double side_3 = get_side_3();
          double height = (2 * get_area()) / side_3;
            double angleRad = angleDeg * M_PI / 180;

            PointF points[3];
            points[0] = PointF(start_x, start_y);
            points[1] = PointF(start_x + side_1 * cos(angleRad), start_y + height);
            points[2] = PointF(start_x + side_3, start_y );
            g->FillPolygon(&brush, points, 3);
        }
        void draw(Graphics* g) const 
        {
            double side_3 = get_side_3();
            double height = (2 * get_area()) / side_3;
            double angleRad = angleDeg * M_PI / 180;

            PointF points[3];
            points[0] = PointF(start_x, start_y);
            points[1] = PointF(start_x + side_1 * cos(angleRad), start_y + height);
            points[2] = PointF(start_x + side_3, start_y);
            Gdiplus::Color penColor(255, 0, 0, 0);
            Pen pen(penColor, line_width); 
            g->DrawPolygon(&pen, points, 3);
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
            cout << "Triangle:" << endl;
            cout << "Сторона 1: " << get_side_1() << endl;
            cout << "Сторона 2: " << get_side_2() << endl;
            cout << "Сторона 3 : " << get_side_3() << endl;
            cout << "Угол между сторонами : " << get_angleDeg() << endl;
            Shape::info();
        }
    };

    class Circle : public Shape {
        int radius;
    public:
        void set_radius(double radius) { this->radius = radius; }
        int get_radius() const { return radius; }
        double get_area() const override { return M_PI * (radius * radius); }
        double get_perimeter() const override { return 2 * M_PI * radius; }
        void fill(Graphics* g) const
        {
            Gdiplus::Color fillColor(FILLCOLOR);
            SolidBrush brush(fillColor);
            int x = start_x - radius;
            int y = start_y - radius;
            g->FillEllipse(&brush, x, y, radius * 2, radius * 2);
        }
        void draw(Graphics* g) const  
        {
            Gdiplus::Color penColor(255, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
            Pen pen(penColor, line_width);
            int x = start_x - radius;
            int y = start_y - radius;
       
            g->DrawEllipse(&pen, x, y, radius * 2, radius * 2);
        }

        Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {
            set_radius(radius);
        }

        void info() const override {
            cout << "Circle:" << endl;
            cout << "Радиус: " << get_radius() << endl;
            Shape::info();
        }
    };

    class Romb :public Shape
    {
        double side_1;
        double side_2;
        double angleDeg;
    public:
        void set_side_1(double side_1) { this->side_1 = side_1; }
        void set_side_2(double side_2) { this->side_2 = side_2; }
        void set_angleDeg(double angleDeg) { this->angleDeg = angleDeg; }
        
        double get_side_1()const { return side_1; }
        double get_side_2()const { return side_2; }
        double get_angleDeg()const { return angleDeg; }

        double get_side_3() const
        {
            return sqrt((side_1 * side_1) + (side_1 * side_1) - 2 * side_1 * side_1 * cos(angleDeg * M_PI / 180));
        }

        double get_area_1() const{return 0.5 * side_1 * side_1 * sin(angleDeg * M_PI / 180); }
        double get_area_2() const
        {
            double s = (side_2 + side_2 + get_side_3()) / 2;
            double radicand = s * (s - side_2) * (s - side_2) * (s - get_side_3());
            if (radicand < 0)
            {
                std::cout << "Ошибка: радианнд отрицателен, проверьте входные параметры." << std::endl;
                return 0;
            }
            return sqrt(radicand);
        }
        double get_perimeter()const override { return (side_1 + side_2) * 2; }
  
        // Основная площадь
        double get_area() const override {return  get_area_1() + get_area_2(); }

            double get_height_1() const {return 2 * get_area_1()/ get_side_3();}
            double get_height_2() const {return 2 * get_area_2()/ get_side_3(); }
       
        // Расчет координат вершин
        void fill(Graphics* g) const {
            Gdiplus::Color fillColor(FILLCOLOR);
            SolidBrush brush(fillColor);

            double angleRad = angleDeg * M_PI / 180;
            double side_3 = get_side_3();

            PointF points[4];
            points[0] = PointF(start_x, start_y);
            points[1] = PointF(start_x + side_3/2, start_y - get_height_1());
            points[2] = PointF(start_x + side_3, start_y);
            points[3] = PointF(start_x + side_3/2, start_y + get_height_2());
            g->FillPolygon(&brush, points, 4);
        }
        void draw(Graphics* g) const
        {
            Gdiplus::Color fillColor(FILLCOLOR);
            SolidBrush brush(fillColor);

            double angleRad = angleDeg * M_PI / 180;
            double side_3 = get_side_3();

            PointF points[8];
            points[0] = PointF(start_x, start_y);
            points[1] = PointF(start_x + side_3 / 2, start_y - get_height_1());
            points[2] = PointF(start_x + side_3, start_y);
            points[3] = PointF(start_x + side_3 / 2, start_y + get_height_2());
            points[4] = PointF(start_x, start_y);
            points[5] = PointF(start_x + side_3, start_y);
            points[6] = PointF(start_x + side_3 / 2, start_y - get_height_1());
            points[7] = PointF(start_x + side_3 / 2, start_y + get_height_2());
            Gdiplus::Color penColor(255, 0, 0, 0);
            Pen pen(penColor, line_width);
            g->DrawPolygon(&pen, points, 8);
        }

        Romb(double side_1, double side_2, double angleDeg ,SHAPE_TAKE_PARAMETERS)
            :Shape(SHAPE_GIVE_PARAMETERS)
        {
            set_side_1(side_1);
            set_side_2(side_2);
            set_angleDeg(angleDeg);
        }

        void info() const override 
        {
            cout << "Romb:" << endl;
            cout << "Сторона 1: " << get_side_1() << endl;
            cout << "Сторона 2: " << get_side_2() << endl;
            cout << "Сторона 3: " << get_side_3() << endl;
            cout << "Угол: " << get_angleDeg() << endl;
            cout << "Высота 1: " << get_height_1() << endl;
            cout << "Высота 2: " << get_height_2() << endl;
            cout << "Площадь 1: " << get_area_1() << endl;
            cout << "Площадь 2: " << get_area_2() << endl;
            Shape::info();
        }
    };
    class Square :public Rectangle 
    {
      public:
        Square(double side, SHAPE_TAKE_PARAMETERS)
            :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {
        }
    };

    
}

   void main()
   {
         setlocale(LC_ALL, "");
        
         // Инициализация GDI+
         InitGDIPlus();
        
         const int width = 800;
         const int height = 600;
        
         // Создаем Bitmap и Graphics для рисования
         Bitmap* pBitmap = new Bitmap(width, height, PixelFormat32bppARGB);
         Graphics* g = Graphics::FromImage(pBitmap);
         g->Clear(Color(255, 255, 255, 255)); // белый фон
        
          
         Geometry::Square square(50, 50, 50, 1, Geometry::Color::Red);
         square.info();
         square.fill(g);
         //square.draw(g);
         cout << "\n";
        
         Geometry::Rectangle rectangle(50, 100, 200, 50, 1, Geometry::Color::Blue);
         rectangle.info();
         rectangle.fill(g);
         //rect.draw(g);
         cout << "\n";
        
         Geometry::Triangle triangle(100, 150, 60,270, 50, 1, Geometry::Color::Green);
         triangle.info();
         triangle.fill(g);
         triangle.draw(g);
         cout << "\n";
        
          Geometry::Circle circle(50, 450, 150, 1, Geometry::Color::Yellow);
          circle.info();
          circle.fill(g);
         //circle.draw(g);
         cout << "\n";
        
          Geometry::Romb romb(50, 150,120, 550,150, 5, Geometry::Color::Violet);
          romb.info();
          romb.fill(g);
          romb.draw(g);
          cout << "\n";


         // Сохраняем изображение
         wchar_t filename[] = L"output.png";
         CLSID pngClsid;
         GetEncoderClsid(L"image/png", &pngClsid);
         pBitmap->Save(filename, &pngClsid, NULL);
        
        
         // Освобождаем ресурсы
         delete g;
         delete pBitmap;
        
         // Открываем файл в Paint
         ShellExecute(NULL, L"open", filename, NULL, NULL, SW_SHOW);
        
         // Завершаем работу GDI+
         ShutdownGDIPlus();
        
    
   }