#include <stdint.h>

static const uint8_t perm[256] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
    36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
    234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
    88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
    134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
    230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
    1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
    116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
    124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
    47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
    154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
    108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
    242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
    239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
    50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
    141, 128, 195, 78, 66, 215, 61, 156, 180};

static uint8_t hash(int32_t i)
{
    return perm[(uint8_t)(i)];
}

static double grad(int32_t hash, double x, double y)
{
    const int32_t h = hash & 0x3F;  // Convert low 3 bits of hash code
    const double u = h < 4 ? x : y; // into 8 simple gradient directions,
    const double v = h < 4 ? y : x;

    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v); // and compute the dot product with (x,y).
}

static inline int32_t fastfloor(float fp)
{
    int32_t i = (int32_t)(fp);
    return (fp < i) ? (i - 1) : (i);
}

double noise(double x, double y, double scale)
{
    x *= scale;
    y *= scale;

    double n0, n1, n2; // Noise contributions from the three corners

    // Skewing/Unskewing factors for 2D
    static const double F2 = 0.366025403f; // F2 = (sqrt(3) - 1) / 2
    static const double G2 = 0.211324865f; // G2 = (3 - sqrt(3)) / 6   = F2 / (1 + 2 * K)

    // Skew the input space to determine which simplex cell we're in
    const double s = (x + y) * F2; // Hairy factor for 2D
    const double xs = x + s;
    const double ys = y + s;
    const int32_t i = fastfloor(xs);
    const int32_t j = fastfloor(ys);

    // Unskew the cell origin back to (x,y) space
    const double t = (double)(i + j) * G2;
    const double X0 = i - t;
    const double Y0 = j - t;
    const double x0 = x - X0; // The x,y distances from the cell origin
    const double y0 = y - Y0;

    int32_t i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if (x0 > y0)
    {
        i1 = 1;
        j1 = 0;
    }
    else
    {
        i1 = 0;
        j1 = 1;
    }

    const double x1 = x0 - i1 + G2;
    const double y1 = y0 - j1 + G2;
    const double x2 = x0 - 1.0f + 2.0f * G2;
    const double y2 = y0 - 1.0f + 2.0f * G2;

    const int gi0 = hash(i + hash(j));
    const int gi1 = hash(i + i1 + hash(j + j1));
    const int gi2 = hash(i + 1 + hash(j + 1));

    double t0 = 0.5f - x0 * x0 - y0 * y0;
    if (t0 < 0.0f)
    {
        n0 = 0.0f;
    }
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * grad(gi0, x0, y0);
    }

    double t1 = 0.5f - x1 * x1 - y1 * y1;
    if (t1 < 0.0f)
    {
        n1 = 0.0f;
    }
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * grad(gi1, x1, y1);
    }

    double t2 = 0.5f - x2 * x2 - y2 * y2;
    if (t2 < 0.0f)
    {
        n2 = 0.0f;
    }
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * grad(gi2, x2, y2);
    }

    return 45.23065f * (n0 + n1 + n2);
}

double noise_octave(double x, double y, double scale, int octave)
{
    double value = 0;
    double strength = 1;
    for (int i = 0; i < octave; i++)
    {
        value += noise(x, y, scale) * strength;
        strength /= 2;
        scale *= 2;
    }

    return value;
}