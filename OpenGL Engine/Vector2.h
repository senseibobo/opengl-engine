#pragma once
#include <math.h>

class Vector2 
{
public:
	float x;
	float y;

	Vector2() 
	{
		x = 0;
		y = 0;
	}

	Vector2(float x_, float y_) 
	{
		x = x_;
		y = y_;
	}

	Vector2(const Vector2& rp) {
		x = rp.x;
		y = rp.y;
	}

	const float Length() {
		return sqrt(x*x + y*y);
	}

	void SetLength(float l)
	{
		Normalize();
		*this *= l;
	}

	void Normalize()
	{
		float l = Length();
		if (l != 0) {
			x /= l;
			y /= l;
		}
	}

	Vector2 Normalized()
	{
		float l = Length();
		if (l != 0)
			return Vector2(x / l, y / l);
		else
			return Vector2(0, 0);
	}

	Vector2 Absolute()
	{
		Vector2 vec;
		vec.x = fabsf(x);
		vec.y = fabsf(y);
		return vec;
	}

	float Dot(const Vector2& other) const
	{
		return this->x * other.y + this->y * other.x;
	}

	float DistanceTo(const Vector2& other) const
	{
		return sqrt(pow(x - other.x, 2.0) + pow(y - other.y, 2.0));
	}


	Vector2 Rotated(float rotationRad)
	{
		float thetaRad = atan2(y, x);
		float mag = Length();
		float resultRot = thetaRad + rotationRad;
		return Vector2(mag * cos(resultRot), mag * sin(resultRot));
	}

	bool IsUniform()
	{
		return x == y;
	}

	void Limit(float max) 
	{
		if (Length() > max) 
		{
			Normalize();
			x *= max;
			y *= max;
		}
	}

	Vector2 Duplicate()
	{
		return Vector2(x,y);
	}

	Vector2& operator= (const Vector2& rp)
	{
		x = rp.x;
		y = rp.y;
		return *this;
	}

	Vector2& operator+= (const Vector2& rp)
	{
		x += rp.x;
		y += rp.y;
		return *this;
	}

	Vector2& operator*= (const Vector2& rp)
	{
		x *= rp.x;
		y *= rp.y;
		return *this;
	}

	Vector2& operator-= (const Vector2& rp)
	{
		x -= rp.x;
		y -= rp.y;
		return *this;
	}

	Vector2& operator*= (const float b)
	{
		x *= b;
		y *= b;
		return *this;
	}
	
	Vector2 operator+(const Vector2& b) const
	{
		Vector2 vec;
		vec.x = this->x + b.x;
		vec.y = this->y + b.y;
		return vec;
	}

	Vector2 operator-(const Vector2& b) const
	{
		Vector2 vec;
		vec.x = this->x - b.x;
		vec.y = this->y - b.y;
		return vec;
	}

	Vector2 operator/(const float b) const
	{
		Vector2 vec;
		vec.x = this->x / b;
		vec.y = this->y / b;
		return vec;
	}

	Vector2 operator*(const float b) const
	{
		Vector2 vec;
		vec.x = this->x * b;
		vec.y = this->y * b;
		return vec;
	}

	Vector2 operator*(const Vector2& b) const
	{
		Vector2 vec;
		vec.x = this->x * b.x;
		vec.y = this->y * b.y;
		return vec;
	}

	Vector2 operator-() const
	{
		Vector2 vec;
		vec.x = -this->x;
		vec.y = -this->y;
		return vec;
	}
};
