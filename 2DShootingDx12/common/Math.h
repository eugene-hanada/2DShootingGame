#pragma once
#include "Vector2.h"

namespace Math
{
	template<Vec2C T>
	constexpr Vector2Tmp<T> zeroVector2{ static_cast<T>(0),static_cast<T>(0) };

	template<Vec2C T>
	constexpr Vector2Tmp<T> upVector2{ static_cast<T>(0),static_cast<T>(-1) };

	template<Vec2C T>
	constexpr Vector2Tmp<T> downVector2{ static_cast<T>(0),static_cast<T>(1) };

	template<Vec2C T>
	constexpr Vector2Tmp<T> rightVector2{ static_cast<T>(1),static_cast<T>(0) };

	template<Vec2C T>
	constexpr Vector2Tmp<T> leftVector2{ static_cast<T>(-1),static_cast<T>(0) };

	/// <summary>
	/// 二乗する
	/// </summary>
	/// <param name="val"> 二乗したい値 </param>
	/// <returns> 二乗した値 </returns>
	template<Vec2C T>
	constexpr T Square(T val)
	{
		return val * val;
	}

	/// <summary>
	/// 内積(Vector2用)
	/// </summary>
	/// <param name="lVec"></param>
	/// <param name="rVec"></param>
	/// <returns></returns>
	template<Vec2C T>
	constexpr T Dot(const Vector2Tmp<T>& lVec, const Vector2Tmp<T>& rVec)
	{
		return lVec.x * rVec.x + lVec.y * rVec.y;
	}


	/// <summary>
	/// 外積(Vector2用)
	/// </summary>
	/// <param name="lVec"></param>
	/// <param name="rVec"></param>
	/// <returns></returns>
	template<Vec2C T>
	constexpr T Cross(const Vector2Tmp<T>& lVec, const Vector2Tmp<T>& rVec)
	{
		return lVec.x * rVec.y - lVec.y * rVec.x;
	}


	// 円周率
	template<Vec2C T>
	constexpr T pi = static_cast<T>(3.1415926535897932384626433832795);

	// 円周率*2
	template<Vec2C T>
	constexpr T pi2 = pi<T> * static_cast<T>(2.0);

	/// <summary>
	/// 度数法を弧度法にする
	/// </summary>
	/// <param name="deg"> 変換したい度数法の値 </param>
	/// <returns>  </returns>
	template<Vec2C T>
	constexpr T Deg2Rad(const T& deg)
	{
		return deg * (pi<T> / static_cast<T>(180));
	}

	/// <summary>
	/// 弧度法を度数法にする
	/// </summary>
	/// <param name="rad"></param>
	/// <returns></returns>
	template<Vec2C T>
	constexpr T Rad2Deg(const T& rad)
	{
		return rad * (static_cast<T>(180) / pi<T>);
	}

	/// <summary>
	/// 角度を指定範囲に正規化する
	/// </summary>
	/// <param name="angle"> 変換する値 </param>
	/// <param name="valMin"> 最小値(デフォルト=0) </param>
	/// <param name="valMax"> 最大値(デフォルト=pi2) </param>
	/// <returns></returns>
	float GetNormalizedAngle(float angle, float valMin = 0.0f, float valMax = pi2<float>);

	double GetNormalizedAngle(double angle, double valMin = 0.0f, double valMax = pi2<double>);
	
	float Clamp(float val, float minVal, float maxVal);
}

