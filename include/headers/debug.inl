#include "debug.h"
#include <iostream>

template <typename... Args>
void log(const Args &...args)
{
    std::cout << "[LOG]: ";
    (std::cout << ... << args) << std::endl;
}

template <typename... Args>
void warning(const Args &...args)
{
    std::cout << "[WARNING]: ";
    (std::cout << ... << args) << std::endl;
}

template <typename... Args>
void error(const Args &...args)
{
    std::cout << "[ERROR]: ";
    (std::cout << ... << args) << std::endl;
}