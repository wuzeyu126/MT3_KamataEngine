﻿
#pragma once
#define _USE_MATH_DEFINES
#define MATRIX_SIZE2 2
#define MATRIX_SIZE3 3
#define MATRIX_SIZE4 4
#define VECTOR_SIZE 2
#define PI 3.14159265358979323846

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include <math.h>
#include "Novice.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static const int kColumnWidth = 60;
int kRowHeight = 20;

/// <summary>
/// ********************************************************************三维向量
/// </summary>

/// <summary>
/// 三维向量输出
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="vector"></param>
/// <param name="label"></param>
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

/// <summary>
/// 三维向量的加法
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

/// <summary>
/// 三维向量的减法
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

/// <summary>
/// 三维向量乘一个数（三维向量扩大）
/// </summary>
/// <param name="scalar"></param>
/// <param name="v"></param>
/// <returns></returns>
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

/// <summary>
/// 三维向量的内积（点乘）
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// <summary>
/// 三维向量的外积（x乘）
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

/// <summary>
/// 三维向量的长度
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Length(const struct Vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/// <summary>
/// 三维向量归一化（正规化）
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
struct Vector3 Normalize(const struct Vector3& v) {
	struct Vector3 result;
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	else {
		result = v;
	}
	return result;
}


/// <summary>
/// ***************************************************************四维矩阵
/// </summary>

/// <summary>
/// 四维矩阵输出
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="matrix"></param>
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int row = 0; row < 4; ++row) {
        for (int colum = 0; colum < 4; ++colum) {
            Novice::ScreenPrintf(x + colum * kColumnWidth,y + (row + 1) * kRowHeight,"%6.02f",matrix.m[row][colum]);
        }
    } 
}

/// <summary>
/// 四维矩阵加法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

/// <summary>
/// 四维矩阵减法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

/// <summary>
/// 四维矩阵乘法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

/// <summary>
/// 四维矩阵的转置矩阵
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

/// <summary>
/// 四维矩阵的逆矩阵
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
int GaussianElimination(float matrix[4][4 * 2]) {
    for (int i = 0; i < 4; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < 4; ++k) {
            if (fabs(matrix[k][i]) > fabs(matrix[maxRow][i])) {
                maxRow = k;
            }
        }
        if (matrix[maxRow][i] == 0) {
            return 0; 
        }
        if (maxRow != i) {
            for (int k = 0; k < 4 * 2; ++k) {
                float temp = matrix[i][k];
                matrix[i][k] = matrix[maxRow][k];
                matrix[maxRow][k] = temp;
            }
        }
        for (int j = i + 1; j < 4; ++j) {
            float factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < 4 * 2; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
    for (int i = 4 - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            float factor = matrix[j][i] / matrix[i][i];
            for (int k = 4 * 2 - 1; k >= i; --k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }    for (int i = 0; i < 4; ++i) {
        float factor = 1 / matrix[i][i];
        for (int j = i; j < 4 * 2; ++j) {
            matrix[i][j] *= factor;
        }
    }
    return 1;
}
Matrix4x4 Inverse(const Matrix4x4& m) {
    float augmentedMatrix[4][4 * 2];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            augmentedMatrix[i][j] = m.m[i][j];
            augmentedMatrix[i][j + 4] = (i == j) ? 1.0f : 0.0f;
        }
    }
    if (!GaussianElimination(augmentedMatrix)) {
        printf("Matrix is singular, inverse does not exist.\n");
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = NAN;
            }
        }
        return result;
    }
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = augmentedMatrix[i][j + 4];
        }
    }
    return result;
}

/// <summary>
/// 4维单位矩阵
/// </summary>
/// <returns></returns>
Matrix4x4 MakeIdentity4x4() {
    Matrix4x4 identity;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            identity.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
    return identity;
}

/// <summary>
/// 坐标变换
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	float w; // 添加一个变量用于存储透视除法后的 w 值
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	// 检查 w 是否为零，如果为零则返回一个错误的向量
	if (w == 0.0f) {
		// 在这里可以进行错误处理，例如输出错误信息或者返回一个特定的错误向量
		// 这里简单地返回一个零向量
		return { 0.0f, 0.0f, 0.0f };
	}

	// 执行透视除法
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

