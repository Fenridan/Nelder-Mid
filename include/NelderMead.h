#pragma once
#include "NelderMeadOperations.h"
#include "Simplex.h"

struct Parameters {
    double delta;
    double alpha;
    double gamma;
    double beta;
    double sigma;
    double tol;
};

Point NelderMead(int n, Parameters parameter, function<double(Point)> f) {
    Point x0(n);
    Point* s = simplex(x0, parameter.delta);
    while (true) {

        s = sort_simplex(s, n + 1, f);

        if (FindEdge(s[n], s[0]) <= parameter.tol || f(s[n - 1]) <= -INFINITY) break; // Условие останова

        Point c = centroid(s, n);
        Point xr = reflection(s[n], c, parameter.alpha);

        if (f(xr) < f(s[n - 1])) {
            if (f(xr) >= f(s[0])) {
                s[n].copy(xr);
            }
            else {
                Point xe = expansion(xr, c, parameter.gamma);
                if (f(xe) < f(s[0])) {
                    s[n].copy(xe);
                }
                else {
                    s[n].copy(xr);
                }
            }
        }
        else {
            if (f(xr) < f(s[n])) {
                s[n].copy(xr);
            }
            Point xc = contraction(s[n], c, parameter.beta);
            if (f(xc) < f(s[n])) {
                s[n].copy(xc);
            }
            else {
                s = shrink(s, n, parameter.sigma);
            }
        }
    }
    return s[0];
}

