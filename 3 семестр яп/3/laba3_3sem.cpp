#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Shapes
{
protected:
	string str;
	float x, y;
public:
	Shapes()
	{
		x = 0;
		y = 0;
	}
	virtual ~Shapes() {};
	virtual string to_String() = 0;
	virtual float Area() = 0; //Вычисление площади
	virtual void Draw() = 0;
	void Move(float move_x, float move_y)
	{
		x = move_x;
		y = move_y;
	}
};

class Triangle : public Shapes// Треугольник
{
private:
	float Ax, Ay, Bx, By, Cx, Cy, a, b, c, p;
public:
	Triangle()
	{
		a = 0;
		b = 0;
		c = 0;
		Ax = 0;
		Ay = 0;
		Bx = 0;
		By = 0;
		Cx = 0;
		Cy = 0;
		p = 0;
	}
	Triangle(float A_x, float A_y, float B_x, float B_y, float C_x, float C_y)
	{
		Ax = A_x;
		Ay = B_y;
		Bx = B_x;
		By = B_y;
		Cx = C_x;
		Cy = C_y;
		a = sqrt(((Bx - Ax) * (Bx - Ax)) + ((By - Ay) * (By - Ay)));
		b = sqrt(((Cx - Bx) * (Cx - Bx)) + ((Cy - By) * (Cy - By)));
		c = sqrt(((Cx - Ax) * (Cx - Ax)) + ((Cy - Ay) * (Cy - Ay)));
		p = (a + b + c) / 2;
	}
	virtual ~Triangle() {};
	virtual float Area()
	{
		return sqrt(p * (p - a) * (p - b) * (p - c));// формула Герона
	}
	virtual string to_String()
	{
		str += "Информация о фигуре треугольник: ";
		str += "Введите сторону а: ";
		str += to_string(a);
		str += " Введите сторону b: ";
		str += to_string(b);
		str += " Введите сторону c: ";
		str += to_string(c);
		str += " Полупериметр: ";
		str += to_string(p);
		str += " Вычисление площади: ";
		str += to_string(Area());
		str += "\n";
		return str;
	}
	virtual void Draw()
	{
		ContextSettings settings;
		settings.antialiasingLevel = 8;
		RenderWindow window(VideoMode(800, 800), "Hello, SFML!", Style::Default, settings);
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(Color(255, 192, 203));
			ConvexShape convex;
			convex.setPointCount(3);
			convex.setPoint(0, Vector2f(Ax * 37.938105 , Ay * 37.938105));
			convex.setPoint(1, Vector2f(Bx * 37.938105, By * 37.938105));
			convex.setPoint(2, Vector2f(Cx * 37.938105 , Cy * 37.938105));
			convex.setFillColor(Color::Red);
			convex.move(x * 37.938105, y * 37.938105);
			window.draw(convex);
			window.display();
		}
	}
};

class Rectangle : public Shapes// Прямоугольник
{
protected:
	float a, b, a_radius, b_radius;
public:
	Rectangle() //Конструктор для фигуры прямоугольник
	{
		a = 0;
		b = 0;
		a_radius = 0;
		b_radius = 0;



	}
	Rectangle(float a_p, float b_p)
	{
		a = a_p;
		b = b_p;
		a_radius = a * 37.938105;
		b_radius = b * 37.938105;
	}
	virtual ~Rectangle()
	{};
	virtual float Area()
	{
		return a * b;
	}
	virtual string to_String()
	{
		str += "Информация о фигуре прямоугольник: ";
		str += "Введите сторону a: ";
		str += to_string(a);
		str += " Введите сторону b: ";
		str += to_string(b);
		str += " Вычисление площади: ";
		str += to_string(Area());
		str += "\n";
		return str;
	}
	virtual void Draw()// функция для рисования фигур
	{
		ContextSettings settings;
		settings.antialiasingLevel = 8;
		RenderWindow window(VideoMode(500, 200), "Hello, SFML!", Style::Default, settings);
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(Color(255, 255, 0));
			RectangleShape rectangle(Vector2f(a_radius, b_radius));
			rectangle.setPosition(x, y);
			rectangle.setFillColor(Color(0, 0, 128));
			window.draw(rectangle);
			window.display();
		}
	}
};

