#pragma once
#include"tgaimage.h"
#include"geometry.h"

struct TriangleFace
{
	Vec2i pts[3];
	float depth;
};

class MyCamera
{
public:
	static Vec2i world2screen(Vec3f, TGAImage image);
};


class MyLumination
{
private:
	int light_state = 0;
public:
	float getRenderIntensity(Vec3f light_dir);
};

class MyDrawAlgorithms
{
public:
	static void line(Vec2i pt1, Vec2i pt2, TGAImage& modyfy_image, TGAColor color);
	static void triangle(TriangleFace face,float *z_buffers, TGAImage& modyfy_image, TGAColor color);
	
};
