#pragma once

struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2D() {}
	Vector2D(const float& x, const float& y) : x(x), y(y) {}

	//Negative vector
	Vector2D operator-() const;

	//Vector addition and subtraction
	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);

	//Scalar multiplication and division
	Vector2D operator*(const float& scalar) const;
	Vector2D operator/(const float& scalar) const;
	Vector2D& operator*=(const float& scalar);
	Vector2D& operator/=(const float& scalar);
};

//Lhs scalar multiplication and division
Vector2D operator*(const float& scalar, const Vector2D& vector);
Vector2D operator/(const float& scalar, const Vector2D& vector);
