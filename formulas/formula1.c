#include <xmmintrin.h> //SSE1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pmmintrin.h> //SSE3

#define MAX_STR 255
#define FLOAT_SIZE 4
#define NUMBER_OF_FLOATS_IN_REGISTER 4

float formula1(float *x, unsigned int length);
float sumFloats(__m128 a);
float mulFloats(__m128 a);

// This function will calculate the difficult formula fast, using intrinsics of course.
float formula1(float *x, unsigned int length) {
    float sumOfSquareRoots = 0;
    const float *array = x;

    // We store the array in chunks of 4, each chunk in a xmm register.
    for (int i = 0; i < length / FLOAT_SIZE; i++, array += NUMBER_OF_FLOATS_IN_REGISTER) {

        // We extract the current 4 floats we are working with
        const __m128 currentFourFloats = _mm_loadu_ps(array);

        // Compute the square roots
        __m128 squareRootFourFloats = _mm_sqrt_ps(currentFourFloats);

        // Adding the sum of square roots of current floats to the overall sum
        sumOfSquareRoots += sumFloats(currentFourFloats);

        // Compute the values squared
        const __m128 fourFloatsSquared = _mm_mul_ps(currentFourFloats, currentFourFloats);

        // Creating the array of ones that will be added to the squared floats
        const __m128 onesRegister = _mm_set1_ps(1);

        // Adding the ones register to the squared floats
        __m128 squaredPlusOne = _mm_add_ps(fourFloatsSquared, onesRegister);





    }
}

// This function receives a xmm register containing four floats and will return the sum of them.
float sumFloats(const __m128 a) {
    const __m128 middleStep = _mm_hadd_ps(a, a);
    const __m128    resultRegister = _mm_hadd_ps(middleStep, middleStep);
    return _mm_cvtss_f32(resultRegister);

}

// This function receives a xmm register containing four floats and will return the product of them.
float mulFloats(const __m128 a) {

    // The result
    __m128 product = a;

    /*
     * The register 'a' is as such: [float_1, float_2, float_3, float_4]
     * We shuffle 'a' to get:       [float 2, float 1, float 4, float 3]
     * Then we multiply to get:     [float_1 * float_2, XXX, float_3 * float_4, YYY]
     * Then we shuffle the multiplication to get: [float_3 * float_4, XXX, float_1 * float 2, YYY]
     * Then multiply the two registers to receive the product in the first entry
     *
     */

    const __m128 secondStep = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));
    const __m128 thirdStep = _mm_mul_ps(a, secondStep);
    const __m128 fourthStep = _mm_shuffle_ps(thirdStep, thirdStep, _MM_SHUFFLE(3, 0, 1, 2));

    // Now we multiply third and fourth steps to get the result in the first entry.
    const __m128 result = _mm_mul_ps(thirdStep, fourthStep);
    return _mm_cvtss_f32(result);
}
