#include "2preprocess.h"
#include "LUT/LUT_definition.h"
# define pi 3.141592653589793238462643383279502884L

double adjust_to_range(double angle,double m=pi) {
    //make the angle between -pi and pi
    while (angle > m) {
        angle -= 2 * m;
    }
    while (angle < -m) {
        angle += 2 * m;
    }
    return angle;
}

double to_sin(double a){
    a= adjust_to_range(a);
    auto lower=map_sin.lower_bound(a);
    auto upper = lower--;
    double x0 = lower->first;
    double x1 = upper->first;
    double y0 = lower->second;
    double y1 = upper->second;
    double ratio = (a - x0) / (x1 - x0);

    return y0 + ratio * (y1 - y0);
}
double to_asin(double a){
    if(a>1 || a<-1){
        throw MyError("Out of bound argument for Asin function (>1 or <-1)");
    }
    auto lower=map_asin.lower_bound(a);
    auto upper = lower--;
    double x0 = lower->first;
    double x1 = upper->first;
    double y0 = lower->second;
    double y1 = upper->second;
    double ratio = (a - x0) / (x1 - x0);

    return y0 + ratio * (y1 - y0);
}
double to_cos(double a){
    a= adjust_to_range(a);
    auto lower=map_cos.lower_bound(a);
    auto upper = lower--;
    double x0 = lower->first;
    double x1 = upper->first;
    double y0 = lower->second;
    double y1 = upper->second;
    double ratio = (a - x0) / (x1 - x0);

    return y0 + ratio * (y1 - y0);
}
double to_acos(double a){
    if(a>1 || a<-1){
        throw MyError("Out of bound argument for Acos function (>1 or <-1)");
    }
    return pi/2- to_asin(a);
}
double to_tan(double a){
    a= adjust_to_range(a,pi/2);
    if(cos(a)==0){
        throw MyError("There is a tan(pi/2) or tan(-pi/2) in your exression :( ");
    }
    return to_sin(a)/to_cos(a);
}
double to_atan(double x) {
    if (x < 0) return -to_atan(-x);
    if (x > 1) return pi / 2 - to_atan(1 / x);
    double result = 0;
    double x_squared = x * x;
    double term = x;
    double divisor = 1;
    while (term != 0) {
        result += term;
        divisor += 2;
        term *= -x_squared / divisor;
    }
    return result;
}
double binaryPower(double base, int exponent) {
    double result = 1.0;
    while (exponent) {
        if (exponent & 1)
            result *= base;
        base *= base;
        exponent >>= 1;
    }
    return result;
}
double to_sqrt(double x) {
    if (x < 0) {
        //throw MyError("Cannot compute square root of a negative number");
    }

    double guess = x / 2.0; // Initial guess
    double prev_guess = 0.0;
    const double epsilon = 1e-6; // Desired precision

    while (abs(guess - prev_guess) > epsilon) {
        prev_guess = guess;
        guess = (guess + x / guess) / 2.0;
    }

    return guess;
}
double to_pow(double base, double exponent) {
    if (exponent == 0.0)
        return 1.0;

    if (exponent < 0.0) {
        base = 1.0 / base;
        exponent = -exponent;
    }

    double intPart = static_cast<int>(exponent);
    double fracPart = exponent - intPart;

    double result = binaryPower(base, intPart);

    double fractionResult = 0.0;
    double fractionmult = 1.0;
    double sqrts = 2;
    double basef = to_sqrt(base);

    while (abs(fracPart - fractionResult) >= 0.0001 ) {
        //cout<<fractionResult<<endl;
        double distance0 = abs(fracPart - fractionResult);
        double distance1 = abs(fracPart - (fractionResult + 1 / sqrts));
        double distance2 = abs(fracPart - (fractionResult - 1 / sqrts));

        if (distance1 < distance2 && distance1<distance0 ) {
            fractionResult += 1 / sqrts;
            fractionmult *= basef;
        }
        else if(distance2 < distance1 && distance2<distance0){
            fractionResult -= 1 / sqrts;
            fractionmult /= basef;
        }
        basef = to_sqrt(basef);
        sqrts *= 2;
        //cout<<"diff"<<fracPart - fractionResult<<endl;
    }

    result *= fractionmult;
    return result;
}