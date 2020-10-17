/*
 * animaly_detection_util.cpp
 *
 * Author: 318432333 Shoval Hen Habas
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum / size;
}

// returns the variance of X and Y
float var(float *x, int size) {
    float populationPart = 1 / (float)size;
    float oneToN = 0, oneToN2 = 0;
    for (int i = 0; i < size; i++) {
        oneToN += x[i];
    }
    for (int i = 0; i < size; i++) {
        oneToN2 += x[i] * x[i];
    }
    float u = populationPart * oneToN;
    float finalCalc = (populationPart * oneToN2) - (u * u);
    return finalCalc;

}

// returns the covariance of X and Y
float cov(float *x, float *y, int size) {
    float avgX = avg(x, size);
    float avgY = avg(y, size);
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += ((x[i] - avgX) * (y[i] - avgY));
    }
    return sum / (size );


}


// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size) {
    float varianceSqrtX = sqrt(var(x, size));
    float varianceSqrtY = sqrt(var(y, size));
    return (cov(x, y, size) / (varianceSqrtX * varianceSqrtY));

}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size) {
    float x[size];
    float y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->getX();
        y[i] = points[i]->getY();
    }
    float avgX = avg(x, size);
    float avgY = avg(y, size);
    float a = (cov(x, y, size) / var(x, size));
    float b = (avgY - (a * avgX));

    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size) {
    Line l = linear_reg(points, size);
    float calcYValue = l.f(p.getX());
    return abs(calcYValue - p.getY());

}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    float calcYValue = l.f(p.getX());
    return abs(calcYValue - p.getY());
}




