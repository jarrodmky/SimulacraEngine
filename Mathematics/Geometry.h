#ifndef IncludedGeometryH
#define IncludedGeometryH

//===========================================================================
// Filename:	Geometry.h
// Author:		Jarrod MacKay
// Description:	Includes the library objects used for 3D space.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "MathBase.h"
#include "Algebra.h"
#include "Point.h"
#include "Simplices.h"

namespace Mathematics
{
//===========================================================================
// Operators
//===========================================================================

	inline const Point operator *(const Matrix& p_Matrix, const Point& p_Point)
	{
		return Point(p_Matrix.Column(4)) + (p_Matrix * p_Point.PositionVector());
	}

//===========================================================================
// Functions
//===========================================================================

//Distance Functions

	//Minimum distance between a point and a line
	const scalar Distance(const Line& p_Line, const Point& p_Point);
	const scalar DistanceSquared(const Line& p_Line, const Point& p_Point);
	
	//Minimum distance between two lines
	const scalar Distance(const Line& p_Line1, const Line& p_Line2);
	const scalar DistanceSquared(const Line& p_Line1, const Line& p_Line2);
	
	//Minimum distance between a plane and a point
	const scalar Distance(const Plane& p_Plane, const Point& p_Point);
	const scalar DistanceSquared(const Plane& p_Plane, const Point& p_Point);

//Intersection Functions

	//True if a point is on a plane, false otherwise
	const bool PointIsOnPlane(const Point& p_Point, const Plane& p_Plane);

	//True if a line intersects a plane, false otherwise. Sets the point of intersection
	const bool LineIntersectsPlane(const Line& p_Line, const Plane& p_Plane, Point& p_Point);

	//True if a plane intersects a plane, false otherwise. Sets the line of intersection
	const bool PlaneIntersectsPlane(const Plane& p_Plane1, const Plane& p_Plane2, Line& p_Line);
	

//Coordinate Transforms

	inline const Vector SphericalToCartesian(const Vector& p_RadPolarAxial)
	{
		const scalar st = sin(p_RadPolarAxial.z);
		const scalar sp = sin(p_RadPolarAxial.y);
		const scalar ct = cos(p_RadPolarAxial.z);
		const scalar cp = cos(p_RadPolarAxial.y);
		const scalar rad = p_RadPolarAxial.x;

		return Vector(rad * ct * sp, rad * st * sp, rad * cp);
	}

//Matrix transforms

	inline const Matrix Transform_RH(const Vector& p_Right
								   , const Vector& p_Up
								   , const Vector& p_Forward
								   , const Point& p_Origin)
	{
		using namespace ConstantScalars;

		return Matrix(p_Right.x, p_Up.x, p_Forward.x, p_Origin.x
					, p_Right.y, p_Up.y, p_Forward.y, p_Origin.y
					, p_Right.z, p_Up.z, p_Forward.z, p_Origin.z
					, Zero, Zero, Zero, Unity);
	}

	inline const Matrix Transform_LH(const Vector& p_Left
								   , const Vector& p_Up
								   , const Vector& p_Forward
								   , const Point& p_Origin)
	{
		using namespace ConstantScalars;

		return Matrix(p_Left.x, p_Up.x, p_Forward.x, p_Origin.x
					, p_Left.y, p_Up.y, p_Forward.y, p_Origin.y
					, p_Left.z, p_Up.z, p_Forward.z, p_Origin.z
					, Zero, Zero, Zero, Unity);
	}

	inline const Matrix ViewLookAt_RH(const Point& p_Position
		, const Point& p_Target
		, const Vector& p_Up = ConstantVectors::J)
	{
		using namespace ConstantScalars;
		const Vector zAxis((p_Position - p_Target).Direction());
		const Vector xAxis((p_Up * zAxis).Direction());
		const Vector yAxis( zAxis * xAxis);
		const Vector eye(p_Position.PositionVector());

		return Matrix(xAxis.x, xAxis.y, xAxis.z, xAxis|eye
					, yAxis.x, yAxis.y, yAxis.z, yAxis|eye
					, zAxis.x, zAxis.y, zAxis.z, zAxis|eye
					, Zero, Zero, Zero, Unity);
	}

	inline const Matrix ViewLookAt_LH(const Point& p_Position
		, const Point& p_Target
		, const Vector& p_Up = ConstantVectors::J)
	{
		using namespace ConstantScalars;
		const Vector zAxis((p_Target - p_Position).Direction());
		const Vector xAxis((p_Up * zAxis).Direction());
		const Vector yAxis(zAxis * xAxis);
		const Vector eye(p_Position.PositionVector());

		return Matrix(xAxis.x, xAxis.y, xAxis.z, -(xAxis | eye)
			, yAxis.x, yAxis.y, yAxis.z, -(yAxis | eye)
			, zAxis.x, zAxis.y, zAxis.z, -(zAxis | eye)
			, Zero, Zero, Zero, Unity);
	}

	inline const Matrix PerspectiveProjection_RH(const scalar p_FieldOfView
		, const scalar p_AspectRatio
		, const scalar p_zFar
		, const scalar p_zNear)
	{
		using namespace ConstantScalars;
		const scalar yFOV = Inverse(std::tan(p_FieldOfView / 2.0f));
		const scalar xFOV = yFOV / p_AspectRatio;
		const scalar depthScale = p_zFar / (p_zNear - p_zFar);

		return Matrix(xFOV, Zero, Zero, Zero
			, Zero, yFOV, Zero, Zero
			, Zero, Zero, depthScale, p_zNear*depthScale
			, Zero, Zero, -Unity, Zero);
	}

	inline const Matrix PerspectiveProjection_LH(const scalar p_FieldOfView
											   , const scalar p_AspectRatio
											   , const scalar p_zFar
											   , const scalar p_zNear)
	{
		using namespace ConstantScalars;
		const scalar yFOV = Inverse(std::tan(p_FieldOfView / 2.0f));
		const scalar xFOV = yFOV / p_AspectRatio;
		const scalar depthScale = p_zFar / (p_zFar - p_zNear);

		return Matrix(xFOV, Zero, Zero, Zero
			, Zero, yFOV, Zero, Zero
			, Zero, Zero, depthScale, -p_zNear*depthScale
			, Zero, Zero, Unity, Zero);
	}

	inline const Matrix ScreenToNDC(const u32 p_Height, const u32 p_Width)
	{
		const scalar w = static_cast<scalar>(p_Width);
		const scalar h = static_cast<scalar>(p_Height);

		return Matrix(2.0f/w, 0.0f, 0.0f, 0.0f
					, 0.0f, -2.0f/h, 0.0f, 0.0f
					, 0.0f, 0.0f, 1.0f, 0.0f
					, -1.0f, 1.0f,0.0f,1.0f);
	}
}

#endif //#ifndef IncludedGeometryH