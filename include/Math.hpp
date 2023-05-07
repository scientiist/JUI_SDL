#include <random>

typedef float float32;
typedef double float64;
typedef long double float128;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;


    class Math{
    public:
        static float32 Lerp(float32 a, float32 b, float32 t)     { return (1-t)*a + t*b; }
        static float64 Lerp(float64 a, float64 b, float64 t)     { return (1-t)*a + t*b; }
        static float128 Lerp(float128 a, float128 b, float128 t) { return (1-t)*a + t*b; }

        static float32 Round(float32 n, int decimals = 0) {
            float32 deci = 10^(decimals);
            return floor(n*deci+0.5)/deci;
        }
        static float64 Round(float64 n, int decimals = 0) {
            float64 deci = 10^(decimals);
            return floor(n*deci+0.5)/deci;
        }
        static float128 Round(float128 n, int decimals = 0) {
            float128 deci = 10^(decimals);
            return floor(n*deci+0.5)/deci;
        }

        static float32 Clamp(float32 n, float32 min, float32 max) {
            return std::min(std::max(min, n), max);
        }
        static float64 Clamp(float64 n, float64 min, float64 max) {
            return std::min(std::max(min, n), max);
        }
        static float128 Clamp(float128 n, float128 min, float128 max) {
            return std::min(std::max(min, n), max);
        }

    };
