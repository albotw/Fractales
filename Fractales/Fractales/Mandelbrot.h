#pragma once
#include <iostream>
#include <vector>
#include "Point.h"

std::vector<Point> generateMandelbrot(float x_min, float x_max, float y_min, float y_max, float zoom, int width, int height, int iterations);