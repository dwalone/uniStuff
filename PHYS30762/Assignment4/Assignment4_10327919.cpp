// PHYS 30762 Programming in C++
// Assignment 5
// Rutwik Mudholkar 08/03/21

// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
    // Make function to overload operator<< a friend
    friend std::ostream & operator<<(std::ostream &os, const complex &z);

    // Make function to overload operator>> a friend
    friend std::istream & operator>>(std::istream &is, complex &z);

private:
    double re,im;
public:
    // Constructors & destructor
    complex(){re=im=0;}
    complex(double real_part, double im_part){re=real_part; im=im_part;}
    ~complex(){}

    // Return real component
    double real() const {return re;}

    // Return imaginary component
    double imaginary() const {return im;}

    // Return modulus
    double modulus() const {return std::pow(std::pow(re,2)+std::pow(im,2), 0.5);}

    // Return argument
    double argument() const {return std::atan2(im, re);}

    // Return complex conjugate
    complex conjugate() const {return complex(re, -im);}

    // Overload + operator for addition
    complex operator+(const complex &z)
    {
        complex temp{re+z.re, im+z.im};
        return temp;
    } 

    // Overload - operator for subtraction
    complex operator-(const complex &z)
    {
        complex temp{re-z.re, im-z.im};
        return temp;
    }

    // Overload * operator for multiplication, z1*z2
    complex operator*(const complex &z)
    {
        complex temp{re*z.re - im*z.im, re*z.im + im*z.re};
        return temp;
    }

     // Overload / operator for division, z1/z2
    complex operator/(const complex &z)
    {
        double temp_re = (re*z.re+im*z.im)/(std::pow(z.re,2)+std::pow(z.im,2));
        double temp_im = (im*z.re-re*z.im)/(std::pow(z.re,2)+std::pow(z.im,2));
        complex temp{temp_re, temp_im};
        return temp;
    }

};

// Function to overload << operator for complex numbers
std::ostream& operator<<(std::ostream &os, const complex &z)
{
    if (z.im<0) {os<<z.re<<z.im<<"i";}
    else {os<<z.re<<"+"<<z.im<<"i";}
    return os;
}

// Function to overload >> operator for complex numbers
std::istream& operator>>(std::istream &is, complex &z)
{
    std::cout<<"enter real part : ";
    is>>z.re;
    std::cout<<"enter imaginary part : ";
    is>>z.im; 
    return is;
}

int main()
{  
    std::cout.precision(3);

    // Create two complex numbers
    complex a{3, 4};
    complex b{1, -2};

    // istream demonstration
    complex z_istream_demo;
    std::cin>>z_istream_demo;
    std::cout<<"z_istream_demo = "<<z_istream_demo<<std::endl;
    std::cout<<std::endl;

    // Get real and imaginary components, modulus and argument
    double a_real{a.real()};
    double a_imaginary{a.imaginary()};
    double a_modulus{a.modulus()};
    double a_argument{a.argument()};
    double b_real{b.real()};
    double b_imaginary{b.imaginary()};
    double b_modulus{b.modulus()};
    double b_argument{b.argument()};

    // Get conjugates
    complex a_conjugate{a.conjugate()};
    complex b_conjugate{b.conjugate()};

    // Get sum, difference, product and quotient of a and b
    complex sum_a_b{a+b};
    complex difference_a_b{a-b};
    complex product_a_b{a*b};
    complex quotient_a_b{a/b};

    // Print out results, also demonstrating use of overloaded operator<<
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"a* = "<<a_conjugate<<std::endl;
    std::cout<<"Re(a) = "<<a_real<<std::endl;
    std::cout<<"Im(a) = "<<a_imaginary<<std::endl;
    std::cout<<"|a| = "<<a_modulus<<std::endl;
    std::cout<<"Arg(a) = "<<a_argument<<" rad"<<std::endl;
    std::cout<<std::endl;

    std::cout<<"b = "<<b<<std::endl;
    std::cout<<"b* = "<<b_conjugate<<std::endl;  
    std::cout<<"Re(b) = "<<b_real<<std::endl;
    std::cout<<"Im(b) = "<<b_imaginary<<std::endl;
    std::cout<<"|b| = "<<b_modulus<<std::endl;
    std::cout<<"Arg(b) = "<<b_argument<<" rad"<<std::endl; 
    std::cout<<std::endl;

    // Show results of overloading arithmetic operators
    std::cout<<"a + b = "<<sum_a_b<<std::endl;
    std::cout<<"a - b = "<<difference_a_b<<std::endl;
    std::cout<<"a * b = "<<product_a_b<<std::endl;
    std::cout<<"a / b = "<<quotient_a_b<<std::endl;

    return 0;
}