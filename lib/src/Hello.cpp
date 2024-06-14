#include <fmt/format.h>
#include <fmt/chrono.h>
#include "Hello.h"

void Hello::print(std::ostream& output) const
{
    output << fmt::format("\"{}\"\n\n", title);
}