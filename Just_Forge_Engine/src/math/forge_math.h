#pragma once
#include "defines.h"
#include "math_types.h"


// - - - |  CONSTANTS AND GENERAL FUNCTIONS  | - - -


// - - - CONSTANTS
#define FORGE_PI 3.14159265358979323846f
#define FORGE_PI_2 2.0f * FORGE_PI
#define FORGE_PI_4 4.0f * FORGE_PI
#define FORGE_HALF_PI 0.5f * FORGE_PI
#define FORGE_QUARTER_PI 0.25f * FORGE_PI
#define FORGE_ONE_OVER_PI 1.0f / FORGE_PI
#define FORGE_ONE_OVER_TWO_PI 1.0f / FORGE_PI_2
#define FORGE_SQRT_2 1.41421356237309504880f
#define FORGE_SQRT_3 1.73205080756887729352f
#define FORGE_SQRT_1_OVER_2 0.70710678118654752440f
#define FORGE_SQRT_1_OVER_3 0.57735026918962576450f
#define FORGE_DEG_TO_RAD FORGE_PI / 180.0f
#define FORGE_RAD_TO_DEG 180.0f / FORGE_PI
#define FORGE_EPSILON 1.192092896e-07f
#define FORGE_EPSILON_SQUARED FORGE_EPSILON * FORGE_EPSILON
#define FORGE_INFINITY 1e30f;


// - - - Functions - - -

// - - - GENERAL FUNCTIONS
FORGE_API float forge_sin(float ANGLE);
FORGE_API float forge_cos(float ANGLE);
FORGE_API float forge_tan(float ANGLE);
FORGE_API float forge_sqrt(float VALUE);
FORGE_API float forge_abs(float VALUE);

// - - - Utility functions
FORGE_INLINE bool8 isPowerOfTwo(uint32 VALUE) 
{ 
    return ((VALUE & (VALUE - 1)) == 0) && (VALUE != 0); 
}

FORGE_API int forgeRandom();
FORGE_API int forgeRandomRange(float MIN, float MAX);
FORGE_API float forgeFloatRandom();
FORGE_API float forgeFloatRandomRange(float MIN, float MAX);


// - - - | Vectors | - - - 


// - - - Vector2D - - -

// - - - Creation
FORGE_INLINE Vector2D createVector2D(float X, float Y)
{
    Vector2D result = {};
    result.x = X;
    result.y = Y;
    //return (Vector2D){X, Y};
    return result;
}

// - - - Common Vectors
FORGE_INLINE Vector2D zeroVector2D()
{
    return createVector2D(0.0f, 0.0f);
    //return (Vector2D){0.0f, 0.0f};
}

FORGE_INLINE Vector2D oneVector2D()
{
    return createVector2D(1.0f, 1.0f);
    //return (Vector2D){1.0f, 1.0f};
}

FORGE_INLINE Vector2D upVector2D()
{
    return createVector2D(0.0f, 1.0f);
    //return (Vector2D){0.0f, 1.0f};
}

FORGE_INLINE Vector2D rightVector2D()
{
    return createVector2D(1.0f, 0.0f);
    //return (Vector2D){1.0f, 0.0f};
}

FORGE_INLINE Vector2D downVector2D()
{
    return createVector2D(0.0f, -1.0f);
    //return (Vector2D){0.0f, -1.0f};
}

FORGE_INLINE Vector2D leftVector2D()
{
    return createVector2D(-1.0f, 0.0f);
    //return (Vector2D){-1.0f, 0.0f};
}

// - - - Operations
FORGE_INLINE Vector2D addVector2D(Vector2D A, Vector2D B)
{
    return createVector2D(A.x + B.x, A.y + B.y);
    //return (Vector2D){A.x + B.x, A.y + B.y};
}

FORGE_INLINE Vector2D subtractVector2D(Vector2D A, Vector2D B)
{
    return createVector2D(A.x - B.x, A.y - B.y);
    //return (Vector2D){A.x - B.x, A.y - B.y};
}

FORGE_INLINE Vector2D multiplyVector2D(Vector2D A, Vector2D B)
{
    return createVector2D(A.x * B.x, A.y * B.y);
    //return (Vector2D){A.x * B.x, A.y * B.y};
}

FORGE_INLINE float dotProductVector2D(Vector2D A, Vector2D B)
{
    return A.x * B.x + A.y * B.y;
}

FORGE_INLINE Vector2D divideVector2D(Vector2D A, Vector2D B)
{
    return createVector2D(A.x / B.x, A.y / B.y);
    //return (Vector2D){A.x / B.x, A.y / B.y};
}

