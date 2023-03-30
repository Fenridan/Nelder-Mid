#pragma once
#include "Point.h"
#include <functional>

// �������� ���������� ������ ���������
bool CheckResult(Point p, function<double(Point)> f) {
    if (f(p) <= -INFINITY) {
        cout << "No global minimum" << endl;
        return false;
    }
    return true;
}

double Rosenbrook(Point p) {
    // ������� ����������
    return pow(1 - p.x[0], 2) + 100 * pow(p.x[1] - p.x[0] * p.x[0], 2);
}

double Himmelblau(Point p) {
    // ������� �����������
    return pow(p.x[0] * p.x[0] + p.x[1] - 11, 2) + pow(p.x[0] + p.x[1] * p.x[1] - 7, 2);
}

double FuncEasy(Point p) {
    return pow(3 - p.x[0], 2) + pow(p.x[1] - p.x[0] * p.x[0], 2);
}