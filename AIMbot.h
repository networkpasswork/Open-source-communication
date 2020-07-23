#pragma once
#include<windows.h>
#include<iostream>
#include<shlwapi.h>
#pragma comment (lib,"Shlwapi.lib")
using namespace std;
struct FVector //ÉèÖÃ×ø±ê
{
	float	X;
	float	Y;
	float	Z;

	inline FVector()
		: X(0), Y(0), Z(0) {
	}
	inline FVector(float x, float y, float z) : X(x), Y(y), Z(z) {}

	__forceinline FVector operator-(const FVector& V) {
		return FVector(X - V.X, Y - V.Y, Z - V.Z);
	}
	__forceinline FVector operator+(const FVector& V) {
		return FVector(X + V.X, Y + V.Y, Z + V.Z);
	}
	__forceinline FVector operator*(float Scale) const {
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}
	__forceinline FVector operator/(float Scale) const {
		const float RScale = 1.f / Scale;
		return FVector(X * RScale, Y * RScale, Z * RScale);
	}
	__forceinline FVector operator+(float A) const {
		return FVector(X + A, Y + A, Z + A);
	}
	__forceinline FVector operator-(float A) const {
		return FVector(X - A, Y - A, Z - A);
	}
	__forceinline FVector operator*(const FVector& V) const {
		return FVector(X * V.X, Y * V.Y, Z * V.Z);
	}
	__forceinline FVector operator/(const FVector& V) const {
		return FVector(X / V.X, Y / V.Y, Z / V.Z);
	}
	__forceinline float operator|(const FVector& V) const {
		return X * V.X + Y * V.Y + Z * V.Z;
	}
	__forceinline float operator^(const FVector& V) const {
		return X * V.Y - Y * V.X - Z * V.Z;
	}
	__forceinline FVector& operator+=(const FVector& v) {
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}
	__forceinline FVector& operator-=(const FVector& v) {
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}
	__forceinline FVector& operator*=(const FVector& v) {
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;
		return *this;
	}
	__forceinline FVector& operator/=(const FVector& v) {
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;
		return *this;
	}
	__forceinline bool operator==(const FVector& src) const {
		return (src.X == X) && (src.Y == Y) && (src.Z == Z);
	}
	__forceinline bool operator!=(const FVector& src) const {
		return (src.X != X) || (src.Y != Y) || (src.Z != Z);
	}
	__forceinline float Size() const {
		return sqrt(X * X + Y * Y + Z * Z);
	}
	__forceinline float Size2D() const {
		return sqrt(X * X + Y * Y);
	}
	__forceinline float SizeSquared() const {
		return X * X + Y * Y + Z * Z;
	}
	__forceinline float SizeSquared2D() const {
		return X * X + Y * Y;
	}
	__forceinline float Dot(const FVector& vOther) const {
		const FVector& a = *this;
		return (a.X * vOther.X + a.Y * vOther.Y + a.Z * vOther.Z);
	}
	inline float Distance(FVector v)
	{
		return float(sqrtf(powf(v.X - X, 2.0) + powf(v.Y - Y, 2.0) + powf(v.Z - Z, 2.0)));
	}
	__forceinline FVector Normalize() {
		FVector vector;
		float length = this->Size();

		if (length != 0) {
			vector.X = X / length;
			vector.Y = Y / length;
			vector.Z = Z / length;
		}
		else
			vector.X = vector.Y = 0.0f;
		vector.Z = 1.0f;

		return vector;
	}
};

FVector Clamp(FVector Ver)
{
	FVector Result;
	Result = Ver;
	if (Result.X > 180)
	{
		Result.X -= 360;
	}
	else if (Result.X < -180)
	{
		Result.X += 360;
	}
	if (Result.Y > 180)
	{
		Result.Y -= 360;
	}
	else if (Result.Y < -180)
	{
		Result.Y += 360;
	}
	if (Result.X < -89.)
	{
		Result.X = -89;
	}
	if (Result.X > 89)
	{
		Result.X = 89;
	}
	while (Result.Y < 180.f)
	{
		Result.Y += 360.f;
	}
	while (Result.Y > 180.f)
	{
		Result.Y -= 360.f;
	}
	Result.Z = 0;
	return(Result);
}
FVector ToFRotator(FVector Ver)
{
	FVector Rot;
	float RADPI;
	RADPI = (float)(180.f / M_PI);
	Rot.Y = (float)atan2f(Ver.Y, Ver.X) * RADPI;
	Rot.X = (float)atan2f(Ver.Z, sqrtf(powf(Ver.X, 2.0) + powf(Ver.Y, 2.0))) * RADPI;
	Rot.Z = 0;
	return(Rot);
}

typedef struct _Vector2
{
	float x;
	float y;
} Vector2, * PVector2;
