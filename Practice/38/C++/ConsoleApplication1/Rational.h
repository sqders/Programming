#pragma once
class Rational {
public:
    static int gcd(int i1, int i2);
    int a, b;//a-числитель b-знаменатель
    Rational() :
        a(0), b(0)
    {}
    Rational(int a, int b) :
        a(a), b(b)
    {}
    friend bool operator==(Rational& const  x, Rational& const y);
    friend Rational operator+(Rational& const x, Rational& const y);
    friend Rational operator-(Rational& const x, Rational& const y);
    friend Rational operator*(Rational& const x, Rational& const y);
    friend Rational operator/(Rational& const x, Rational& const y);
    operator double()const
    {
        double da = a, db = b;
        return da / db;
    }
    operator bool() const
    {
        if (a == 0 && b != 0)
            return 0;
        else
            return 1;
    }
    int numerator()
    {
        return a;
    }
    int denominator()
    {
        return b;
    }
    bool isNaN()
    {
        if (a == 0 && b == 0)
            return 1;
        else
            return 0;
    }
};
int Rational::gcd(int i1, int i2) {
    int great;
    if (i1 < 0 || i2 < 0)
        return 1;
    if (i1 > i2)great = i2;
    else great = i1;
    while (great > 0)
    {
        if (i1 % great == 0 && i2 % great == 0)
            return great;
        great--;
    }
    return i1 + i2;
}

bool operator==(const Rational& x, const Rational& y) {
    Rational x_new = x, y_new = y;
    if (x_new.isNaN() || y_new.isNaN())
    {
        return 0;
    }
    if (bool(x) != bool(y))
        return 0;
    if (x.b == 0 && y.b == 0 && (x.a > 0 && y.a < 0 || x.a < 0 && y.a>0))
    {
        return 0;
    }
    return ((x.a * y.b) == (y.a * x.b));
}
Rational operator+(const Rational& x, const Rational& y) {
    {Rational x_new = x, y_new = y;
    if (x_new.isNaN() || y_new.isNaN())
        return Rational(0, 0); }
    if (x.b == y.b)
        return Rational(x.a + y.a, x.b);

    Rational sum((x.a * y.b + y.a * x.b), (x.b * y.b));
    while (Rational::gcd(sum.a, sum.b) > 1)
    {
        int great = Rational::gcd(sum.a, sum.b);
        sum.b /= great;
        sum.a /= great;
    }
    return sum;
}
Rational operator-(const Rational& x, const Rational& y) {
    {Rational x_new = x, y_new = y;
    if (x_new.isNaN() || y_new.isNaN())
        return Rational(0, 0); }
    if (x.b == y.b)
        return Rational(x.a - y.a, x.b);

    Rational sum((x.a * y.b - y.a * x.b), (x.b * y.b));
    while (Rational::gcd(sum.a, sum.b) > 1)
    {
        int great = Rational::gcd(sum.a, sum.b);
        sum.b /= great;
        sum.a /= great;
    }
    return sum;
}
Rational operator*(const Rational& x, const Rational& y) {
    Rational mult(x.a * y.a, x.b * y.b);
    while (Rational::gcd(mult.a, mult.b) > 1)
    {
        int great = Rational::gcd(mult.a, mult.b);
        mult.b /= great;
        mult.a /= great;
    }
    return mult;
}
Rational operator/(const Rational& x, const Rational& y) {
    Rational mult(x.a * y.b, x.b * y.a);
    if ((x.b == 0) && (y.a < 0))
        mult.a = -x.a * y.b;
    while (Rational::gcd(mult.a, mult.b) > 1)
    {
        int great = Rational::gcd(mult.a, mult.b);
        mult.b /= great;
        mult.a /= great;
    }
    return mult;

}