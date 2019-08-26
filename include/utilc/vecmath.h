#ifndef UTILC_VECMATH_H
#define UTILC_VECMATH_H

#include <math.h>   //sqrt(f)

//
// this header file has the following content:
//
// 1. macros for vector math
// 2. functions for vector math
// 3. functions for specific sized vector
//

//
// 1. macros
//

/** vec<n> res_i = vec_i */
#define VecCopy(out_set, vec, n)\
for (int i = 0; i < (n); i++) {\
    (out_set)[i] = (vec)[i];\
}

/** vec<n> res_i = scalar */
#define VecSet(out_set, scalar, n)\
for (int i = 0; i < (n); i++) {\
    (out_set)[i] = (scalar);\
}

/** vec<n> res_i = a_i + b_i */
#define VecAddVec(out_vec, vec_a, vec_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] + (vec_b)[i];\
}

/** vec<n> res_i = a_i + b */
#define VecAddSca(out_vec, vec_a, sca_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a=[i] + (sca_b);\
}

/** vec<n> res_i = a_i - b_i */
#define VecSubVec(out_vec, vec_a, vec_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] - (vec_b)[i];\
}

/** vec<n> res_i = a_i * b_i */
#define VecScaleVec(out_vec, vec_a, vec_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] * (vec_b)[i];\
}

/** * vec<n> res_i = a_i * b */
#define VecScaleSca(out_vec, vec_a, sca_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] * (sca_b);\
}


/** sca = vec[0] + vec[1] + ... + vec[n-1] */
#define VecSum(out_sca, vec, n)\
{\
    (out_sca) = 0;\
    for (int i = 0; i < (n); i++) {\
        (out_sca) += (vec)[i]; \
    }\
}

/** sca = vec<n> dot vec<n> */
#define VecDot(out_sca, vec_a, vec_b, n)\
{\
    (out_sca) = 0;\
    for (int i = 0; i < (n); i++) {\
        (out_sca) += (vec_a)[i] * (vec_b)[i];\
    }\
}

/** vec3 res = a cross b, all values after the third will be set to 1 */
#define VecCross(out_vec, vec_a, vec_b, n)\
{\
    (out_vec)[0] = (vec_a)[1] * (vec_b)[2] - (vec_a)[2] * (vec_b)[1];\
    (out_vec)[1] = (vec_a)[2] * (vec_b)[0] - (vec_a)[0] * (vec_b)[2];\
    (out_vec)[2] = (vec_a)[0] * (vec_b)[1] - (vec_a)[1] * (vec_b)[0];\
    for (int i=3; i<n; i++) {\
        (out_vec)[i] = 1;\
    }\
}

//
// 2. functions
//


