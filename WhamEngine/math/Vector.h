#ifndef WE_VECTOR_H
#define WE_VECTOR_H

template <class Real> class Vector2
{
private:
	Real data[2];
	Real mag;
	bool magInit;
public:
	Vector2();
	Vector2( Real i, Real j );
	Vector2( Real dataIn[2] );
	Vector2( Vector2<Real> &vectorIn );
	void addIn ( Vector2<Real> &vectorIn );
	Vector2 add ( Vector2<Real>& vectorIn);
	void subIn (Vector2<Real> &vectorIn);
	Vector2 sub (Vector2<Real>& vectorIn);
	void multiplyIn ( Real s );
	Vector2 multiply ( Real s );
	Real dot (Vector2<Real>& vectorIn);
	void normalizeIn();
	Vector2 normalize();
	Real getMag();
	Real getEntry( int i ) const;
	Real* getArray();
};

template <class Real> class Vector3
{
private:
	Real data[3];
	Real mag;
	bool magInit;
public:
	Vector3();
	Vector3( Real i, Real j, Real k );
	Vector3( Real dataIn[3] );
	Vector3( Vector3<Real> &vectorIn );
	void addIn ( Vector3<Real> &vectorIn );
	Vector3 add ( Vector3<Real>& vectorIn);
	void subIn (Vector3<Real> &vectorIn);
	Vector3 sub (Vector3<Real>& vectorIn);
	void multiplyIn ( Real s );
	Vector3 multiply ( Real s );
	Real dot (Vector3<Real>& vectorIn);
	Vector3 cross (Vector3<Real>& vectorIn);
	void normalizeIn();
	Vector3 normalize();
	Real getMag();
	Real getEntry( int i ) const;
	void setEntry( int index, Real value );
	Real* getArray();
};

template <class Real> class Vector4
{
private:
	Real data[4];
	Real mag;
	bool magInit;
public:
	Vector4();
	Vector4( Real i, Real j, Real k, Real m );
	Vector4( Real dataIn[4] );
	Vector4( Vector4<Real> &vectorIn );
	void addIn ( Vector4<Real> &vectorIn );
	Vector4 add ( Vector4<Real>& vectorIn);
	void subIn (Vector4<Real> &vectorIn);
	Vector4 sub (Vector3<Real>& vectorIn);
	void multiplyIn ( Real s );
	Vector4 multiply ( Real s );
	Real dot (Vector3<Real>& vectorIn);
	void normalizeIn();
	Vector4 normalize();
	Real getMag();
	Real getEntry( int i ) const;
	Real* getArray();
};


template <class Real> Vector2<Real>::Vector2()
{
	data[0] = 0; data[1] = 0;
	mag = 0;
	magInit = true;
}
template <class Real> Vector2<Real>::Vector2( Real i, Real j )
{
	data[0] = i;
	data[1] = j;
	magInit = false;
}
template <class Real> Vector2<Real>::Vector2( Real dataIn[2] )
{
	data[0] = dataIn[0];
	data[1] = dataIn[1];
	magInit = false;
}
template <class Real> Vector2<Real>::Vector2( Vector2<Real> &vectorIn )
{
	data[0] = vectorIn.getEntry(0);
	data[1] = vectorIn.getEntry(1);
	magInit = false;
}
template <class Real> void Vector2<Real>::addIn ( Vector2<Real> &vectorIn )
{
	data[0] += vectorIn.getEntry(0);
	data[1] += vectorIn.getEntry(1);
	return true;
}
template <class Real> Vector2<Real> Vector2<Real>::add ( Vector2<Real>& vectorIn) 
{
	Vector2<Real> newVec (data[0]+vectorIn.getEntry(0), data[1]+vectorIn.getEntry(1));
	return newVec;
}
template <class Real> void Vector2<Real>::subIn (Vector2<Real> &vectorIn)
{
	data[0] -= vectorIn.getEntry(0);
	data[1] -= vectorIn.getEntry(1);
}
template <class Real> Vector2<Real> Vector2<Real>::sub (Vector2<Real>& vectorIn)
{
	Vector newVec(data[0]-vectorIn.getEntry(0), data[1]-vectorIn.getEntry(1));
	return newVec;
}
template <class Real> void Vector2<Real>::multiplyIn ( Real s )
{
	data[0] *= s;
	data[1] *= s;
}
template <class Real> Vector2<Real> Vector2<Real>::multiply ( Real s )
{
	Vector2<Real> newVec(data[0]*s,data[1]*s);
	return newVec;
}
template <class Real> Real Vector2<Real>::dot (Vector2<Real>& vectorIn)
{
	return (data[0] * vectorIn.getEntry(0)) + (data[1] * vectorIn.getEntry(1));
}
template <class Real> void Vector2<Real>::normalizeIn()
{
	Real m = getMag();
	data[0] /= m;
	data[1] /= m;
}
template <class Real> Vector2<Real> Vector2<Real>::normalize()
{
	Real m = getMag();
	Vector2<Real> newVec( data[0]/m, data[1]/m );
	return newVec;
}
template <class Real> Real Vector2<Real>::getMag()
{
	if (magInit == false)
	{
		mag = sqrt(data[0]*data[0] + data[1]*data[1]);
		magInit = true;
	}
	return mag;
}
template <class Real> Real Vector2<Real>::getEntry( int i ) const
{
	if ( i > -1 && i < 2 )
		return data[i];
	else
		return -1;
}
template <class Real> Real* Vector2<Real>::getArray()
{
	return data;
}





