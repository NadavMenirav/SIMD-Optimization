long decode_c_version(long x, long y, long z);

long decode_c_version(long x, long y, long z) {
    long result = 0;
    y = y - z;
    x = x * y;
    result = y;
    result = result % 2 == 0 ? 0: -1; // The arithmetic shift
    result = result ^ x;
    return result;
}