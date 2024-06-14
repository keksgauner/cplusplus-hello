#pragma once

#include <string>
#include <iostream>

struct Hello
{
    std::string title;

    void print(std::ostream& output) const;
};