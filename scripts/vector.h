//
// Created by Baka-tannn on 21/2/2025.
//
#pragma once

struct Vector
{
    double x, y;
    Vector() : x(0), y(0) {}
    Vector(double x, double y) : x(x), y(y) {}

    Vector operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y);
    }

    Vector operator*(double n) const
    {
        return Vector(x * n, y * n);
    }

};