/// <summary>
/// 3次元扩大缩小行列
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix4x4 MakeScaleMatrix(const Vector3& scale){
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
}

/// <summary>
/// 3次元平行移动行列
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeTranslateMatrix(const Vector3& translate){
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;
	return result;
}

/// <summary>
/// 3次元X轴旋转
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateXMatrix(float radian){
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = cosf(radian);
	result.m[1][2] = sinf(radian);
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = -sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
}

/// <summary>
/// 3次元Y轴旋转
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateYMatrix(float radian){
	Matrix4x4 result;
	result.m[0][0] = cosf(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -sinf(radian);
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = sinf(radian);
	result.m[2][1] = 0;
	result.m[2][2] = cosf(radian);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
}

/// <summary>
/// 3次元Z轴旋转
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateZMatrix(float radian){
	Matrix4x4 result;
	result.m[0][0] = cosf(radian);
	result.m[0][1] = sinf(radian);
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = -sinf(radian);
	result.m[1][1] = cosf(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
}

/// <summary>
/// 4x4矩阵的乘法
/// </summary>
/// <param name="Matrix1"></param>
/// <param name="Matrix2"></param>
/// <returns></returns>
Matrix4x4 MultiplyMatrix4x4(const Matrix4x4& Matrix1, const Matrix4x4& Matrix2){
	Matrix4x4 result;
	for (int i = 0; i < MATRIX_SIZE4; i++) {
		for (int j = 0; j < MATRIX_SIZE4; j++) {
			result.m[i][j] = 0; // 初始化结果矩阵的元素为0
			for (int k = 0; k < MATRIX_SIZE4; k++) {
				result.m[i][j] += Matrix1.m[i][k] * Matrix2.m[k][j];
			}
		}
	}
	return result;
}

/// <summary>
/// 3次元旋转矩阵
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 rotateMatrix(Vector3 radian) {
	Matrix4x4 result;
	result = MultiplyMatrix4x4(MakeRotateXMatrix(radian.x), MultiplyMatrix4x4(MakeRotateYMatrix(radian.y), MakeRotateZMatrix(radian.z)));
	return result;
}

/// <summary>
/// 扩缩旋转移动 SRT 3 in 1 矩阵
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result;
	result = MultiplyMatrix4x4(MakeScaleMatrix(scale), MultiplyMatrix4x4(rotateMatrix(rotate), MakeTranslateMatrix(translate)));
	return result;
}

/// <summary>
/// 透视投影矩阵
/// </summary>
/// <param name="fovY"></param>
/// <param name="aspectRatio"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
/// <returns></returns>
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result = { 0 };
	float tanHalfFovY = tanf(fovY / 2.0f);
	float range = farClip - nearClip;
	result.m[0][0] = 1.0f / (aspectRatio * tanHalfFovY);
	result.m[1][1] = 1.0f / tanHalfFovY;
	result.m[2][2] = farClip / range;
	result.m[2][3] = 1.0f;
	result.m[3][2] = -1.0f *farClip * nearClip / range;
	return result;
}

/// <summary>
/// 正射影矩阵
/// </summary>
/// <param name="left"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
/// <param name="top"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
/// <returns></returns>
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result = { 0 };
	float lr = 1.0f / (right - left);
	float bt = 1.0f / (top - bottom);
	float nf = 1.0f / (farClip - nearClip);
	result.m[0][0] = 2.0f * lr;
	result.m[1][1] = 2.0f * bt;
	result.m[2][2] = nf;
	result.m[3][0] = -(right + left) * lr;
	result.m[3][1] = -(top + bottom) * bt;
	result.m[3][2] = -nearClip / nf;
	result.m[3][3] = 1.0f;
	return result;
}

/// <summary>
/// Viewport变换矩阵
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="minDepth"></param>
/// <param name="maxDepth"></param>
/// <returns></returns>
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = { 0 };
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float depthRange = maxDepth - minDepth;
	result.m[0][0] = halfWidth;
	result.m[1][1] = -halfHeight; // Y坐标通常是从上到下递增的，所以这里是负的
	result.m[2][2] = depthRange;
	result.m[3][0] = left + halfWidth;
	result.m[3][1] = top + halfHeight;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;
	return result;
}