FORGE_INLINE Vector2D scaleVector2D(Vector2D A, float SCALAR)
{
    return createVector2D(A.x * SCALAR, A.y * SCALAR);
    //return (Vector2D){A.x * SCALAR, A.y * SCALAR};
}

FORGE_INLINE float lengthSquaredVector2D(Vector2D A)
{
    return A.x * A.x + A.y * A.y;
}

FORGE_INLINE float lengthVector2D(Vector2D A)
{
    return forge_sqrt(lengthSquaredVector2D(A));
}

FORGE_INLINE void normalizeVector2D(Vector2D* A)
{
    const float length = lengthVector2D(*A);
    A->x /= length;
    A->y /= length;
}

FORGE_INLINE Vector2D normalizedVector2D(Vector2D A)
{
    normalizeVector2D(&A);
    return A;
}

FORGE_INLINE bool8 compareVector2D(Vector2D A, Vector2D B, float TOLERANCE)
{
    if (forge_abs(A.x - B.x) > TOLERANCE) 
    {
        return FALSE;
    }
    if (forge_abs(A.y - B.y) > TOLERANCE) 
    {
        return FALSE;
    }
    return TRUE;
}

FORGE_INLINE float distanceSquaredVector2D(Vector2D A, Vector2D B)
{
    return lengthSquaredVector2D(subtractVector2D(A, B));
}

FORGE_INLINE float distanceVector2D(Vector2D A, Vector2D B)
{
    return forge_sqrt(distanceSquaredVector2D(A, B));
}


// - - - Vector3D - - -

// - - - Creation
FORGE_INLINE Vector3D createVector3D(float X, float Y, float Z)
{
    Vector3D result = {};
    result.x = X;
    result.y = Y;
    result.z = Z;
    //return (Vector3D){X, Y, Z};
    return result;
}

// - - - Conversion
FORGE_INLINE Vector4D vector3DToVector4D(Vector3D A, float W)
{
    return createVector4D(A.x, A.y, A.z, W);
}

// - - - Common Vectors
FORGE_INLINE Vector3D zeroVector3D()
{
    return createVector3D(0.0f, 0.0f, 0.0f);
    //return (Vector3D){0.0f, 0.0f, 0.0f};
}

FORGE_INLINE Vector3D oneVector3D()
{
    return createVector3D(1.0f, 1.0f, 1.0f);
    //return (Vector3D){1.0f, 1.0f, 1.0f};
}

FORGE_INLINE Vector3D upVector3D()
{
    return createVector3D(0.0f, 1.0f, 0.0f);
    //return (Vector3D){0.0f, 1.0f, 0.0f};
}

FORGE_INLINE Vector3D rightVector3D()
{
    return createVector3D(1.0f, 0.0f, 0.0f);
    //return (Vector3D){1.0f, 0.0f, 0.0f};
}

FORGE_INLINE Vector3D forwardVector3D()
{
    return createVector3D(0.0f, 0.0f, -1.0f);
    //return (Vector3D){0.0f, 0.0f, -1.0f};
}

FORGE_INLINE Vector3D downVector3D()
{
    return createVector3D(0.0f, -1.0f, 0.0f);
    //return (Vector3D){0.0f, -1.0f, 0.0f};
}

FORGE_INLINE Vector3D leftVector3D()
{
    return createVector3D(-1.0f, 0.0f, 0.0f);
    //return (Vector3D){-1.0f, 0.0f, 0.0f};
}

FORGE_INLINE Vector3D backVector3D()
{
    return createVector3D(0.0f, 0.0f, 1.0f);
    //return (Vector3D){0.0f, 0.0f, 1.0f};
}

// - - - Operations
FORGE_INLINE Vector3D addVector3D(Vector3D A, Vector3D B)
{
    return createVector3D(A.x + B.x, A.y + B.y, A.z + B.z);
    //return (Vector3D){A.x + B.x, A.y + B.y, A.z + B.z};
}

FORGE_INLINE Vector3D subtractVector3D(Vector3D A, Vector3D B)
{
    return createVector3D(A.x - B.x, A.y - B.y, A.z - B.z);
    //return (Vector3D){A.x - B.x, A.y - B.y, A.z - B.z};
}

FORGE_INLINE Vector3D multiplyVector3D(Vector3D A, Vector3D B)
{
    return createVector3D(A.x * B.x, A.y * B.y, A.z * B.z);
    //return (Vector3D){A.x * B.x, A.y * B.y, A.z * B.z};
}