template <class Real> Vector3<Real>::Vector3()
{
	data[0] = 0; data[1] = 0; data[2] = 0;
	mag = 0;
	magInit = true;
}
template <class Real> Vector3<Real>::Vector3( Real i, Real j, Real k )
{
	data[0] = i;
	data[1] = j;
	data[2] = k;
	magInit = false;
}
template <class Real> Vector3<Real>::Vector3( Real dataIn[3] )
{
	data[0] = dataIn[0];
	data[1] = dataIn[1];
	data[2] = dataIn[2];
	magInit = false;
}
template <class Real> Vector3<Real>::Vector3( Vector3<Real> &vectorIn )
{
	data[0] = vectorIn.getEntry(0);
	data[1] = vectorIn.getEntry(1);
	data[2] = vectorIn.getEntry(2);
	magInit = false;
}
template <class Real> void Vector3<Real>::addIn ( Vector3<Real> &vectorIn )
{
	data[0] += vectorIn.getEntry(0);
	data[1] += vectorIn.getEntry(1);
	data[2] += vectorIn.getEntry(2);
}
template <class Real> Vector3<Real> Vector3<Real>::add ( Vector3<Real>& vectorIn) 
{
	Vector3<Real> newVec (data[0]+vectorIn.getEntry(0), data[1]+vectorIn.getEntry(1), data[2]+vectorIn.getEntry(2));
	return newVec;
}
template <class Real> void Vector3<Real>::subIn (Vector3<Real> &vectorIn)
{
	data[0] -= vectorIn.getEntry(0);
	data[1] -= vectorIn.getEntry(1);
	data[2] -= vectorIn.getEntry(2);
}
template <class Real> Vector3<Real> Vector3<Real>::sub (Vector3<Real>& vectorIn)
{
	Vector3 newVec(data[0]-vectorIn.getEntry(0), data[1]-vectorIn.getEntry(1), data[2]-vectorIn.getEntry(2));
	return newVec;
}
template <class Real> void Vector3<Real>::multiplyIn ( Real s )
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
}
template <class Real> Vector3<Real> Vector3<Real>::multiply ( Real s )
{
	Vector3<Real> newVec(data[0]*s,data[1]*s,data[2]*s);
	return newVec;
}
template <class Real> Real Vector3<Real>::dot (Vector3<Real>& vectorIn)
{
	return (data[0] * vectorIn.getEntry(0)) + (data[1] * vectorIn.getEntry(1)) + (data[2] * vectorIn.getEntry(2));
}
template <class Real> Vector3<Real> Vector3<Real>::cross (Vector3<Real>& vectorIn)
{
	Vector3<Real> newVec( data[1]*vectorIn.getEntry(2) - data[2]*vectorIn.getEntry(1),
					data[2]*vectorIn.getEntry(0) - data[0]*vectorIn.getEntry(2),
					data[0]*vectorIn.getEntry(1) - data[1]*vectorIn.getEntry(0) );
	return newVec;
}
template <class Real> void Vector3<Real>::normalizeIn()
{
	Real m = getMag();
	data[0] /= m;
	data[1] /= m;
	data[2] /= m;
}
template <class Real> Vector3<Real> Vector3<Real>::normalize()
{
	Real m = getMag();
	Vector3<Real> newVec( data[0]/m, data[1]/m, data[2]/m );
	return newVec;
}
template <class Real> Real Vector3<Real>::getMag()
{
	if (magInit == false)
	{
		mag = sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
		magInit = true;
	}
	return mag;
}

