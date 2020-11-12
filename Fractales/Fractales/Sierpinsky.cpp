#include "Sierpinsky.h"

Point milieu_sierpinsky(Point a, Point b) {
	return Point{
		(a.x + b.x) / 2.0f,
		(a.y + b.y) / 2.0f,
		(a.z + b.z) / 2.0f,
		a.r + 0.5f * b.r,
		a.g + 0.5f * b.g,
		a.b + 0.5f * b.b
	};
}

void generateSierpinsky(int n, Point A, Point B, Point C, std::vector<Point> &vertices) {
	if (n != 0) {
		Point A_ = milieu_sierpinsky(A, B);
		Point B_ = milieu_sierpinsky(A, C);
		Point C_ = milieu_sierpinsky(B, C);
		generateSierpinsky(n - 1, A, A_, B_, vertices);
		generateSierpinsky(n - 1, A_, B, C_, vertices);
		generateSierpinsky(n - 1, B_, C_, C, vertices);
	}
	else {
		vertices.push_back(A);
		vertices.push_back(B);
		vertices.push_back(C);
	}
}