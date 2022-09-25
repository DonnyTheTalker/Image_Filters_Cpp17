#include "args_parser.h"
#include "image.h"
#include "bmp_exporter.h"
#include "bmp_importer.h"
#include "filters/filter.h"
#include "filters/filters_builder.h"

#include <exception>
#include <iostream>

void PrintHelpInfo() {
    std::cout << "Arguments format:" << std::endl;
    std::cout << "{program name} {input image path} {output image path}" << std::endl;
    std::cout << "[-{first filter name} [first parameter] [second parameter] ...]" << std::endl;
    std::cout << "[-{second filter name} [first parameter] [second parameter] ...]" << std::endl;
    std::cout << "Use as many filters as you want" << std::endl;

    std::cout << std::endl;

    std::cout << "Filters:" << std::endl;
    std::cout << "Crop (-crop width height)" << std::endl;
    std::cout << "Grayscale (-gs)" << std::endl;
    std::cout << "Negative (-neg)" << std::endl;
    std::cout << "Sharpening (-sharp)" << std::endl;
    std::cout << "Edge detection (-edge threshold)" << std::endl;
    std::cout << "Gaussian blur (-blur sigma)" << std::endl;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        PrintHelpInfo();
        return 0;
    }

    Image image;
    ArgsParser parser(argv + 1, argc - 1);

    std::string input_file_name;
    std::string output_file_name;

    try {
        input_file_name = parser.GetArgument<std::string>();
        output_file_name = parser.GetArgument<std::string>();
    } catch (const std::exception &ex) {
        std::cout << "Too few arguments given" << std::endl;
        return 0;
    }

    try {
        BmpImporter::Import(image, input_file_name);
    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
        return 0;
    }

    try {
        std::vector<std::unique_ptr<Filter>> filters;
        FiltersBuilder::Build(parser, filters);
        try {
            for (auto &filter : filters) {
                filter->Apply(image);
            }
        } catch (const std::exception &ex) {
            std::cout << "Error applying filters" << std::endl;
            return 0;
        }

    } catch (std::exception &ex) {
        std::cout << ex.what();
    }

    try {
        BmpExporter::Export(image, output_file_name);
    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
}
