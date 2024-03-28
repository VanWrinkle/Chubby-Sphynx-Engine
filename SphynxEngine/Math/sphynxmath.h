//
// Created by andre on 25.12.22.
//

#ifndef CHUBBYSPHYNXENGINE_SPHYNXMATH_H
#define CHUBBYSPHYNXENGINE_SPHYNXMATH_H

#include <glm/glm.hpp>


namespace sem {
    using namespace glm;

    template <typename T>
    float min (const T &val, const T &val2) {
        return (val < val2) ? val : val2;
    }

    template <typename T>
    float max (const T &val, const T &val2) {
        return (val > val2) ? val2 : val;
    }

    float clamp (const float &min, const float &max, const float &value) {
        if(value < min) {
            return min;
        }
        if(value > max) {
            return max;
        }
        return value;
    }

    template <typename T>
    T lerp (const T &val, const T &val2, const float& blend) {
        return static_cast<T>(val * (1.0f - blend) + val2 * blend);
    }


    template <typename T>
    T mix (const T &val, const T &val2, const float& blend) {
        return lerp(val, val2, blend);
    }


    template <typename T>
    float smoothstep(const T &edge0, const T &edge1, T x) {
        x = clamp(0.0f, 1.0f, (x - edge0) / (edge1-edge0));
        return x * x * (3 - 2 * x);
    }

    template <typename T>
    float smootherstep(const T &edge0, const T &edge1, T x) {
        x = clamp(0.0f, 1.0f, (x - edge0) / (edge1 - edge0));
        return x * x * x * ( x * (x * 6 - 15) + 10);
    }

    // Assumes an x in range 0..1
    float smoothstepSimple ( const float &x ){
        return x * x * (3 - 2 * x);
    }

    // Assumes an x in range 0..1
    float smootherstepSimple( const float &x ) {
        return x * x * x * ( x * (x * 6 - 15) + 10);
    }











}

#endif //CHUBBYSPHYNXENGINE_SPHYNXMATH_H

