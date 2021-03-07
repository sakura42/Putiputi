#include "Object.h"

Object::Object(float x, float y, float size){
	this->x = x;
	this->y = y;
	this->size = size;
}

Object::Object(){
	Object(0,0,0);
}

bool Object::IsHit(Object* obj)
{
	float dis = this->Distance(obj);
	if (dis < this->GetSize() / 2 + obj->GetSize() / 2) {
		return true;
	}
	else {
		return false;
	}
}
float Object::Distance(Object* obj)
{
	float difX = (this->x + this->GetSize() / 2) - (obj->x + obj->GetSize() / 2);
	float difY = (this->y + this->GetSize() / 2) - (obj->y + obj->GetSize() / 2);
	return sqrt(difX * difX + difY * difY);
}
float Object::Distance(float x, float y, float size)
{
	float difX = (this->x + this->GetSize() / 2) - (x + size / 2);
	float difY = (this->y + this->GetSize() / 2) - (y + size / 2);
	return sqrt(difX * difX + difY * difY);
}

float Object::Distance(float x, float y)
{
	return this->Distance(x, y, 0);
}

void Object::SetX(float inx){
	this->x = inx;
}
void Object::SetY(float iny) {
	this->y = iny;
}

float Object::GetX() {
	return this->x;
}
float Object::GetY() {
	return this->y;
}
float Object::GetSize()
{
	return this->size;
}
void Object::SetSize(float inSize)
{
	this->size = inSize;
}

