/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * <Wang Haoen 3018216021>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // Using Chinese comments under linux will be garbled
    // I think it should be caused by the coding problem
    // so the following unified use of English comments


    // check if 48 <= x < 58
    int x_minus_48 = x + (~48 + 1); // perform subtraction by bit operation
    int is_bigger_48 = (x_minus_48 >> 31) + 1;
    // get the highest bit
    // if x >= 48, (x_minus_48 >> 31) = 0, then the above variable is equal to 1
    // otherwise (x_minus_48 >> 31) = 1111...1111, after adding 1, the variable will be equal to 0

    int x_minus_58 = x + (~58 + 1); // perform subtraction by bit operation
    int is_lower_58 = !((x_minus_58 >> 31) + 1);
    // Similar to the above operation
    // if x < 58, (x_minus_58 >> 31) = 1111...1111, after adding 1 and performing not operation the above variable is equal to 1
    // otherwise it will be 0

    return is_bigger_48 & is_lower_58;
    //if and only if 48 <= x < 58, return 1
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
    int x1 = x >> 8;
    int x2 = x1 >> 8;
    int x3 = x2 >> 8;
    int xx = x | x1 | x2 | x3;
    // integrate 32-bit information into the lowest 8 bits

    return !!(xx & 0x55);
    // make xx & 01010101
    // if the result is not 0, it means there are 1 on the even bits of x
    // using !! to change the return value to 1(otherwise it might be a big integer)
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    // if the 0 bit is 1, the result is 0xFFFFFFFF(1111...1111)
    // if the 0 bit is 0, the result is 0x00000000(0000...0000)


    int lowest_bit = x & 1;
    // get the lowest bit

    return (~lowest_bit + 1);
    // just return -lowest_bit, using bit operations to achieve negative operations
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
    // one of the common operations of ACM, find the lowest 1 bit
    // (-x)&x

    return (~x+1) & x;
    // using bit operations to achieve negative operations
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int highest_bit = (x >> 31) + 1;
    // if the highest bit is 1, the above variable is 0
    // otherwise it will be 1

    int x1 = x >> n;
    // result, rounded down by default

    int x2 = x1 << n;
    int is_divisible = !!(x ^ x2);
    // if x is an integral multiple of 2^n, then this value is 0
    // otherwise it will be 1
    // using !! to change the variable to 1

    return x1 + ((!highest_bit) & (!!n) & is_divisible);
    // if x is a negative number && (n != 0) && (x % 2^n != 0), round up,
    // using !! to change the variable to 1
}


/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    // int mask = 0x11111111;
    int mask = (0x11 << 24) | (0x11 << 16) | (0x11 << 8) | 0x11;
    //only numbers within 0xFF are allowed, so we can only implement it like this

    int count = x & mask; //collect bits:0 4 8 12 16 20 24 28
    x = x >> 1;
    count = count + (x & mask); //collect bits:1 5 9 13 17 21 25 29
    x = x >> 1;
    count = count + (x & mask); //collect bits:2 6 10 14 18 22 26 30
    x = x >> 1;
    count = count + (x & mask); //collect bits:3 7 11 15 19 23 27 31
    // store the number of these four positions 1 every 4 bits

    res = (count & 0x0f) +
            ((count >> 4) & 0x0f) +
            ((count >> 8) & 0x0f) +
            ((count >> 12) & 0x0f) +
            ((count >> 16) & 0x0f) +
            ((count >> 20) & 0x0f) +
            ((count >> 24) & 0x0f) +
            ((count >> 28) & 0x0f);
    // extract results every 4 digits
    return res;
}

