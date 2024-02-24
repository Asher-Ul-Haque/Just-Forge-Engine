#include <cmath>
#include "../../TheMachine/PhysicsEngine/Vector2D.h"
#include <iostream>

//Construction
Vector2D::Vector2D() {};
Vector2D::Vector2D(float X, float Y): x(X), y(Y){};
//---------------------------------

//METHODS-
//Operator Overload
bool Vector2D::operator == (const Vector2D& RHS) const
{
    return (x == RHS.x && y == RHS.y);
};
bool Vector2D::operator != (const Vector2D& RHS) const
{
    return !(x == RHS.x && y == RHS.y);
};
// - - - - - -
Vector2D Vector2D::operator + (const Vector2D& RHS) const
{
    return Vector2D(x + RHS.x, y + RHS.y);
};
Vector2D Vector2D::operator - (const Vector2D& RHS) const
{
    return Vector2D(x - RHS.x, y - RHS.y);
};
Vector2D Vector2D::operator * (const float VAL) const
{
    return Vector2D(x * VAL, y * VAL);
};
Vector2D Vector2D::operator / (const float VAL) const
{
    return Vector2D(x / VAL, y / VAL);
};
// - - - - - -
void Vector2D::operator += (const Vector2D& RHS)
{
    x += RHS.x;
    y += RHS.y;
}
void Vector2D::operator -= (const Vector2D& RHS)
{
    x -= RHS.x;
    y -= RHS.y;
}
void Vector2D::operator *= (const float VAL)
{
    x *= VAL;
    y *= VAL;
}
void Vector2D::operator /= (const float VAL)
{
    x /= VAL;
    y /= VAL;
}

//Other Methods
float Vector2D::distanceSquared(const Vector2D& RHS) const
{
    return ((float) x * RHS.x + y * RHS.y);
}
float Vector2D::distance(const Vector2D& RHS) const
{
    return sqrtf((float) abs(x - RHS.x) + abs(y - RHS.y));
}
float Vector2D::lengthSquared() const
{
    return ((float) x * x + y * y);
}
float Vector2D::length() const
{
    return sqrtf((float) x * x + y * y);
}
float Vector2D::dotMultiply(const Vector2D &RHS)
{
    return x * RHS.x + y * RHS.y;
}
Vector2D Vector2D::normalise()
{
    float length = sqrtf((float) x * x + y * y);
    return Vector2D(x/length, y/length);
}
float Vector2D::getAngle(const Vector2D &RHS)
{
    return atan2(RHS.y - y, RHS.x - x);
}
Vector2D Vector2D::rotate(const float ANGLE)
{
    float sin = std::sin(ANGLE);
    float cos = std::cos(ANGLE);
    return Vector2D(x * cos, y * sin);
}
float Vector2D::crossMultiply2D(const Vector2D &RHS)
{
    return x*RHS.y - y*RHS.x;
}
