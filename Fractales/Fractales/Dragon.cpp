#include "Dragon.h"

Point milieu_dragon(Point a, Point b) {
	return Point{
		((a.x + b.x) / 2.0f) + ((b.y - a.y) / 2.0f),
		((a.y + b.y) / 2.0f) - ((b.x - a.x) / 2.0f),
		(a.z + b.z) / 2.0f + (b.z - a.z) / 2.0f,
		a.r + 0.2f * b.r,
		a.g + 0.2f * b.g,
		a.b + 0.2f * b.b
	};
}

void generateDragon(int n, Point A, Point B, std::vector<Point>& vertices) {
	if (n != 0) {
		Point C = milieu_dragon(A, B);

		generateDragon(n - 1, A, C, vertices);
		generateDragon(n - 1, B, C, vertices);
	}
	else {
		vertices.push_back(A);
		vertices.push_back(B);
	}
}