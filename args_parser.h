#pragma once

#include <cstddef>
#include <string>
#include <sstream>

class ArgsParser
{
public:
    ArgsParser(char **args, size_t size);

    bool IsOver() const;

    template <typename T>
    T GetArgument()
    {
        if (IsOver())
        {
            throw std::invalid_argument("Too few arguments");
        }
        std::stringstream sx;
        T val;
        sx << args_[cur_++];
        if (!(sx >> val))
        {
            throw std::invalid_argument("Invalid command line argument");
        }
        return val;
    }

private:
    char **args_;
    size_t size_;
    size_t cur_;
};
