#ifndef WE_QUATERNION_H
#define WE_QUATERNION_H

// For this Quaternion class, we assume a [1, i, j, k] basis
template <class Real> class Quaternion
{
private:
	Real w, x, y, z, mag;
	bool magInit;
public:
	Quaternion(Real a, Real b, Real c, Real d)
	{
		w = a;
		x = b;
		y = c;
		z = d;
		magInit = false;
	}
	void addIn( Quaternion q )
	{
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;
	}
	Quaternion add ( Quaternion q )
	{
		Quaternion newQ( w+q.w, x+q.x, y+q.y, z+q.z );
		return newQ;
	}
	void multiplyIn( Real r )
	{
		w *= r;
		x *= r;
		y *= r;
		z *= r;
	}
	Quaternion multiply( Real r )
	{
		Quaternion newQ(w*r, x*r, y*r, z*r);
		return newQ;
	}
	Quaternion multiplyIn( Real wIn, Real xIn, Real yIn, Real zIn )
	{
		Real wTemp = w*wIn - x*xIn - y*yIn - z*zIn;
		Real xTemp = w*xIn + wIn*x + y*zIn - z*yIn;
		Real yTemp = w*yIn + wIn*y + z*xIn - x*zIn;
		Real zTemp = w*zIn + wIn*z + x*yIn - y*xIn;

		w = wTemp;
		x = xTemp;
		y = yTemp;
		z = zTemp;
	}
	Quaternion multiply( Real wIn, Real xIn, Real yIn, Real zIn )
	{
		Real wTemp = w*wIn - x*xIn - y*yIn - z*zIn;
		Real xTemp = w*xIn + wIn*x + y*zIn - z*yIn;
		Real yTemp = w*yIn + wIn*y + z*xIn - x*zIn;
		Real zTemp = w*zIn + wIn*z + x*yIn - y*xIn;

		Quaternion newQ(wTemp,xTemp,yTmp,zTemp);
		return newQ;
	}
	void multiplyIn( Quaternion q )
	{
		multiplyIn( q );
	}
	Quaternion multiply( Quaternion q )
	{
		return multiply( q.w, q.x, q.y, q.z );
	}
	Real magnitude()
	{
		if (magInit == false)
		{
			mag = sqrt(w*w + x*x + y*y + z*z);
			magInit = true;
			return mag;
		}
		return mag;
	}
	void normalizeIn()
	{
		float temp = magnitude();
		if( temp < 1.001f && temp > 0.999f ) //no need to reevaluate
			return;
		w = w / temp;
		x = x / temp;
		y = y / temp;
		z = z / temp;
		magInit = false;
	}
	Quaternion conjugate()
	{
		Quaternion newQ( w, -x, -y, -z );
		return newQ;
	}
	Quaternion invert()
	{
		//double magnitude = currRot->w*currRot->w + currRot->x*currRot->x + currRot->y*currRot->y + currRot->z*currRot->z;
		//rotationKeys[k] = new Quaternionf(currRot->w / buh, -currRot->x / buh, -currRot->y / buh, -currRot->z / buh);
		Quaternion newQ(this).invertIn();
		return newQ;
	}
	void invertIn()
	{
		double magSq = w*w + x*x + y*y + z*z;
		w = w / magSq;
		x = -x / magSq;
		y = -y / magSq;
		z = -z / magSq;
	}
	Real getW() const
	{
		return w;
	}
	Real getX() const
	{
		return x;
	}
	Real getY() const
	{
		return y;
	}
	Real getZ() const
	{
		return z;
	}
	Matrix44<Real> toMatrix()
	{
		return Matrix44<Real>(1 - 2 * (y*y + z*z), 2 * (x*y + w*z), 2 * (x*z - w*y), 0.0f,
			2 * (x*y - w*z), 1 - 2 * (x*x + z*z), 2 * (y*z + w*x), 0.0f,
			2 * (x*z + w*y), 2 * (y*z - x*w), 1 - 2 * (x*x + y*y), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}
};


typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;

#endif