#pragma once
#include "Point.h"
#include <algorithm>
#include <functional>

// Генерация начального симплекса
Point* simplex(Point x0, double delta) {
    int n = x0.size();
    Point* res = new Point[n + 1];
    res[0].copy(x0);
    for (int i = 1; i <= n; i++) {
        res[i].copy(x0);
        res[i].x[i - 1] += delta;
    }
    return res;
}

// Сортировка симплекса
Point* sort_simplex(Point* s, int n, function <double(Point)> f) {
    sort(s, s + n, [f](Point a, Point b) {return f(a) < f(b); });
    return s;
}
