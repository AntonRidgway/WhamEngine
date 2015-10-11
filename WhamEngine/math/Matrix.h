#ifndef WE_MATRIX_H
#define WE_MATRIX_H

#include "math/Vector.h"

template <class Real> class Matrix22
{
private:
	static const int M_SIZE = 2;
	static const int M_AREA = 4;
	Real data[M_SIZE][M_SIZE];		//matrix data
	Real det;				//matrix determinant-- lazy evaluation, not found unless needed
	Real inv[M_SIZE][M_SIZE];			//matrix inverse-- lazy evaluation, not found unless needed
	bool detInit;			//flag: has the determinant been found?
	bool invInit;			//flag: has the inverse been found?
public:
	Matrix22() {}
	Matrix22( Real a, Real b, Real c, Real d )
	{
		data[0][0] = a;	data[0][1] = b;
		data[1][0] = c;	data[1][1] = d;
		detInit = false;
		invInit = false;
	}
	Matrix22( Real dataIn[M_AREA] )
	{
		data[0][0] = dataIn[0];
		data[0][1] = dataIn[1];
		data[1][0] = dataIn[2];
		data[1][1] = dataIn[3];
		detInit = false;
		invInit = false;
	}
	Matrix22( Real dataIn[2][2] )
	{
		data[0][0] = dataIn[0][0];
		data[0][1] = dataIn[0][1];
		data[1][0] = dataIn[1][0];
		data[1][1] = dataIn[1][1];
		detInit = false;
		invInit = false;
	}
	Matrix22( const Matrix22<Real> &m )
	{
		data[0][0] = m.getEntry(0,0);
		data[0][1] = m.getEntry(0,1);
		data[1][0] = m.getEntry(1,0);
		data[1][1] = m.getEntry(1,1);
		detInit = false;
		invInit = false;
	}
	Matrix22<Real> add( Matrix22<Real> b )
	{
		Matrix22 mNew( data[0][0] + b.getEntry(0,0), data[0][1] + b.getEntry(0,0),
					   data[1][0] + b.getEntry(1,0), data[1][1] + b.getEntry(1,1) );
		return mNew;
	}
	Matrix22<Real> subtract( Matrix22<Real> b )
	{
		Matrix22 mNew( data[0][0] - b.getEntry(0,0), data[0][1] - b.getEntry(0,0),
					   data[1][0] - b.getEntry(1,0), data[1][1] - b.getEntry(1,1) );
		return mNew;
	}
	Matrix22<Real> multiply( const Real s )
	{
		Matrix22 mNew( data[0][0] * s, data[0][1] * s,
					   data[1][0] * s, data[1][1] * s);
		return mNew;
	}
	Vector2<Real> multiply( Vector2<Real> v )
	{
		Real results[M_SIZE];
		Real runSum = 0.0;
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
				runSum += data[i][j] * v.getEntry(j);
			results[i] = runSum;
			runSum = 0.0;
		}
		Vector2<Real> newVec(results);
		return newVec;
	}
	Matrix22<Real> multiply( Matrix22<Real> b )
	{
		Real dataNew[M_SIZE][M_SIZE];
		for(int i = 0; i < M_SIZE; i++)
		{
			for(int j = 0; j < M_SIZE; j++)
			{
				float runSum = 0;
				for (int k = 0; k < 2; k++)
				{
					runSum += data[i][k] * b.getEntry(k,j);
				}
				dataNew[i][j] = runSum;
			}
		}
		Matrix22<Real> newMat(dataNew);
		return newMat;
	}
	Matrix22<Real> transpose()
	{
		Real dataNew[2][2];
		for( int i = 0; i < 2; i++ )
		{
			for ( int j = 0; j < 2; j++ )
			{
				dataNew[i][j] = data[j][i];
			}
		}
		Matrix22<Real> newMat(dataNew);
		return newMat;
	}
	Matrix22<Real> negate()
	{
		Real dataNew[2][2];
		for (int i = 0; i < 2; i++ )
		{
			for (int j = 0; j < 2; j++ )
				dataNew[i][j] = -data[i][j];
		}
		Matrix22<Real> newMat(dataNew);
		return newMat;
	}

	Real determinant()
	{
		if (detInit == false)
		{
			det = data[0][0]*data[1][1] - data[1][0]*data[0][1];
			detInit = true;
		}
		return det;
	}

	Matrix22<Real> invert()
	{
		if( determinant() == 0 )
			return null;
		Matrix22<Real> newMat( data[1][1]/det, -data[0][1]/det, -data[0][1]/det, data[0][0]/det);
		inv[0][0] = newMat.getEntry(0,0);
		inv[0][1] = newMat.getEntry(0,1);
		inv[1][0] = newMat.getEntry(1,0);
		inv[1][1] = newMat.getEntry(1,1);
		invInit = true;
		return newMat;
	}

	Real getEntry(int r,int c) const
	{
		if( r >= 0 && r < M_SIZE && c >= 0 && r < M_SIZE )
			return data[r][c];
		else
			return -1;
	}

	void setEntry(int r, int c, Real value)
	{
		if( r >= 0 && r < M_SIZE && c >= 0 && r < M_SIZE )
			data[r][c] = value;
	}

	Real* getArray()
	{
		Real myArray[M_AREA];
		for (int i = 0; i < M_AREA; i++)
		{
			myArray[i]= data[i / M_SIZE][i % M_SIZE];
		}
		Real* aPointer = myArray;
		return aPointer;
	}
};

