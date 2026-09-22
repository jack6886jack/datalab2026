/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(x&y))&(~(~x&~y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(x)
        if(y)
            if((x>>31)^(y>>31))
                return 0;
            else
                return 1;
        else
            return 0;
    else
        if(y)
            return 0;
        else
            return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int answer = 0;
    int shift = 0;
    shift = ((v >> 16) > 0) << 4;
    answer = answer | shift;
    v = v >> shift;
    shift = ((v >> 8) > 0) << 3;
    answer = answer | shift;
    v = v >> shift;
    shift = ((v >> 4) > 0) << 2;
    answer = answer | shift;
    v = v >> shift;
    shift = ((v >> 2) > 0) << 1;
    answer = answer | shift;
    v = v >> shift;
    shift = ((v >> 1) > 0);
    answer = answer | shift;
    v = v >> shift;
    return answer;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int check = 0x000000FF;
    int an , am;
    n = n << 3;
    m = m << 3;
    an = (x >> n) & check;
    am = (x >> m) & check;
    // printf("%d %d %d %d %d\n", x, an, am, n, m);
    int answer = x;
    answer = answer ^ (an << n);
    answer = answer ^ (am << m);
    answer = answer ^ (an << m);
    answer = answer ^ (am << n);
    return answer;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    // int i = 32;
    // unsigned answer = 0;
    // while (i)
    // {
    //     answer = answer << 1;
    //     answer = answer | (v & 1);
    //     v = v >> 1;
    //     i = i + (-1);
    // }
    // return answer;
    v = (v >> 16 & 0x0000FFFF) + (v << 16 & 0xFFFF0000);
    v = (v >> 8 & 0x00FF00FF) + (v << 8 & 0xFF00FF00);
    v = (v >> 4 & 0x0F0F0F0F) + (v << 4 & 0xF0F0F0F0);
    v = (v >> 2 & 0x33333333) + (v << 2 & 0xCCCCCCCC);
    v = (v >> 1 & 0x55555555) + (v << 1 & 0xAAAAAAAA);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
// int printf(const char *format, ...);
int logicalShift(int x, int n) {
    int answer = x,check = 0,minus_1 = 0xFFFFFFFF;
    answer = answer >> n;
    check = !(!n) << 31;
    check = ~(check >> (n + minus_1));
    // printf("%d %d %d %d\n",x,n,answer,check);
    return answer & check;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int answer = 0, shift;
    shift = !((x & 0xFFFF0000) ^ 0xFFFF0000) << 4;
    answer += shift;
    x = x << shift;
    shift = !((x & 0xFF000000) ^ 0xFF000000) << 3;
    answer += shift;
    x = x << shift;
    shift = !((x & 0xF0000000) ^ 0xF0000000) << 2;
    answer += shift;
    x = x << shift;
    shift = !((x & 0xC0000000) ^ 0xC0000000) << 1;
    answer += shift;
    x = x << shift;
    shift = !((x & 0x80000000) ^ 0x80000000);
    answer += shift;
    x = x << shift;
    shift = !((x & 0x80000000) ^ 0x80000000);
    answer += shift;
    return answer;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    return 2;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    return 2;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    return 2;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
