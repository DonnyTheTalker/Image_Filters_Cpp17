#include "args_parser.h"

ArgsParser::ArgsParser(char **args, size_t size) : args_(args), size_(size), cur_(0) {
}

bool ArgsParser::IsOver() const {
    return cur_ >= size_;
}
