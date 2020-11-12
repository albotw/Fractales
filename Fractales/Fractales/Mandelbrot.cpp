#include "Mandelbrot.h"
#include <Math.h>

Point generateMandelbrot(int n, Point p,int imgWidth, int imgHeight) {

	float c_reel = p.x;
	float c_img = p.y;

	float z_reel = 0;
	float z_img = 0;

	int i = 0;

	do {
		float temp = z_reel;
		z_reel = pow(z_reel, 2) - pow(z_img, 2) + c_reel;
		z_img = 2 * z_img * temp * c_img;
		i = i + 1;
	} while (pow(z_reel, 2) + pow(z_img, 2) <= 4 && i <= n);

	if (i == n) {
		p.r = 0.0f;
		p.g = 0.0f;
		p.b = 0.0f;
		return p;
	}
}


std::vector<Point> generateMandelbrot(float x_min, float x_max, float y_min, float y_max, float zoom, int width, int height, int iterations) {
	float zoom_x = width / (x_max - x_min);
	float zoom_y = height / (y_max - y_min);

	std::vector<Point> plan{ 0 };

	for (float i = x_min; i < x_max; i = i + 0.001f) {
		for (float j = y_min; j < y_max; j = j + 0.001f) {
			
			float c_reel = i ;
			float c_img = j;

			float z_reel = 0;
			float z_img = 0;

			int k = 0;

			do {
				float temp = z_reel;
				z_reel = pow(z_reel, 2) - pow(z_img, 2) + c_reel;
				z_img = 2 * z_img * temp + c_img;
				k++;
			} while (pow(z_reel, 2) + pow(z_img, 2) < 4 && k < 50);

			if (k == 50) {
				Point tmp{
					i, j, 0.0f,
					1.0f, 1.0f, 1.0f
				};
				plan.push_back(tmp);
			}
		}
	}

	return plan;
}

