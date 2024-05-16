struct Complex {
    double real;
    double im;

    Complex() : real(0.0), im(0.0) {}

    Complex(double r, double i) : real(r), im(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, im + other.im);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, im - other.im);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - im * other.im, real * other.im + im * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.im * other.im;
        return Complex((real * other.real + im * other.im) / denominator, (im * other.real - real * other.im) / denominator);
    }
};