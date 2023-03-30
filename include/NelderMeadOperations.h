#pragma once
#include "Point.h"

// ����� ������ �������
Point centroid(Point* s, int n) {
    Point res(n);
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += s[j].x[i];
        }
        res.x[i] = sum / n;
    }
    return res;
}

// ���������
Point reflection(Point x, Point c, double alpha) {
    Point xr(x.size());
    xr = (alpha + 1) * c - alpha * x;
    return xr;
}

// ����������
Point expansion(Point xr, Point c, double gamma) {
    Point xe(xr.size());
    xe = (1 - gamma) * c + gamma * xr;
    return xe;
}

// ������
Point contraction(Point x, Point c, double beta) {
    Point xc(x.size());
    xc = (1 + beta) * c - beta * x;
    return xc;
}

// ���������� ������
Point* shrink(Point* s, int n, double sigma) {
    for (int i = 1; i <= n; i++)
        s[i] = s[0] + sigma * (s[i] - s[0]);
    return s;
}

// ��������� ����� ����� �������
double FindEdge(Point pf, Point ps) {
    double result = 0;

    for (int i = 0; i < pf.size(); i++) {
        result += pow(pf.x[i] - ps.x[i], 2);
    }
    result = sqrt(result);

    return result;
}