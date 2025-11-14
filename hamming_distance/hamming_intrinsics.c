#include <emmintrin.h>   // SSE2
#include <smmintrin.h>   // SSE4.1
#include <string.h>

#define MAX_STR 256

size_t local_strlen(const char *s);

/*
 * This function will calculate the hamming distance of two strings using C intrinsics.
 * We will store the string in two chunks of 128bit xmm registers and compare the two registers by their bytes.
 * The result of the matches will be stored in a xmm register as well, and then we will use the "sad" function to sum
 * all the matches.
 */
int hamming_dist(char str1[MAX_STR], char str2[MAX_STR]) {

}

size_t local_strlen(const char *s) {
    for (int i = 0; i < MAX_STR; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
}