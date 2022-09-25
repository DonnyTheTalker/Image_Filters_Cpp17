#pragma once

struct Color
{
    Color() = default;
    Color(float r, float g, float b);
    Color(const Color& other) = default;
    Color& operator=(const Color& other) = default;
    ~Color() = default;

    float r;
    float g;
    float b;
};