template <class Real> class Matrix33
{
private:
	static const int M_SIZE = 3;
	static const int M_AREA = 9;
	Real data[M_SIZE][M_SIZE];		//matrix data
	Real det;				//matrix determinant-- lazy evaluation, not found unless needed
	Real inv[M_SIZE][M_SIZE];			//matrix inverse-- lazy evaluation, not found unless needed
	bool detInit;			//flag: has the determinant been found?
	bool invInit;			//flag: has the inverse been found?
public:
	Matrix33() {}
	Matrix33( Real d00, Real d01, Real d02,
			  Real d10, Real d11, Real d12,
			  Real d20, Real d21, Real d22  )
	{
		data[0][0] = d00;	data[0][1] = d01;	data[0][2] = d02;
		data[1][0] = d10;	data[1][1] = d11;	data[1][2] = d12;
		data[2][0] = d20;	data[2][1] = d21;	data[2][2] = d22;
		detInit = false;
		invInit = false;
	}
	Matrix33( Real dataIn[M_AREA] )
	{
		for( int i = 0; i < M_SIZE; i++ )
		{
			for( int j = 0; j < M_SIZE; j++ )
			{
				data[i][j] = dataIn[(i*M_SIZE)+j];
			}
		}
		detInit = false;
		invInit = false;
	}
	Matrix33( Real dataIn[M_SIZE][M_SIZE] )
	{
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
			{
				data[i][j] = dataIn[i][j];
			}
		}
		detInit = false;
		invInit = false;
	}
	Matrix33( const Matrix33<Real>& m )
	{
		Real* mArray = m.getArray();
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
			{
				data[i][j] = mArray[i][j];
			}
		}
		detInit = false;
		invInit = false;
	}
	Matrix33<Real> add( Matrix33<Real> b )
	{
		Real dataNew[M_SIZE][M_SIZE];
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
			{
				dataNew[i][j] = data[i][j] + b.getEntry(i,j);
			}
		}
		Matrix33 mNew( dataNew );
		return mNew;
	}
	Matrix33<Real> subtract( Matrix33<Real> b )
	{
		Real dataNew[M_SIZE][M_SIZE];
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
			{
				dataNew[i][j] = data[i][j] - b.getEntry(i,j);
			}
		}
		Matrix33 mNew( dataNew );
		return mNew;
	}
	Matrix33<Real> multiply( const Real s )
	{
		Real dataNew[M_SIZE][M_SIZE];
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
			{
				dataNew[i][j] = data[i][j] *s;
			}
		}
		Matrix33 mNew( dataNew );
		return mNew;
	}
	Vector3<Real> multiply( Vector3<Real> v )
	{
		Real results[M_SIZE];
		Real runSum = 0.0;
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
				runSum += data[i][j] * v.getEntry(j);
			results[i] = runSum;
			runSum = 0.0;
		}
		Vector3<Real> newVec(results);
		return newVec;
	}
	Matrix33<Real> multiply( Matrix33<Real> b )
	{
		Real dataNew[M_SIZE][M_SIZE];
		for(int i = 0; i < M_SIZE; i++)
		{
			for(int j = 0; j < M_SIZE; j++)
			{
				float runSum = 0;
				for (int k = 0; k < M_SIZE; k++)
				{
					runSum += data[i][k] * b.getEntry(k,j);
				}
				dataNew[i][j] = runSum;
			}
		}
		Matrix33<Real> newMat(dataNew);
		return newMat;
	}
	Matrix33<Real> transpose()
	{
		Real dataNew[M_SIZE][M_SIZE];
		for( int i = 0; i < M_SIZE; i++ )
		{
			for ( int j = 0; j < M_SIZE; j++ )
			{
				dataNew[i][j] = data[j][i];
			}
		}
		Matrix33<Real> newMat(dataNew);
		return newMat;
	}
	Matrix33<Real> negate()
	{
		Real dataNew[M_SIZE][M_SIZE];
		for (int i = 0; i < M_SIZE; i++ )
		{
			for (int j = 0; j < M_SIZE; j++ )
				dataNew[i][j] = -data[i][j];
		}
		Matrix33<Real> newMat(dataNew);
		return newMat;
	}

	Real determinant()
	{
		if (detInit == false)
		{
			det = data[0][0]*data[1][1]*data[2][2] -
				  data[0][0]*data[1][2]*data[2][1] +
				  data[0][1]*data[1][2]*data[2][0] -
				  data[0][1]*data[1][0]*data[2][2] +
				  data[0][2]*data[1][0]*data[2][1] -
				  data[0][2]*data[1][1]*data[2][0];
			detInit = true;
		}
		return det;
	}

	Matrix33<Real> invert()
	{
		if( determinant() == 0 )
			return nullptr;
		//invInit = true;
		return nullptr;
	}

	Real getEntry(int r,int c) const
	{
		if( r >= 0 && r < M_SIZE && c >= 0 && r < M_SIZE )
			return data[r][c];
		else
			return -1;
	}

	void setEntry(int r, int c, Real value)
	{
		if( r >= 0 && r < M_SIZE && c >= 0 && r < M_SIZE )
			data[r][c] = value;
	}

	Real* getArray()
	{
		Real myArray[M_AREA];
		for (int i = 0; i < M_AREA; i++)
		{
			myArray[i]= data[i/M_SIZE][i%M_SIZE];
		}
		Real* aPointer = myArray;
		return aPointer;
	}
};

