
#include <iostream>
#include <conio.h>

#include "four_arithmetic.h"

void fun1()
{
    std::cout << "Hello, C++" << std::endl;

    int a = 0;
    int b = 0;
    int c = 0;

    std::cout << "Enter a: ";
    std::cin >> a;

    std::cout << "Enter b: ";
    std::cin >> b;

    c = a + b;

    std::cout << "a + b = " << a << " + " << b << " = " << c << std::endl;
}

void fun2()
{
    int a = 0;
    int b = 0;
    int c = 0;

    std::cout << "Enter a: ";
    std::cin >> a;

    std::cout << "Enter b: ";
    std::cin >> b;

    c = add(a, b);

    std::cout << "add(a, b) = " << a << " + " << b << " = " << c << std::endl;
}

int main()
{
    fun2();
    return 0;
}
