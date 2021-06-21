#pragma once
#pragma once

#include <cmath>
#include <array>
#include <limits>
#include <string>
#include <memory>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>

#define NOMINMAX
#include <Windows.h>

//角度与弧度
#define PI	(3.1415926f)
#define D2R(d)	(PI / 180.0f * (d))
#define R2D(r)	(180.0f / PI * (r))

#ifdef RGB
#undef RGB
#endif
#define RGB(r, g, b) ((r) << 16 | (g) << 8 | (b) << 0) //颜色

#define RGBA(r, g, b, a) ((a) << 24 | (r) << 16 | (g) << 8 | (b) << 0) //透明度

//intensity
#define F2B(v)	((v) * 255)

#define RENDERER_DEBUG