template <class Real> class Matrix44
{
private:
	static const int M_SIZE = 4;
	static const int M_AREA = 16;
	Real* data;		//matrix data
	Real det;				//matrix determinant-- lazy evaluation, not found unless needed
	Real inv[M_AREA];		//matrix inverse-- lazy evaluation, not found unless needed
	bool detInit;			//flag: has the determinant been found?
	bool invInit;			//flag: has the inverse been found?
public:
	Matrix44() {}
	Matrix44( Real d00, Real d01, Real d02, Real d03,
			  Real d10, Real d11, Real d12, Real d13,
			  Real d20, Real d21, Real d22, Real d23,
			  Real d30, Real d31, Real d32, Real d33 )
	{
		data = new Real[16];
		data[0] = d00;	data[1] = d01;	data[2] = d02;	data[3] = d03;
		data[4] = d10;	data[5] = d11;	data[6] = d12;	data[7] = d13;
		data[8] = d20;	data[9] = d21;	data[10] = d22;	data[11] = d23;
		data[12] = d30;	data[13] = d31;	data[14] = d32;	data[15] = d33;
		detInit = false;
		invInit = false;
	}
	Matrix44( Real dataIn[M_AREA] )
	{
		data = new Real[16];
		for( int i = 0; i < M_AREA; i++ )
		{
			data[i] = dataIn[i];
		}
		detInit = false;
		invInit = false;
	}
	Matrix44( Real dataIn[M_SIZE][M_SIZE] )
	{
		data = new Real[16];
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
			{
				data[M_SIZE*i+j] = dataIn[i][j];
			}
		}
		detInit = false;
		invInit = false;
	}
	Matrix44<Real>( const Matrix44<Real>& m )
	{
		data = new Real[16];
		Real* mArray = m.getArray();
		for (int i = 0; i < M_AREA; i++)
		{
			data[i] = mArray[i];
		}
		detInit = false;
		invInit = false;
	}
	~Matrix44<Real>()
	{
		delete[] data;
	}
	Matrix44<Real> add( Matrix44<Real> b )
	{
		Real* bArray = b.getArray();
		return Matrix44<Real>( data[0] + bArray[0], data[1] + bArray[1], data[2] + bArray[2], data[3] + bArray[3],
						data[4] + bArray[4], data[5] + bArray[5], data[6] + bArray[6], data[7] + bArray[7],
						data[8] + bArray[8], data[9] + bArray[9], data[10] + bArray[10], data[11] + bArray[11],
						data[12] + bArray[12], data[13] + bArray[13], data[14] + bArray[14], data[15] + bArray[15]);
	}
	Matrix44<Real> subtract( Matrix44<Real> b )
	{
		Real dataNew[M_AREA];
		Real* bArray = b.getArray();
		for (int i = 0; i < M_AREA; i++)
		{
			dataNew[i] = data[i] - bArray[i];
		}
		Matrix44 mNew( dataNew );
		return mNew;
	}
	Matrix44<Real> multiply( const Real s )
	{
		return Matrix44<Real>(data[0]*s,data[1]*s,data[2]*s,data[3]*s,
									data[4]*s,data[5]*s,data[6]*s,data[7]*s,
									data[8]*s,data[9]*s,data[10]*s,data[11]*s,
									data[12]*s,data[13]*s,data[14]*s,data[15]*s);
	}
	Vector4<Real> multiply( Vector4<Real> v )
	{
		Real results[M_SIZE];
		Real runSum = 0.0;
		for (int i = 0; i < M_SIZE; i++)
		{
			for (int j = 0; j < M_SIZE; j++)
				runSum += data[M_SIZE*i+j] * v.getEntry(j);
			results[i] = runSum;
			runSum = 0.0;
		}
		Vector4<Real> newVec(results);
		return newVec;
	}
	Matrix44<Real> multiply( Matrix44<Real> b )
	{
		Real dataNew[M_SIZE][M_SIZE];
		for(int i = 0; i < M_SIZE; i++)
		{
			for(int j = 0; j < M_SIZE; j++)
			{
				float runSum = 0;
				for (int k = 0; k < M_SIZE; k++)
				{
					runSum += data[M_SIZE*i+k] * b.getEntry(k,j);
				}
				dataNew[i][j] = runSum;
			}
		}
		Matrix44<Real> newMat(dataNew);
		return newMat;
	}
	void multiplyIn( Matrix44<Real> b )
	{
		Real dataNew[M_SIZE][M_SIZE];
		for(int i = 0; i < M_SIZE; i++) //iterate through rows of the result
		{
			for(int j = 0; j < M_SIZE; j++) //iterate through columns of the result
			{
				float runSum = 0;
				for (int k = 0; k < M_SIZE; k++) //iterate through the rows and columns of the respective matrices
				{
					runSum += data[M_SIZE*i+k] * b.getEntry(k,j);
				}
				dataNew[i][j] = runSum;
			}
		}
		for( int i = 0; i < M_SIZE; i++)
		{
			for ( int j = 0; j < M_SIZE; j++ )
				data[M_SIZE*i+j] = dataNew[i][j];
		}
	}
	Matrix44<Real> transpose()
	{
		Real dataNew[M_AREA];
		for( int i = 0; i < M_SIZE; i++ )
		{
			for( int j = 0; j < M_SIZE; j++ )
			{
				dataNew[M_SIZE*i + j] = data[M_SIZE*j + i];
			}
		}
		Matrix44<Real> newMat(dataNew);
		return newMat;
	}
	Matrix44<Real> negate()
	{
		Real dataNew[M_AREA];
		for (int i = 0; i < M_AREA; i++ )
		{
			dataNew[i] = -data[i];
		}
		Matrix44<Real> newMat(dataNew);
		return newMat;
	}
	/*
	Real determinant()
	{
		if (detInit == false)
		{
		}
		return det;
	}

	Matrix44<Real> invert()
	{
		if( determinant() == 0 )
			return nullptr;
		//invInit = true;
		return nullptr;
	}
	*/
	Real getEntry(int r,int c) const
	{
		if( r >= 0 && r < M_SIZE && c >= 0 && r < M_SIZE )
			return data[4*r+c];
		else
			return -1;
	}

	void setEntry(int r, int c, Real value)
	{
		if( r >= 0 && r < M_SIZE && c >= 0 && r < M_SIZE )
			data[M_SIZE*r+c] = value;
	}

	Real* getArray() const
	{
		return data;
	}
};

typedef Matrix22<float> Matrix22f;
typedef Matrix22<double> Matrix22d;
typedef Matrix33<float> Matrix33f;
typedef Matrix33<double> Matrix33d;
typedef Matrix44<float> Matrix44f;
typedef Matrix44<double> Matrix44d;

#endif
