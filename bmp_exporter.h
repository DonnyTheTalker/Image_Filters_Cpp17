#pragma once

#include "image.h"
#include "bmp_format.h"

#include <fstream>
#include <exception>

namespace BmpExporter
{

void AssignBmpHeader(unsigned char *bmp_header, const size_t file_size)
{
    bmp_header[bmp_header_format::ID_POS] = 'B';
    bmp_header[bmp_header_format::ID_POS + 1] = 'M';

    for (size_t i = 0; i < bmp_format::BYTES_OFFSET; ++i)
    {
        bmp_header[i + bmp_header_format::FILE_SIZE_POS] = file_size >> (i * bmp_format::BYTE);
    }

    bmp_header[bmp_header_format::DATA_POS] = bmp_format::BMP_HEADER_SIZE + bmp_format::DIB_HEADER_SIZE;
}

void AssignDibHeader(unsigned char *dib_header, const size_t width, const size_t height)
{
    dib_header[dib_header_format::SIZE_POS] = bmp_format::DIB_HEADER_SIZE;

    for (size_t i = 0; i < bmp_format::BYTES_OFFSET; ++i)
    {
        dib_header[dib_header_format::WIDTH_POS + i] = width >> (i * bmp_format::BYTE);
        dib_header[dib_header_format::HEIGHT_POS + i] = height >> (i * bmp_format::BYTE);
    }

    dib_header[dib_header_format::COLOR_PLANE_POS] = bmp_format::COLOR_PLANES;
    dib_header[dib_header_format::BITS_PER_PIXEL_POS] = bmp_format::BITS_PER_PIXEL;
}

void Export(const Image &image, const std::string &path) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);

    if (!file)
    {
        throw std::invalid_argument("Could not open an output file");
    }

    try
    {
        unsigned char bmp_padding[bmp_format::COLOR_CHANNELS] = {0};
        const size_t padding_size = image.GetPadding();

        const size_t file_size = bmp_format::BMP_HEADER_SIZE + bmp_format::DIB_HEADER_SIZE +
                                 image.GetWidth() * image.GetHeight() * bmp_format::COLOR_CHANNELS +
                                 padding_size * image.GetHeight();

        unsigned char bmp_header[bmp_format::BMP_HEADER_SIZE] = {0};
        unsigned char dib_header[bmp_format::DIB_HEADER_SIZE] = {0};

        AssignBmpHeader(bmp_header, file_size);
        AssignDibHeader(dib_header, image.GetWidth(), image.GetHeight());

        file.write(reinterpret_cast<char *>(bmp_header), bmp_format::BMP_HEADER_SIZE);
        file.write(reinterpret_cast<char *>(dib_header), bmp_format::DIB_HEADER_SIZE);

        for (size_t y = 0; y < image.GetHeight(); ++y)
        {
            for (size_t x = 0; x < image.GetWidth(); ++x)
            {
                auto [r, g, b] = image.GetColor(x, y);
                unsigned char colors[] = {static_cast<unsigned char>(b * 255.0f),
                                          static_cast<unsigned char>(g * 255.0f),
                                          static_cast<unsigned char>(r * 255.0f)};
                file.write(reinterpret_cast<char *>(colors), 3);
            }

            file.write(reinterpret_cast<char *>(bmp_padding), padding_size);
        }
    } catch (const std::exception &ex)
    {
        throw std::runtime_error("Error during writing image into output file");
    }
}
}  // namespace BmpExporter
