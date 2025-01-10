#include "perlinNoise.h"

float PerlinNoise::perlin2D(int height, int width, float scale)
{
	//Point
	float xf = (float)width * scale;
	float yf = (float)height * scale;

	//Grid Points
	int x0 = (int)xf;
	int y0 = (int)yf;
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	//Gradients
	Vector gradient0 = getGradient(x0, y1);
	Vector gradient1 = getGradient(x1, y1);
	Vector gradient2 = getGradient(x0, y0);
	Vector gradient3 = getGradient(x1, y0);

	//Distance Vectors
	Vector dv0 = getVectorDistance(xf, x0, yf, y1);
	Vector dv1 = getVectorDistance(xf, x1, yf, y1);
	Vector dv2 = getVectorDistance(xf, x0, yf, y0);
	Vector dv3 = getVectorDistance(xf, x1, yf, y0);
	 
	//Fading
	float fadeX = fade(xf - floor(xf));
	float fadeY = fade(yf - floor(yf));

	//Dot Product
	float dp0 = dotProduct(gradient0, dv0);
	float dp1 = dotProduct(gradient1, dv1);
	float dp2 = dotProduct(gradient2, dv2);
	float dp3 = dotProduct(gradient3, dv3);

	//X-Axis Lerp
	float lerpTop = lerp(dp0, dp1, fadeX);
	float lerpBottom = lerp(dp2, dp3, fadeX);

	//Final Interpolation
	float noiseVal = lerp(lerpTop, lerpBottom, fadeY);
	//std::cout << "Noise Value: " << noiseVal << "\n";
	return noiseVal;
}

float PerlinNoise::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

float PerlinNoise::fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::dotProduct(Vector gradient, Vector gridPoint)
{
	return (gradient.x * gridPoint.x) + (gradient.y * gridPoint.y);
}

Vector PerlinNoise::getGradient(int x, int y)
{
	int h = hash(x, y);
	float angle = (h / 255.0f) * 2.0f * 3.14159265358979323846;
	return Vector(cos(angle), sin(angle));
}

int PerlinNoise::hash(int x, int y)
{
	return (x * 73856093 ^ y * 19349663) & 255;
}

Vector PerlinNoise::getVectorDistance(float xf, float x, float yf, float y)
{
	return Vector(xf - x, yf - y);
}