#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Ex1
{
private:
	float a, b;
	string iskl;
public:
	Ex1(float a_p, float b_p)
	{
		a = a_p;
		b = b_p;
		iskl = "Длина сторон фигур должна быть больше 0, а так же не может быть отрицательного значения";
	}
	float F_a()
	{
		return a;
	}
	float F_b()
	{
		return b;
	}
	string F_iskl()
	{
		return iskl;
	}
};

class Ex2
{
private:
	float ax, ay, bx, by, cx, cy;
	string iskl;
public:
	Ex2(float ax_p, float ay_p, float bx_p, float by_p, float cx_p, float cy_p)
	{
		ax = ax_p;
		ay = ay_p;
		bx = bx_p;
		by = by_p;
		cx = cx_p;
		cy = cy_p;
		iskl = "Например, неверно заданы координаты фигуры, поэтому сработало исключение: ";
	}
	float F_ax()
	{
		return ax;
	}
	float F_ay()
	{
		return ay;
	}
	float F_bx()
	{
		return bx;
	}
	float F_by()
	{
		return by;
	}
	float F_cx()
	{
		return cx;
	}
	float F_cy()
	{
		return cy;
	}
	string F_iskl()
	{
		return iskl;
	}
};

class Ex3
{
private:
	float r1, r2;
	string iskl;
public:
	Ex3(float r1_p, float r2_p)
	{
		r1 = r1_p;
		r2 = r2_p;
		iskl = "Значение радиуса должно быть больше 0:";
	}
	float F_a()
	{
		return r1;
	}
	float F_b()
	{
		return r2;
	}
	string F_iskl()
	{
		return iskl;
	}
};

class Ex4
{
private:
	float h;
	string iskl;
public:
	Ex4(float h_p)
	{
		h = h_p;
		iskl = "Высота должна иметь значение больше 0, а так же не иметь отрицательного значения: ";
	}
	float F_h()
	{
		return h;
	}
	string F_iskl()
	{
		return iskl;
	}
};

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

class Triangle : public Shapes // Треугольник
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
		if ((A_x == B_x && A_x == C_x && B_x == C_x) || (A_y == B_y && A_y == C_y && B_y == C_y) || (A_x == B_x && A_y == B_y) || (A_x == C_x && A_y == C_y) || (B_x == C_x && B_y == C_y))
		{
			Ex2 e2(A_x, A_y, B_x, B_y, C_x, C_y);
			throw e2;
		}
		Ax = A_x;
		Ay = A_y;
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
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
	virtual string to_String()
	{
		str += "Информация о фигуре треугольник: ";
		str += "Введите сторону a: ";
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
		RenderWindow window(VideoMode(500, 200), "Hello, SFML!");
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(Color(255, 255, 255));
			ConvexShape convex;
			convex.setPointCount(3);
			convex.setPoint(0, Vector2f(Ax * 37.936267, Ay * 37.936267));
			convex.setPoint(1, Vector2f(Bx * 37.936267, By * 37.936267));
			convex.setPoint(2, Vector2f(Cx * 37.936267, Cy * 37.936267));
			convex.setFillColor(Color::Red);
			convex.move(x * 37.936267, y * 37.936267);
			window.draw(convex);
			window.display();
		}
	}
};

