#pragma once
#include "Point.h"
#include <functional>

// Проверка результата работы алгоритма
bool CheckResult(Point p, function<double(Point)> f) {
    if (f(p) <= -INFINITY) {
        cout << "No global minimum" << endl;
        return false;
    }
    return true;
}

double Rosenbrook(Point p) {
    // Функция Розенброка
    return pow(1 - p.x[0], 2) + 100 * pow(p.x[1] - p.x[0] * p.x[0], 2);
}

double Himmelblau(Point p) {
    // Функция Химмельблау
    return pow(p.x[0] * p.x[0] + p.x[1] - 11, 2) + pow(p.x[0] + p.x[1] * p.x[1] - 7, 2);
}

double FuncEasy(Point p) {
    return pow(3 - p.x[0], 2) + pow(p.x[1] - p.x[0] * p.x[0], 2);
}

double FuncThrio(Point p) {
    return pow(3 - p.x[0], 2) + pow(p.x[1] - p.x[0] * p.x[0], 4) + pow(p.x[2] * p.x[1] - 18, 2);
}
