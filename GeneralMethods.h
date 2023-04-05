#ifndef ALGORITHMS_PROJECT_1_GENERALMETHODS_H
#define ALGORITHMS_PROJECT_1_GENERALMETHODS_H
#include "Graph.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Graph getGraphInfo() noexcept(false);

class generalException: public std::exception
{
public:
    const char* what() const noexcept override { return "General exception."; }
};

class invalidInputException: public generalException
{
public:
    const char* what() const noexcept override { return "Invalid input"; }
};

#endif //ALGORITHMS_PROJECT_1_GENERALMETHODS_H