class Rectangle : public Shapes //  Прямоугольник
{
protected:
	float a, b, a_radius, b_radius;
public:
	Rectangle()
	{
		a = 0;
		b = 0;
		a_radius = 0;
		b_radius = 0;
	}
	Rectangle(float a_p, float b_p)
	{

		if (a_p <= 0 || b_p <= 0)
		{
			Ex1 e1(a_p, b_p);
			throw e1;
		}
		a = a_p;
		b = b_p;
		a_radius = a * 37.936267; // 1 см= 37.936267
		b_radius = b * 37.936267;
	}
	virtual ~Rectangle() {};
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
	virtual void Draw()
	{
		RenderWindow window(VideoMode(800, 800), "Hello, SFML!");
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
		if (a_p <= 0 || b_p <= 0)
		{
			Ex3 e3(a_p, b_p);
			throw e3;
		}
		a = a_p;
		b = b_p;
		a_radius = a * 37.936267;
		b_radius = b * 37.936267;
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
		RenderWindow window(VideoMode(800, 800), "Hello, SFML!");
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

template <typename T> // шаблон для сравнения значения, ввод числа должен быть больше 0
class Cylinder
{
protected:
	float h;
	string str;
	T shp;
public:
	Cylinder()
	{
		h = 0;
		shp = 0;
	}
	Cylinder(float h_p, T shp_p)
	{
		if (h_p <= 0)
		{
			Ex4 e4(h_p);
			throw e4;
		}
		h = h_p;
		shp = shp_p;
	}
	~Cylinder() {};
	float Volume()
	{
		return h * shp->Area();
	}
	string to_String()
	{
		str += "Информация о цилиндре: ";
		str += "Введите высоту: ";
		str += to_string(h);
		str += " Площадь: ";
		str += to_string(shp->Area());
		str += " Объем: ";
		str += to_string(Volume());
		str += "\n";
		return str;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Shapes* shp;
	Cylinder<Shapes*> shape;
	float a, b;
	float Ax, Ay, Bx, By, Cx, Cy;
	int lab = 0;
	do
	{
		cout << "1) Треугольник" << endl
			<< "2) Прямоугольник" << endl
			<< "3) Квадрат" << endl
			<< "4) Эллипс" << endl
			<< "5) Круг" << endl
			<< "6) Цилиндр" << endl
			<< "0) Успешый выход" << endl;
		cout << endl << "Выберите действие от 1-6: ";
		cin >> lab;
		cout << endl;
		switch (lab)
		{
		case 1:
			Ax = 0, Ay = 2, Bx = 1, By = 1, Cx = 0, Cy = 2;
			try
			{
				shp = new Triangle(Ax, Ay, Bx, By, Cx, Cy);
			}
			catch (Ex2& e2)
			{
				cout << e2.F_iskl() << e2.F_ax() << " " << e2.F_ay() << " " << e2.F_bx() << " " << e2.F_by() << " " << e2.F_cx() << " " << e2.F_cy() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			cout << shp->to_String() << endl;
			shp->Move(0, 1);
			shp->Draw();
			break;
		case 2:
			a = 0, b = 3;
			try
			{
				shp = new Rectangle(a, b);
			}
			catch (Ex1& e1)
			{
				cout << e1.F_iskl() << e1.F_a() << " " << e1.F_b() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 3:
			a = 4;
			try
			{
				shp = new Square(a);
			}
			catch (Ex1& e1)
			{
				cout << e1.F_iskl() << e1.F_a() << " " << e1.F_b() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 4:
			a = 3, b = 1;
			try
			{
				shp = new Ellipse(a, b);
			}
			catch (Ex3& e3)
			{
				cout << e3.F_iskl() << e3.F_a() << " " << e3.F_b() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 5:
			a = 4;
			try
			{
				shp = new Circle(a);
			}
			catch (Ex3& e3)
			{
				cout << e3.F_iskl() << e3.F_a() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			cout << shp->to_String() << endl;
			shp->Move(0, 0);
			shp->Draw();
			break;
		case 6:
			try
			{
				shape = Cylinder<Shapes*>(4, new Square(8));
			}
			catch (Ex1& e1)
			{
				cout << e1.F_iskl() << e1.F_a() << " " << e1.F_b() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			catch (Ex2& e2)
			{
				cout << e2.F_iskl() << e2.F_ax() << " " << e2.F_ay() << " " << e2.F_bx() << " " << e2.F_by() << " " << e2.F_cx() << " " << e2.F_cy() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			catch (Ex3& e3)
			{
				cout << e3.F_iskl() << e3.F_a() << " " << e3.F_b() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			catch (Ex4& e4)
			{
				cout << e4.F_iskl() << e4.F_h() << endl;
				cout << "Попробуйте снова..." << endl << endl;
				break;
			}
			cout << shape.to_String() << endl;
			break;
		default:
			if (lab != 0)
			{
				cout << "Такое действие не найдено..." << endl << endl;
			}
			break;
		}
	} while (lab != 0);
}