FORGE_INLINE float dotProductVector3D(Vector3D A, Vector3D B)
{
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

FORGE_INLINE Vector3D crossProductVector3D(Vector3D A, Vector3D B)
{
    return createVector3D(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
    //return (Vector3D){A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x};
}

FORGE_INLINE Vector3D divideVector3D(Vector3D A, Vector3D B)
{
    return createVector3D(A.x / B.x, A.y / B.y, A.z / B.z);
    //return (Vector3D){A.x / B.x, A.y / B.y, A.z / B.z};
}

FORGE_INLINE Vector3D scaleVector3D(Vector3D A, float SCALAR)
{
    return createVector3D(A.x * SCALAR, A.y * SCALAR, A.z * SCALAR);
    //return (Vector3D){A.x * SCALAR, A.y * SCALAR, A.z * SCALAR};
}

FORGE_INLINE float lengthSquaredVector3D(Vector3D A)
{
    return A.x * A.x + A.y * A.y + A.z * A.z;
}

FORGE_INLINE float lengthVector3D(Vector3D A)
{
    return forge_sqrt(lengthSquaredVector3D(A));
}

FORGE_INLINE void normalizeVector3D(Vector3D* A)
{
    const float length = lengthVector3D(*A);
    A->x /= length;
    A->y /= length;
    A->z /= length;
}

FORGE_INLINE Vector3D normalizedVector3D(Vector3D A)
{
    normalizeVector3D(&A);
    return A;
}


// - - - Vector4D - - -

// - - - Creation
FORGE_INLINE Vector4D createVector4D(float X, float Y, float Z, float W)
{
    Vector4D result = {};
    result.x = X;
    result.y = Y;
    result.z = Z;
    result.w = W;
    //return (Vector4D){X, Y, Z, W};
    return result;
}

// - - - Conversion
FORGE_INLINE Vector3D vector4DToVector3D(Vector4D A)
{
    return createVector3D(A.x, A.y, A.z);
}

// - - - Common Vectors
FORGE_INLINE Vector4D zeroVector4D()
{
    return createVector4D(0.0f, 0.0f, 0.0f, 0.0f);
    //return (Vector4D){0.0f, 0.0f, 0.0f, 0.0f};
}

FORGE_INLINE Vector4D oneVector4D()
{
    return createVector4D(1.0f, 1.0f, 1.0f, 1.0f);
    //return (Vector4D){1.0f, 1.0f, 1.0f, 1.0f};
}

// - - - Operations
FORGE_INLINE Vector4D addVector4D(Vector4D A, Vector4D B)
{
    return createVector4D(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
    //return (Vector4D){A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w};
}

FORGE_INLINE Vector4D subtractVector4D(Vector4D A, Vector4D B)
{
    return createVector4D(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);
    //return (Vector4D){A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w};
}

FORGE_INLINE Vector4D multiplyVector4D(Vector4D A, Vector4D B)
{
    return createVector4D(A.x * B.x, A.y * B.y, A.z * B.z, A.w * B.w);
    //return (Vector4D){A.x * B.x, A.y * B.y, A.z * B.z, A.w * B.w};
}

FORGE_INLINE float dotProductVector4D(Vector4D A, Vector4D B)
{
    return A.x * B.x + A.y * B.y + A.z * B.z + A.w * B.w;
}

FORGE_INLINE float dotProductWithFloats(float A_0, float A_1, float A_2, float A_3, float B_0, float B_1, float B_2, float B_3)
{
    return A_0 * B_0 + A_1 * B_1 + A_2 * B_2 + A_3 * B_3;
}

FORGE_INLINE Vector4D divideVector4D(Vector4D A, Vector4D B)
{
    return createVector4D(A.x / B.x, A.y / B.y, A.z / B.z, A.w / B.w);
    //return (Vector4D){A.x / B.x, A.y / B.y, A.z / B.z, A.w / B.w};
}

FORGE_INLINE Vector4D scaleVector4D(Vector4D A, float SCALAR)
{
    return createVector4D(A.x * SCALAR, A.y * SCALAR, A.z * SCALAR, A.w * SCALAR);
    //return (Vector4D){A.x * SCALAR, A.y * SCALAR, A.z * SCALAR, A.w * SCALAR};
}

FORGE_INLINE float lengthSquaredVector4D(Vector4D A)
{
    return A.x * A.x + A.y * A.y + A.z * A.z + A.w * A.w;
}

FORGE_INLINE float lengthVector4D(Vector4D A)
{
    return forge_sqrt(lengthSquaredVector4D(A));
}

FORGE_INLINE void normalizeVector4D(Vector4D* A)
{
    const float length = lengthVector4D(*A);
    A->x /= length;
    A->y /= length;
    A->z /= length;
    A->w /= length;
}

FORGE_INLINE Vector4D normalizedVector4D(Vector4D A)
{
    normalizeVector4D(&A);
    return A;
}
