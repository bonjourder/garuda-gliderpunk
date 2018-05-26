#ifndef GARUDA_MATH
#define GARUDA_MATH

#include "Vector3.h"
#define PI = 3.14159

#include <vector>
#include <math.h>
using namespace std;

//David
//Erastus nambahin floatAbs
namespace Math
{
	double ConvertToRadians(double degrees);
	double ConvertToDegrees(double radians);
	Vector3 RotatePoint(Vector3 point, Vector3 pivot, float rot);
	float Min(vector<float> x);
	float Max(vector<float> x);
	float Abs(float x);

}



#endif