class Square : public Rectangle
{
public:
	Square(float a_p) : Rectangle(a_p, a_p) {};
	virtual ~Square() {};
	virtual string to_String()
	{
		str += "Информация о фигуре квадрат: ";
		str += "Введите сторону a: ";
		str += to_string(a);
		str += " Вычисление площади: ";
		str += to_string(Area());
		str += "\n";
		return str;
	}
};

class Ellipse : public Shapes
{
protected:
	float a, b, a_radius, b_radius;
public:
	Ellipse()
	{
		a = 0;
		b = 0;
		a_radius = 0;
		b_radius = 0;
	}
	Ellipse(float a_p, float b_p)
	{
		a = a_p;
		b = b_p;
		a_radius = a * 37.938105;
		b_radius = b * 37.938105;
	}
	virtual ~Ellipse() {};
	virtual float Area()
	{
		return 3.1415926535 * (a * b);
	}
	virtual string to_String()
	{
		str += "Информация о фигуре Эллипс: ";
		str += "Введите сторону a: ";
		str += to_string(a);
		str += " Введите сторону b: ";
		str += to_string(b);
		str += " Вычисление площади: ";
		str += to_string(Area());
		str += "\n";
		return str;
	}
	virtual void Draw()
	{
		ContextSettings settings;
		settings.antialiasingLevel = 8;
		RenderWindow window(VideoMode(400, 200), "Hello, SFML!", Style::Default, settings);
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(Color(255, 255, 0));
			CircleShape circle(1.f);
			circle.setScale(a_radius, b_radius);
			circle.setFillColor(Color(0, 255, 255));
			window.draw(circle);
			window.display();
			void show();
		}
	}
};

class Circle : public Ellipse
{
public:
	Circle(float r_p) : Ellipse(r_p, r_p) {};
	virtual ~Circle() {};
	virtual string to_String()
	{
		str += "Информация о фигуре круг: ";
		str += "Радиус круга: ";
		str += to_string(a);
		str += " Вычисление площади: ";
		str += to_string(Area());
		str += "\n";
		return str;
	}
};
class Cylinder
{
protected:
	float h;
	string str;
	Shapes* shp;
public:
	Cylinder()
	{
		h = 0;
		shp = 0;
	}
	Cylinder(float h_p, Shapes* shp_p)
	{
		h = h_p;
		shp = shp_p;
	}
	~Cylinder() {};
	float Capacity()
	{
		return h * shp->Area();
	}
	string to_String()
	{
		str += "Информация о фигуре цилиндр: ";
		str += "Высота : ";
		str += to_string(h);
		str += " Вычисление площади: ";
		str += to_string(shp->Area());
		str += " Вычисление объема: ";
		str += to_string(Capacity());
		str += "\n";
		return str;
	}
};



int main()
{
	setlocale(LC_ALL, "Russian");

	Shapes* shp;
	Cylinder  Cylinderz;
	int Figur = 0;
	do
	{
		cout << "1) Треугольник" << endl
			<< "2) Прямоугольник" << endl
			<< "3) Квадрат" << endl
			<< "4) Эллипс" << endl
			<< "5) Круг" << endl
			<< "6) Цилиндр" << endl
			<< "0) Выход с успешным завершением" << endl;
		cout << endl << "Выберите пункт от 1-6: ";
		cin >> Figur;
		cout << endl;
		switch (Figur)
		{
		case 1:
			shp = new Triangle(1, 1, 2, 2, 1, 3);
			cout << shp->to_String() << endl;
			shp->Move(4, 1);
			shp->Draw();
			break;
		case 2:
			shp = new Rectangle(3, 5);
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 3:
			shp = new Square(4);
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 4:
			shp = new Ellipse(2, 1);
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 5:
			shp = new Circle(4);
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 6:
			Cylinderz = Cylinder(3, new Square(4));
			cout << Cylinderz.to_String() << endl;
			break;
		default:
			if (Figur != 0)
			{
				cout << "Такое действие не найдено!" << endl << endl;
			}
			break;
		}
	} while (Figur != 0);
}
