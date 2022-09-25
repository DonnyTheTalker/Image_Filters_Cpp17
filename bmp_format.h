#pragma once

namespace bmp_format
{
const size_t BYTE = 8;
const size_t BYTES_OFFSET = 4;
const size_t BITS_PER_PIXEL = 24;

const size_t COLOR_CHANNELS = 3;
const size_t COLOR_PLANES = 1;

const size_t BMP_HEADER_SIZE = 14;
const size_t DIB_HEADER_SIZE = 40;
}  // namespace bmp_format

namespace bmp_header_format
{
const size_t ID_POS = 0;
const size_t FILE_SIZE_POS = 2;
const size_t DATA_POS = 10;
}  // namespace bmp_header_format

namespace dib_header_format
{
const size_t SIZE_POS = 0;
const size_t WIDTH_POS = 4;
const size_t HEIGHT_POS = 8;
const size_t COLOR_PLANE_POS = 12;
const size_t BITS_PER_PIXEL_POS = 14;
}  // namespace dib_header_format
