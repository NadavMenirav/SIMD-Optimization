#include <xmmintrin.h> //SSE1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pmmintrin.h> //SSE3

#define MAX_STR 255
#define FLOAT_SIZE 4
#define NUMBER_OF_FLOATS_IN_REGISTER 4


// This function will calculate the difficult formula fast, using intrinsics of course.
float formula1(float *x, unsigned int length) {
    int sumOfSquareRoots = 0;
    const float *array = x;

    // We store the array in chunks of 4, each chunk in a xmm register.
    for (int i = 0; i < length / FLOAT_SIZE; i++, array += NUMBER_OF_FLOATS_IN_REGISTER) {

        // We extract the current 4 floats we are working with
        const __m128 currentFourFloats = _mm_loadu_ps(array);

        // Compute the square roots
        __m128 squareRootFourFloats = _mm_sqrt_ps(currentFourFloats);



    }
}