template <class Real> Real Vector3<Real>::getEntry( int i ) const
{
	if ( i > -1 && i < 3 )
		return data[i];
	else
		return -1;
}
template <class Real> void Vector3<Real>::setEntry( int index, Real value )
{
	if(index >= 0 && index < 3)
	{
		data[index] = value;
	}
}
template <class Real> Real* Vector3<Real>::getArray()
{
	return data;
}




template <class Real> Vector4<Real>::Vector4()
{
	data[0] = 0; data[1] = 0; data[2] = 0; data[3] = 0;
	mag = 0;
	magInit = true;
}
template <class Real> Vector4<Real>::Vector4( Real i, Real j, Real k, Real m )
{
	data[0] = i;
	data[1] = j;
	data[2] = k;
	data[3] = m;
	magInit = false;
}
template <class Real> Vector4<Real>::Vector4( Real dataIn[4] )
{
	data[0] = dataIn[0];
	data[1] = dataIn[1];
	data[2] = dataIn[2];
	data[3] = dataIn[3];
	magInit = false;
}
template <class Real> Vector4<Real>::Vector4( Vector4<Real> &vectorIn )
{
	data[0] = vectorIn.getEntry(0);
	data[1] = vectorIn.getEntry(1);
	data[2] = vectorIn.getEntry(2);
	data[2] = vectorIn.getEntry(3);
	magInit = false;
}
template <class Real> void Vector4<Real>::addIn ( Vector4<Real> &vectorIn )
{
	data[0] += vectorIn.getEntry(0);
	data[1] += vectorIn.getEntry(1);
	data[2] += vectorIn.getEntry(2);
	data[3] += vectorIn.getEntry(3);
	return true;
}
template <class Real> Vector4<Real> Vector4<Real>::add ( Vector4<Real>& vectorIn) 
{
	Vector4<Real> newVec (data[0]+vectorIn.getEntry(0), data[1]+vectorIn.getEntry(1), data[2]+vectorIn.getEntry(2), data[3]+vectorIn.getEntry(3));
	return newVec;
}
template <class Real> void Vector4<Real>::subIn (Vector4<Real> &vectorIn)
{
	data[0] -= vectorIn.getEntry(0);
	data[1] -= vectorIn.getEntry(1);
	data[2] -= vectorIn.getEntry(2);
	data[3] -= vectorIn.getEntry(3);
}
template <class Real> Vector4<Real> Vector4<Real>::sub (Vector3<Real>& vectorIn)
{
	Vector4 newVec(data[0]-vectorIn.getEntry(0), data[1]-vectorIn.getEntry(1), data[2]-vectorIn.getEntry(2), data[3]-vectorIn.getEntry(3));
	return newVec;
}
template <class Real> void Vector4<Real>::multiplyIn ( Real s )
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
}
template <class Real> Vector4<Real> Vector4<Real>::multiply ( Real s )
{
	Vector4<Real,len> newVec(data[0]*s,data[1]*s,data[2]*s,data[3]*s);
	return newVec;
}
template <class Real> Real Vector4<Real>::dot (Vector3<Real>& vectorIn)
{
	return (data[0] * vectorIn.getEntry(0)) + (data[1] * vectorIn.getEntry(1)) + (data[2] * vectorIn.getEntry(2)) + (data[3] * vectorIn.getEntry(3));
}
template <class Real> void Vector4<Real>::normalizeIn()
{
	Real m = getMag();
	data[0] /= m;
	data[1] /= m;
	data[2] /= m;
	data[3] /= m;
}
template <class Real> Vector4<Real> Vector4<Real>::normalize()
{
	Real m = getMag();
	Vector4<Real> newVec( data[0]/m, data[1]/m, data[2]/m, data[3]/m );
	return newVec;
}
template <class Real> Real Vector4<Real>::getMag()
{
	if (magInit == false)
	{
		mag = sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2] + data[3]*data[3]);
		magInit = true;
	}
	return mag;
}

template <class Real> Real Vector4<Real>::getEntry( int i ) const
{
	if ( i > -1 && i < 4 )
		return data[i];
	else
		return -1;
}
template <class Real> Real* Vector4<Real>::getArray()
{
	return data;
}

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

#endif