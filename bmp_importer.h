#pragma once
#include "image.h"
#include "bmp_format.h"

#include <fstream>
#include <exception>

namespace BmpImporter
{
void Import(Image &image, const std::string &path)
{
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);

    if (!file)
    {
        throw std::invalid_argument("Could not open an input file");
    }

    image.Clear();

    unsigned char bmp_header[bmp_format::BMP_HEADER_SIZE];
    unsigned char dib_header[bmp_format::DIB_HEADER_SIZE];

    file.read(reinterpret_cast<char *>(bmp_header), bmp_format::BMP_HEADER_SIZE);
    file.read(reinterpret_cast<char *>(dib_header), bmp_format::DIB_HEADER_SIZE);

    if (!(bmp_header[0] == 'B' && bmp_header[1] == 'M'))
    {
        throw std::invalid_argument("Incorrect input file");
    }

    try
    {
        size_t new_width = 0;
        size_t new_height = 0;

        for (size_t i = 0; i < bmp_format::BYTES_OFFSET; ++i)
        {
            new_width += dib_header[dib_header_format::WIDTH_POS + i] << (i * bmp_format::BYTE);
            new_height += dib_header[dib_header_format::HEIGHT_POS + i] << (i * bmp_format::BYTE);
        }

        image.Resize(new_width, new_height);

        const size_t padding_size = image.GetPadding();

        for (size_t y = 0; y < image.GetHeight(); ++y)
        {
            for (size_t x = 0; x < image.GetWidth(); ++x)
            {
                unsigned char colors[3];
                file.read(reinterpret_cast<char *>(colors), 3);
                image.SetColor(x, y,
                               Color(static_cast<float>(colors[2]) / 255.0f, static_cast<float>(colors[1]) / 255.0f,
                                     static_cast<float>(colors[0]) / 255.0f));
            }

            file.ignore(padding_size);
        }
    } catch (const std::exception &ex)
    {
        throw std::runtime_error("Error reading image from file");
    }
}
}  // namespace BmpImporter