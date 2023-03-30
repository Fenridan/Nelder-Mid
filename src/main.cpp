#pragma once
#include "TestFunctions.h"
#include "NelderMead.h"

int main() {

    int num = 2; // Количество переменных

    Parameters parameter; // Параметры алгоритма
    parameter.delta = 1.0;
    parameter.alpha = 1.0;
    parameter.gamma = 2.0;
    parameter.beta = 0.5;
    parameter.sigma = 0.5;
    parameter.tol = 0.0001;

    function < double(Point) > func; // Функция
    
    func = Himmelblau;

    Point result = NelderMead(num, parameter, func);

    CheckResult(result, func);
    return 0;
}
