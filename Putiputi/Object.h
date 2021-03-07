#pragma once
#include <cmath>

class Object{
public:
	Object(float x, float y, float size);
	Object();

	bool IsHit(Object* obj);
	float Distance(Object* obj);
	float Distance(float x, float y, float size);
	float Distance(float x, float y);

	float GetX();
	float GetY();
	void SetX(float inx);
	void SetY(float iny);
	float GetSize();
	void SetSize(float inSize);

protected:
	float x;
	float y;
	float size;
};

