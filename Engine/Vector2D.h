#ifndef SUPERMARIO_VECTOR2D_H
#define SUPERMARIO_VECTOR2D_H
//---------------------------------

class Vector2D
{
public:
    //Data
    float x = 0;
    float y = 0;
    //---------------------------------

    //Construction
    Vector2D();
    Vector2D(float X, float Y);
    //---------------------------------

    //METHODS-
    //Operator Overload
    bool operator == (const Vector2D& RHS) const;
    bool operator != (const Vector2D& RHS) const;
    // - - - - - -
    Vector2D operator + (const Vector2D& RHS) const;
    Vector2D operator - (const Vector2D& RHS) const;
    Vector2D operator / (const float VAL) const;
    Vector2D operator * (const float VAL) const;
    // - - - - - -
    void operator += (const Vector2D& RHS);
    void operator -= (const Vector2D& RHS);
    void operator *= (const float VAL);
    void operator /= (const float VAL);
    // - - - - - -
    float crossMultiply2D(const Vector2D& RHS);
    float dotMultiply(const Vector2D& RHS);

    //other methods
    float distanceSquared(const Vector2D& RHS) const;
    float distance(const Vector2D& RHS) const;
    float lengthSquared() const;
    float length() const;
    Vector2D normalise();
    float getAngle(const Vector2D& RHS);
    Vector2D rotate(const float ANGLE);
};
//---------------------------------

#endif //SUPERMARIO_VECTOR2D_H
