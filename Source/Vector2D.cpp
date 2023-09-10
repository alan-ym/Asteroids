#include "Vector2D.h"

Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return Vector2D(x - other.x, y - other.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2D Vector2D::operator*(const float& scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(const float& scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

Vector2D& Vector2D::operator*=(const float& scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2D operator*(const float& scalar, const Vector2D& vector)
{
	return vector * scalar;
}

Vector2D operator/(const float& scalar, const Vector2D& vector)
{
	return vector / scalar;
}
