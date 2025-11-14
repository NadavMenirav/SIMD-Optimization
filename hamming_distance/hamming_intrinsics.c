#include <emmintrin.h>   // SSE2
#include <smmintrin.h>   // SSE4.1
#include <string.h>

#define MAX_STR 256

int local_strlen(const char *s);
int hamming_dist(char str1[MAX_STR], char str2[MAX_STR]);
int local_min(int a, int b);
int local_abs(int a);

/*
 * This function will calculate the hamming distance of two strings using C intrinsics.
 * We will store the string in two chunks of 128bit xmm registers and compare the two registers by their bytes.
 * The result of the matches will be stored in a xmm register as well, and then we will use the "sad" function to sum
 * all the matches.
 */
int hamming_dist(char str1[MAX_STR], char str2[MAX_STR]) {

    // Calculating the lengths of the strings
    const int len1 = local_strlen(str1);
    const int len2 = local_strlen(str2);

    const int minLen = local_min(len1, len2);

    // We need minLen / 16 iterations rounded up.
    const int numberOfIterations = minLen / 16 + (minLen % 16 != 0);

    int currentLen = 0;

    // Storing the string in a char* so that we will be able to +=16 it.
    const char* pstr1 = str1;
    const char* pstr2 = str2;

    // Storing the strings in the xmm registers
    const __m128i firstString = _mm_loadu_si128((__m128i *)pstr1);
    const __m128i secondString = _mm_loadu_si128((__m128i *)pstr2);

    for (int i = 0; i < numberOfIterations; i++) {

        // Moving the strings up to the next 16 bytes.
        pstr1 += i * 16;
        pstr2 += i * 16;


    }
    /*
     * The function returns a xmm register that every bit in it represents whether the corresponding chars in
     * the array are equal
     */
    const __m128i matches = _mm_cmpeq_epi8(secondString, firstString);

    // The function sets the register 0
    const __m128i zeroString = _mm_setzero_si128();

    /*
     * The function splits the register in half and sums over it. we use the zero string because it first subtracts it
     * from our string
     */
    const __m128i sumOfMatches= _mm_sad_epu8(matches, zeroString);

    // The number of natches is calculated by taking the lower 16 bits  sumOfMatches and the 16 bits in the second half
    const int numberOfMatches = _mm_extract_epi32(sumOfMatches, 0) + _mm_extract_epi32(sumOfMatches, 4);

    const int numberOfDiff = 16 - numberOfMatches;
}

int local_strlen(const char *s) {
    for (int i = 0; i < MAX_STR; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return -1;
}

// Calculates the minimum value between two integers
int local_min(const int a, const int b) {
    return a < b ? a : b;
}


// Calculates the absolute value of an integer
int local_abs(const int a) {
    return a < 0 ? -a : a;
}