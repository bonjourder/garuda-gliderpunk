 #include "Math.h"

//David
//Erastus nambahin floatAbs
namespace Math 
{
	double ConvertToRadians(double degrees)
	{
		return (degrees * 3.14159)/180;

	}

	double ConvertToDegrees(double radians)
	{
		return (radians * 180) / (3.14159);
	}



	Vector3 RotatePoint(Vector3 point, Vector3 pivot, float rot)
	{
		double radRot = ConvertToRadians(rot);
		double s = sin(radRot);
		double c = cos(radRot);

		point = point - pivot;
		float newX = (float)(point.x * c - point.y * s);
		float newY = (float)(point.x * s + point.y * c);

		point.x = newX + pivot.x;
		point.y = newY + pivot.y;

		return point;
	}

	float Min(vector<float> x) 
	{
		float retVal = x[0];

		for (int i = 1; i < x.size(); i++)
		{
			if (x[i] < retVal)
				retVal = x[i];
		}

		return retVal;
	}

	float Max(vector<float> x)
	{
		float retVal = x[0];

		for (int i = 1; i < x.size(); i++)
		{
			if (x[i] > retVal)
				retVal = x[i];
		}

		return retVal;
	}
	
	float Abs(float x)
	{
		if (x > 0)
		{
			return x;
		}
		return -x;
	}


}