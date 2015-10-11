#ifndef WE_MATH_H
#define WE_MATH_H

#include <math.h>
#include "Vector.h"

/**
 * Abstraction of the C++ math functions, so they can be sped up with approximate methods if need be.
 */
template <class Real> class Math
{
public:
	static Real Abs(Real val) {
		return abs(val);
	}
	static Real ACos(Real val) {
		return acos(val);
	}
	static Real ASin(Real val) {
		return asin(val);
	}
	static Real ATan(Real val) {
		return atan(val);
	}
	static Real ATan2(Real y, Real x) {
		return atan2(y, x);
	}
	static Real Ceil(Real val) {
		return ceil(val);
	}
	static Real Cos(Real val) {
		return cos(val);
	}
	static Real Exp(Real val) {
		return exp(val);
	}
	static Real Floor(Real val) {
		return floor(val);
	}
	static Real Fmod(Real val1, Real val2) {
		return fmod(val1, val2);
	}
	static Real Log(Real val) {
		return log(val);
	}
	static Real Pow(Real x, Real exp) {
		return pow(x, exp);
	}
	static Real Sin(Real val) {
		return sin(val);
	}
	static Real Sqrt(Real val) {
		return sqrt(val);
	}
	static Real Tan(Real val) {
		return tan(val);
	}
	static Real Sign(Real iValue) {
		if (iValue < 0) return -1;
		else if (iValue > 0) return 1;
		else return 0;
	}
	static Real lerp(Real x, Real x0, Real x1, Real y0, Real y1) {
		return y0 + ((y1 - y0)*(x - x0) / (x1 - x0));
	}
	static Real slerp(Vector3<Real> p0, Vector3<Real> p1, Real t) {
		return p0.multiply(1 - t).add(p1.multiply(t));
	}
	
    // common constants
    static const Real EPSILON;
    static const Real ZERO_TOLERANCE; //Arbitrary. Adjust as needed.
    static const Real MAX_REAL; //Arbitrary. Adjust as needed.
    static const Real PI;
	static const Real TWO_PI;
    static const Real HALF_PI;
    static const Real INV_PI;
    static const Real INV_TWO_PI;
    static const Real DEG_TO_RAD;
    static const Real RAD_TO_DEG;
};

typedef Math<float> Mathf;
typedef Math<double> Mathd;
 
#endif