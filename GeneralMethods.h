#ifndef ALGORITHMS_PROJECT_1_GENERALMETHODS_H
#define ALGORITHMS_PROJECT_1_GENERALMETHODS_H
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

char isGraphDirected() noexcept(false);
void getGraphInfo(int&, int&) noexcept(false);

class generalException: public std::exception
{
public:
    const char* what() const noexcept override { return "General exception."; }
};

class invalidInputException: public generalException
{
    const char* what() const noexcept override { return "Invalid input."; }
};

#endif //ALGORITHMS_PROJECT_1_GENERALMETHODS_H