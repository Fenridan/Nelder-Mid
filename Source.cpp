#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    vector <double > x;

    int size() {
        return x.size();
    }

    void debug();
};

double f(Point x) {
    // Функция Розенброка
    return pow(1-x.x[0], 2) + 100*pow(x.x[1] - x.x[0]*x.x[0], 2);
}

void Point::debug() {
    cout << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << ' ';
    }
    cout << " =  " << f(*this);
    cout << endl;
}

Point operator*(double k, Point p) {
    Point result = p;
    for (int i = 0; i < p.size(); i++) result.x[i] *= k;
    return result;
}

Point operator+(Point pf, Point ps) {
    Point result = pf;
    for (int i = 0; i < ps.size(); i++) result.x[i] += ps.x[i];
    return result;
}

Point operator-(Point pf, Point ps) {
    Point result = pf;
    for (int i = 0; i < ps.size(); i++) result.x[i] -= ps.x[i];
    return result;
}

struct Parameters {
    double delta;
    double alpha;
    double gamma;
    double beta;
    double sigma;
    double tol;
};

vector<Point> simplex(Point x0, double delta) {
    int n = x0.size();
    vector<Point> res(n + 1);
    res[0] = x0;
    for (int i = 1; i <= n; i++) {
        res[i] = x0;
        res[i].x[i - 1] += delta;
    }
    return res;
}

vector<Point> sort_simplex(vector<Point> s) {
    sort(s.begin(), s.end(), [](Point a, Point b) {return f(a) < f(b); });
    return s;
}

// Поиск центра тяжести
Point centroid(vector<Point> s) {
    int n = s.size() - 1;
    Point res = s[0];
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += s[j].x[i];
        }
        res.x[i] = sum / n;
    }
    return res;
}

// Отражение
Point reflection(Point x, Point c, double alpha) {
    Point xr = x;
    xr = (alpha + 1) * c - alpha * x;
    return xr;
}

// Расширение
Point expansion(Point xr, Point c, double gamma) {
    Point xe;
    xe = (1 - gamma) * c + gamma * xr;
    return xe;
}

// Сжатие
Point contraction(Point x, Point c, double beta) {
    Point xc;
    xc = (1 + beta) * c - beta * x;
    return xc;
}

// Глобальное сжатие
vector<Point> shrink(vector<Point> s, double sigma) {
    int n = s.size() - 1;
    for (int i = 1; i <= n; i++)
        s[i] = s[0] + sigma * (s[i] - s[0]);
    return s;
}

double NelderMead(Point x0, Parameters parameter) {
    int n = x0.size();
    vector<Point> s = simplex(x0, parameter.delta);
    int iter = 0;
    while (true) {
        iter++;
        s = sort_simplex(s);
        if (abs(f(s[n - 1])) >= INFINITY) {
            break;
        }
        if (abs(f(s[n]) - f(s[0])) <= parameter.tol && iter > 100) break; // Условие останова
 
        Point c = centroid(s);
        Point xr = reflection(s[n], c, parameter.alpha);
        if (f(xr) < f(s[n - 1])) {
            if (f(xr) >= f(s[0])) {
                s[n] = xr;
            }
            else {
                Point xe = expansion(xr, c, parameter.gamma);
                if (f(xe) < f(s[0])) {
                    s[n] = xe;
                }
                else {
                    s[n] = xr;
                }
            }
        }
        else {
            if (f(xr) < f(s[n])) {
                s[n] = xr;
            }
            Point xc = contraction(s[n], c, parameter.beta);
            if (f(xc) < f(s[n])) {
                s[n] = xc;
            }
            else {
                s = shrink(s, parameter.sigma);
            }
        }
    }
    x0 = s[0];
    return f(s[0]);
}

int main() {
    // Начальная точка
    Point x0;
    x0.x = { 1.0, 1.0 };

    Parameters parameter;
    parameter.delta = 1.0;
    parameter.alpha = 1.0;
    parameter.gamma = 2.0;
    parameter.beta = 0.5;
    parameter.sigma = 0.5;
    parameter.tol = 0.00001;

    Point res = x0;
    double result = NelderMead(x0, parameter);
    if (result <= -INFINITY) {
        cout << "No global minimum" << endl;
        return 0;
    }
    cout << fixed;
    cout.precision(5);
    cout << "Result: ";
    res.debug();
    return 0;
}
