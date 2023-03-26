#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
bool inf = false;

// Начальная точка
vector<double> x0 = { 1.0, 1.0 };
double f(vector<double> x) {
    // Функция
    return pow(1-x[0], 2) + pow(x[1] + 1, 2);
}

vector<vector<double>> simplex(vector<double> x0, double delta) {
    int n = x0.size();
    vector<vector<double>> res(n + 1);
    res[0] = x0;
    for (int i = 1; i <= n; i++) {
        res[i] = x0;
        res[i][i - 1] += delta;
    }
    return res;
}

vector<vector<double>> sort_simplex(vector<vector<double>> s) {
    sort(s.begin(), s.end(), [](vector<double> a, vector<double> b) {return f(a) < f(b); });
    return s;
}

// Поиск центра тяжести
vector<double> centroid(vector<vector<double>> s) {
    int n = s.size() - 1;
    vector<double> res(n);
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) sum += s[j][i];
        res[i] = sum / n;
    }
    return res;
}

// Отражение
vector<double> reflection(vector<double> x, vector<double> c, double alpha) {
    int n = x.size();
    vector<double> xr(n);
    for (int i = 0; i < n; i++) xr[i] = (alpha + 1) * c[i] - alpha * x[i];
    return xr;
}

// Расширение
vector<double> expansion(vector<double> xr, vector<double> c, double gamma) { 
    int n = xr.size();
    vector<double> xe(n);
    for (int i = 0; i < n; i++) xe[i] = (1 - gamma) * c[i] + gamma * xr[i];
    return xe;
}

// Сжатие
vector<double> contraction(vector<double> x, vector<double> c, double beta){
    int n = x.size();
    vector<double> xc(n);
    for (int i = 0; i < n; i++) xc[i] = (1 + beta) * c[i] - beta * x[i];
    return xc;
}

// Глобальное сжатие
vector<vector<double>> shrink(vector<vector<double>> s, double sigma) {
    int n = s.size() - 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < n; j++)
            s[i][j] = s[0][j] + sigma * (s[i][j] - s[0][j]);
    return s;
}

vector<double> NelderMead(vector<double> x0, double delta, double alpha, double gamma, double beta, double sigma, double tol) {
    int n = x0.size();
    vector<vector<double>> s = simplex(x0, delta);
    int iter = 0;
    while (true) {
        iter++;
        s = sort_simplex(s);
        if (abs(f(s[n - 1])) >= INFINITY) {
            cout << "no global minimum";
            inf = true;
            break;
        }
        /*for (int i = 0; i < s[n - 1].size(); i++) cout << s[n - 1][i] << ' ';
        cout << endl;
        cout << f(s[n - 1]);
        cout << endl;
        cout << endl;*/
        if (abs(f(s[n]) - f(s[0])) <= tol && iter > 100) break; // Условие останова

        vector<double> c = centroid(s);
        vector<double> xr = reflection(s[n], c, alpha);

        if (f(xr) < f(s[n - 1])) {
            if (f(xr) >= f(s[0])) {
                s[n] = xr;
            }
            else {
                vector<double> xe = expansion(xr, c, gamma);
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
            vector<double> xc = contraction(s[n], c, beta);
            if (f(xc) < f(s[n])) {
                s[n] = xc;
            }
            else {
                s = shrink(s, sigma);
            }
        }
    }
    return s[0];
}

int main() {
    double delta = 1.0;
    double alpha = 1.0;
    double gamma = 2.0;
    double beta  = 0.5;
    double sigma = 0.5;
    double tol  = 0.00001;

    vector<double> res = NelderMead(x0, delta, alpha, gamma, beta, sigma, tol);
    if (inf) return 0;
    cout << fixed;
    cout.precision(5);
    cout << "Result: ";
    for (double x : res) cout << x << " ";
    return 0;
}
