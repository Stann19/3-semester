#include <iostream>
using namespace std;

double min(double a, double b) {
	if (a <= b) {
		return a;
	};
	return b;
};


double max(double a, double b) {
	if (a >= b) {
		return a;
	};
	return b;
}

class rect {
private:
	double x1, x2, y1, y2;
public:
	rect(): rect(0, 0 , 0, 0) {}
	rect(double x1, double x2, double y1, double y2): x1(x1), x2(x2), y1(y1), y2(y2) {}

	void output()
	{
		cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
	}

	void move(double dx, double dy)
	{
		x1 += dx;
		y1 += dy;
		x2 += dx;
		y2 += dy;
	}

	void changeSize(double dx, double dy)
	{
		x2 += dx;
		y2 += dy;
	}

	rect intersection(rect a) {
		if (x1 >= a.x2 || x2 <= a.x1 || y2 <= a.y1 || y1 >= a.y2)
		{
			cout << "No intersection";
			rect voidrectangle;
			return voidrectangle;
		}

		double new_x1, new_y1, new_x2, new_y2;

		new_x1 = max(x1, a.x1);
		new_x2 = min(x2, a.x2);
		new_y1 = max(y1, a.y1);
		new_y2 = min(y2, a.y2);

		rect rectangle(new_x1, new_x2, new_y1, new_y2);
		return rectangle;

	}
	rect min_rect(rect a) {
		double new_x1, new_y1, new_x2, new_y2;
		new_x1 = min(a.x1, x1);
		new_y1 = min(a.y1, y1);
		new_x2 = max(a.x2, x2);
		new_y2 = max(a.y2, y2);

		rect rectangle(new_x1, new_x2, new_y1, new_y2);
		return rectangle;
	}
};

int main()
{
	double x11, x12, y11, y12;
	cin >> x11 >> x12 >> y11 >> y12;
	double x21, x22, y21, y22;
	cin >> x21 >> x22 >> y21 >> y22;
	rect a(x11, x12, y11, y12);
	rect b(x21, x22, y21, y22);
	double dx1, dy1;
	cin >> dx1 >> dy1;
	a.changeSize(dx1, dy1);
	a.output();
	a.move(-2, -1);
	a.output();
	rect rectangle = a.intersection(b);
	rectangle.output();
	rect shell = b.min_rect(a);
	shell.output();

	return 0;
}
