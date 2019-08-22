#ifndef UTILC_VECMATH_H
#define UTILC_VECMATH_H

#include <math.h>   //sqrt(f)


/** vec<n> res_i = vec_i */
#define VecVecSet(out_set, vec, n)\
for (int i = 0; i < (n); i++) {\
    (out_set)[i] = (vec)[i];\
}

/** vec<n> res_i = scalar */
#define VecScaSet(out_set, scalar, n)\
for (int i = 0; i < (n); i++) {\
    (out_set)[i] = (scalar);\
}

/** vec<n> res_i = a_i + b_i */
#define VecVecSum(out_vec, vec_a, vec_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] + (vec_b)[i];\
}

/** vec<n> res_i = a_i + b */
#define VecScaSum(out_vec, vec_a, sca_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a=[i] + (sca_b);\
}

/** vec<n> res_i = a_i - b_i */
#define VecVecSub(out_vec, vec_a, vec_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] - (vec_b)[i];\
}

/** vec<n> res_i = a_i * b_i */
#define VecVecScale(out_vec, vec_a, vec_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] * (vec_b)[i];\
}

/** * vec<n> res_i = a_i * b */
#define VecScaScale(out_vec, vec_a, sca_b, n)\
for (int i = 0; i < (n); i++) {\
    (out_vec)[i] = (vec_a)[i] * (sca_b);\
}

/** sca = vec<n> dot vec<n> */
#define VecDot(out_sca, vec_a, vec_b, n)\
{\
    (out_sca) = 0;\
    for (int i = 0; i < (n); i++) {\
        (out_sca) += (vec_a)[i] * (vec_b)[i];\
    }\
}

/** vec3 res = a cross b */
#define Vec3Cross(out_vec3, vec3_a, vec3_b)\
{\
    (out_vec3)[0] = (vec3_a)[1] * (vec3_b)[2] - (vec3_a)[2] * (vec3_b)[1];\
    (out_vec3)[1] = (vec3_a)[2] * (vec3_b)[0] - (vec3_a)[0] * (vec3_b)[2];\
    (out_vec3)[2] = (vec3_a)[0] * (vec3_b)[1] - (vec3_a)[1] * (vec3_b)[0];\
}


/** sca = norm2 of a float vector */
#define VecfNorm(out_sca, vecf, n)\
{\
    VecDot((out_sca), vecf, vecf, n)\
    (out_sca) = sqrtf((out_sca));\
}
/** sca = norm2 of a double vector */
#define VecdNorm(out_sca, vecd, n)\
{\
    VecDot((out_sca), vecd, vecd, n)\
    (out_sca) = sqrt((out_sca));\
}

/** out = vecf / norm(a) */
#define VecfNormalize(out_vec, vecf, n)\
{\
    float vecfnormalize_norm_;\
    VecfNorm(vecfnormalize_norm_, vecf, n)\
    VecScaScale((out_vec), (vecf), 1.0f / vecfnormalize_norm_, n);\
}
/** out = vecf / norm(a) */
#define VecdNormalize(out_vec, vecd, n)\
{\
    float vecdnormalize_norm_;\
    VecdNorm(vecdnormalize_norm_, vecd, n)\
    VecScaScale((out_vec), (vecd), 1.0 / vecdnormalize_norm_, n);\
}


#endif //UTILC_VECMATH_H
