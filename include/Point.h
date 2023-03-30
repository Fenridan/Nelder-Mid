#pragma once
#include <iostream>
#include <functional>

using namespace std;

// Класс точка
class Point {
private:
    int num = 0;
public:
    double* x;

    Point(int n) {
        num = n;
        x = new double[num];
        for (int i = 0; i < num; i++) {
            *(x + i) = 1.0;
        }
    }
    Point() {}

    double* operator[](int row)
    {
        return x + row * num;
    }

    // Вывод точки
    void debug(function<double(Point)> f) {
        cout << endl;
        cout << fixed;
        cout.precision(3);
        cout << "Result: ";
        for (int i = 0; i < num; i++) {
            cout << x[i] << ' ';
        }
        cout << " with answer:" << f(*this) << endl;
        cout << endl;
    }

    void debug() {
        cout << endl;
        cout << fixed;
        cout.precision(3);
        cout << "Result: ";
        for (int i = 0; i < num; i++) {
            cout << x[i] << ' ';
        }
        cout << endl;
    }

    int size() {
        return num;
    }

    // Копирование координат из другой точки
    void copy(Point p) {
        int n = p.size();
        Point res(n);
        for (int i = 0; i < n; i++) {
            res.x[i] = *(p.x + i);
        }
        *this = res;
    }
};

// Переопределение операторов для точки
Point operator*(double k, Point p) {
    Point result;
    result.copy(p);
    for (int i = 0; i < p.size(); i++) result.x[i] *= k;
    return result;
}
Point operator+(Point pf, Point ps) {
    Point result;
    result.copy(pf);
    for (int i = 0; i < ps.size(); i++) result.x[i] += ps.x[i];
    return result;
}
Point operator-(Point pf, Point ps) {
    Point result;
    result.copy(pf);
    for (int i = 0; i < ps.size(); i++) result.x[i] -= ps.x[i];
    return result;
}