//
// vec = float
//
/** vec<n> dst_i = vec_i */
static void vec_copy(float *dst_vec, const float *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** vec<n> dst_i = scalar */
static void vec_set(float *dst_vec, float scalar, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = scalar;
}

/** vec<n> dst_i = a_i + b_i */
static void vec_add_vec(float *dst_vec, const float *vec_a, const float *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + vec_b[i];
}

/** vec<n> dst_i = a_i + b */
static void vec_add_sca(float *dst_vec, const float *vec_a, float scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + scalar_b;
}

/** vec<n> dst_i = a_i - b_i */
static void vec_sub_vec(float *dst_vec, const float *vec_a, const float *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - vec_b[i];
}

/** vec<n> dst_i = a_i * b_i */
static void vec_scale_vec(float *dst_vec, const float *vec_a, const float *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * vec_b[i];
}

/** vec<n> res_i = a_i * b */
static void vec_scale_sca(float *dst_vec, const float *vec_a, float scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * scalar_b;
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static float vec_sum(const float *vec, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    return sum;
}

/** returns vec<n> dot vec<n> */
static float vec_dot(const float *vec_a, const float *vec_b, int n) {
    float dot = 0;
    for (int i = 0; i < n; i++)
        dot += vec_a[i] * vec_b[i];
    return dot;
}

/** vec3 dst = a cross b, all values after the third will be set to 1 */
static void vec_cross(float *dst_vec, const float *vec_a, const float *vec_b, int n) {
    dst_vec[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    dst_vec[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    dst_vec[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
    for (int i = 3; i < n; i++)
        dst_vec[i] = 1;
}

/** returns norm2 of a float vector */
static float vec_norm(const float *vec, int n) {
    return sqrtf(vec_dot(vec, vec, n));
}

/** dst = vec / norm(vec) */
static void vec_normalize(float *dst_vec, const float *vec, int n) {
    vec_scale_sca(dst_vec, vec, 1.0f / vec_norm(vec, n), n);
}


//
// vecd = double
//
/** vec<n> dst_i = vec_i */
static void vecd_copy(double *dst_vec, const double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** vec<n> dst_i = scalar */
static void vecd_set(double *dst_vec, double scalar, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = scalar;
}

/** vec<n> dst_i = a_i + b_i */
static void vecd_add_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + vec_b[i];
}

/** vec<n> dst_i = a_i + b */
static void vecd_add_sca(double *dst_vec, const double *vec_a, double scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + scalar_b;
}

/** vec<n> dst_i = a_i - b_i */
static void vecd_sub_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - vec_b[i];
}

/** vec<n> dst_i = a_i * b_i */
static void vecd_scale_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * vec_b[i];
}

/** vec<n> res_i = a_i * b */
static void vecd_scale_sca(double *dst_vec, const double *vec_a, double scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * scalar_b;
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double vecd_sum(const double *vec, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    return sum;
}

/** returns vec<n> dot vec<n> */
static double vecd_dot(const double *vec_a, const double *vec_b, int n) {
    double dot = 0;
    for (int i = 0; i < n; i++)
        dot += vec_a[i] * vec_b[i];
    return dot;
}

/** vec3 dst = a cross b, all values after the third will be set to 1 */
static void vecd_cross(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    dst_vec[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    dst_vec[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    dst_vec[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
    for (int i = 3; i < n; i++)
        dst_vec[i] = 1;
}

/** returns norm2 of a double vector */
static double vecd_norm(const double *vec, int n) {
    return sqrt(vecd_dot(vec, vec, n));
}

/** dst = vec / norm(vec) */
static void vecd_normalize(double *dst_vec, const double *vec, int n) {
    vecd_scale_sca(dst_vec, vec, 1.0f / vecd_norm(vec, n), n);
}


//
// 3. specific size functions
//

//
// Vec3
//
typedef struct {
    float v[3];
} Vec3;

/** vec<n> dst_i = vec_i */
static Vec3 vec3_copy(const float *vec) {
    Vec3 res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec[i];
    return res;
}

/** vec<n> dst_i = scalar */
static Vec3 vec3_set(float scalar) {
    Vec3 res;
    for (int i = 0; i < 3; i++)
        res.v[i] = scalar;
    return res;
}

/** vec<n> dst_i = a_i + b_i */
static Vec3 vec3_add_vec(const float *vec_a, const float *vec_b) {
    Vec3 res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] + vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i + b */
static Vec3 vec3_add_sca(const float *vec_a, float scalar_b) {
    Vec3 res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] + scalar_b;
    return res;
}

/** vec<n> dst_i = a_i - b_i */
static Vec3 vec3_sub_vec(const float *vec_a, const float *vec_b) {
    Vec3 res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] - vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i * b_i */
static Vec3 vec3_scale_vec(const float *vec_a, const float *vec_b) {
    Vec3 res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] * vec_b[i];
    return res;
}

/** vec<n> res_i = a_i * b */
static Vec3 vec3_scale_sca(const float *vec_a, float scalar_b) {
    Vec3 res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] * scalar_b;
    return res;
}

/** vec3 dst = a cross b */
static Vec3 vec3_cross(const float *vec_a, const float *vec_b) {
    Vec3 res;
    res.v[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    res.v[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    res.v[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
    return res;
}

/** dst = vec / norm(vec) */
static Vec3 vec3_normalize(const float *vec) {
    return vec3_scale_sca(vec, 1.0f / vec_norm(vec, 3));
}


//
// Vec3d
//
typedef struct {
    double v[3];
} Vec3d;

/** vec<n> dst_i = vec_i */
static Vec3d vec3d_copy(const double *vec) {
    Vec3d res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec[i];
    return res;
}

/** vec<n> dst_i = scalar */
static Vec3d vec3d_set(double scalar) {
    Vec3d res;
    for (int i = 0; i < 3; i++)
        res.v[i] = scalar;
    return res;
}

/** vec<n> dst_i = a_i + b_i */
static Vec3d vec3d_add_vec(const double *vec_a, const double *vec_b) {
    Vec3d res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] + vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i + b */
static Vec3d vec3d_add_sca(const double *vec_a, double scalar_b) {
    Vec3d res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] + scalar_b;
    return res;
}

/** vec<n> dst_i = a_i - b_i */
static Vec3d vec3d_sub_vec(const double *vec_a, const double *vec_b) {
    Vec3d res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] - vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i * b_i */
static Vec3d vec3d_scale_vec(const double *vec_a, const double *vec_b) {
    Vec3d res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] * vec_b[i];
    return res;
}

/** vec<n> res_i = a_i * b */
static Vec3d vec3d_scale_sca(const double *vec_a, double scalar_b) {
    Vec3d res;
    for (int i = 0; i < 3; i++)
        res.v[i] = vec_a[i] * scalar_b;
    return res;
}

/** vec3 dst = a cross b */
static Vec3d vec3d_cross(const double *vec_a, const double *vec_b) {
    Vec3d res;
    res.v[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    res.v[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    res.v[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
    return res;
}

/** dst = vec / norm(vec) */
static Vec3d vec3d_normalize(const double *vec) {
    return vec3d_scale_sca(vec, 1.0f / vecd_norm(vec, 3));
}


//
// Vec4
//
typedef struct {
    float v[4];
} Vec4;

/** vec<n> dst_i = vec_i */
static Vec4 vec4_copy(const float *vec) {
    Vec4 res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec[i];
    return res;
}

/** vec<n> dst_i = scalar */
static Vec4 vec4_set(float scalar) {
    Vec4 res;
    for (int i = 0; i < 4; i++)
        res.v[i] = scalar;
    return res;
}

/** vec<n> dst_i = a_i + b_i */
static Vec4 vec4_add_vec(const float *vec_a, const float *vec_b) {
    Vec4 res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] + vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i + b */
static Vec4 vec4_add_sca(const float *vec_a, float scalar_b) {
    Vec4 res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] + scalar_b;
    return res;
}

/** vec<n> dst_i = a_i - b_i */
static Vec4 vec4_sub_vec(const float *vec_a, const float *vec_b) {
    Vec4 res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] - vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i * b_i */
static Vec4 vec4_scale_vec(const float *vec_a, const float *vec_b) {
    Vec4 res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] * vec_b[i];
    return res;
}

/** vec<n> res_i = a_i * b */
static Vec4 vec4_scale_sca(const float *vec_a, float scalar_b) {
    Vec4 res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] * scalar_b;
    return res;
}

/** vec4 dst = a cross b, the fourth component (w) will be set to 1 */
static Vec4 vec4_cross(const float *vec_a, const float *vec_b) {
    Vec4 res;
    res.v[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    res.v[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    res.v[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
    res.v[3] = 1;
    return res;
}

/** dst = vec / norm(vec) */
static Vec4 vec4_normalize(const float *vec) {
    return vec4_scale_sca(vec, 1.0f / vec_norm(vec, 4));
}


//
// Vec4d
//
typedef struct {
    double v[4];
} Vec4d;

/** vec<n> dst_i = vec_i */
static Vec4d vec4d_copy(const double *vec) {
    Vec4d res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec[i];
    return res;
}

/** vec<n> dst_i = scalar */
static Vec4d vec4d_set(double scalar) {
    Vec4d res;
    for (int i = 0; i < 4; i++)
        res.v[i] = scalar;
    return res;
}

/** vec<n> dst_i = a_i + b_i */
static Vec4d vec4d_add_vec(const double *vec_a, const double *vec_b) {
    Vec4d res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] + vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i + b */
static Vec4d vec4d_add_sca(const double *vec_a, double scalar_b) {
    Vec4d res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] + scalar_b;
    return res;
}

/** vec<n> dst_i = a_i - b_i */
static Vec4d vec4d_sub_vec(const double *vec_a, const double *vec_b) {
    Vec4d res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] - vec_b[i];
    return res;
}

/** vec<n> dst_i = a_i * b_i */
static Vec4d vec4d_scale_vec(const double *vec_a, const double *vec_b) {
    Vec4d res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] * vec_b[i];
    return res;
}

/** vec<n> res_i = a_i * b */
static Vec4d vec4d_scale_sca(const double *vec_a, double scalar_b) {
    Vec4d res;
    for (int i = 0; i < 4; i++)
        res.v[i] = vec_a[i] * scalar_b;
    return res;
}

/** vec4 dst = a cross b, the fourth component (w) will be set to 1 */
static Vec4d vec4d_cross(const double *vec_a, const double *vec_b) {
    Vec4d res;
    res.v[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    res.v[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    res.v[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
    res.v[3] = 1;
    return res;
}

/** dst = vec / norm(vec) */
static Vec4d vec4d_normalize(const double *vec) {
    return vec4d_scale_sca(vec, 1.0f / vecd_norm(vec, 4));
}

#endif //UTILC_VECMATH_H
