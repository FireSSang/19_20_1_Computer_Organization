/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * Haoen Wang 3018216021
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
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int a = (!x) << 31 >> 31;
    // if x=0,  !x=1, a = -1
    // if x!=0, !x=0, a = 0
    return (a & (y ^ z)) ^ y;
    // It is well known: a^a = 0;
    // a^0 = a

    // x=0: (a&(y^z)) = (y^z), return z
    // x!=0: (a&(y^z)) = 0, return y
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
    return (x >> 31) + 1;
    // if x>=0, the highest bit of x is 0, x>>31 = 0, return 1
    // if x<0 , the highest bit of x is 1, x>>31 = -1(1111...1111), return 0
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    // First get the sign of x and y,
    // if the signs are the same:
    //   if x>y, sign bit of (~y+x)=0,
    //   if x<y, sign bit of (~y+x)=1;
    // if the signs are not equal:
    //   if x>y, sign bit of (~y+x)=1,
    //   if x<y, sign bit of (~y+x)=0;
    // lastly, bitwise OR and logical NOT
    // the results from two if conditions
    int sign_x = x>>31;
    int sign_y = y>>31;
    int same = !(sign_x ^ sign_y) & ((~y + x) >> 31);
    int not_same = sign_x & !sign_y;
    int to_ret = !(same | not_same);
    return to_ret;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    int t = x >> 31; // get the highest bit of x
    return (t + x) ^ t;
    // It is well known: a^0=a
    // a^(-1) = ~a = -a-1

    // if x=0, t=0, x+t=0, 0^0=0, return 0
    // if x>0, t=0, x+t=x, x^0=0, return x
    // if x<0, t=-1, x+t=x-1, (x-1)^(-1) = -x+1-1 = -x, return -x
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
    // if x is 2^n, the highest bit of x should be 0
    // x   should be 000...010...000
    // x-1 should be 000...001...111
    // so (x-1)&x = 0
    int sign = !(x >> 31);
    return (!!x) & sign & !((x + ~1 + 1) & x);
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    // Other than NaN, top most bit of argument should be reversed
    // NaN remains unchanged as a return value
    // Get the part exponent
    unsigned exponent = (uf << 1) >> 24;
    // Get the part fraction
    unsigned fraction = uf << 9;
    unsigned is_exponent_full_1 = ! (exponent ^ 0xff);
    // Determine if this value a NaN
    unsigned is_NaN_or_not = is_exponent_full_1 && fraction;
    // If uf a NaN, keep it unchanged, else inverse the top most bit
    unsigned result = uf + ((! is_NaN_or_not) << 31);
    return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    // First determine the exponent bias based on the value x
    // Then keep the symbol of x, get the absolute value of x
    // Then determine the index of left most 1 of the abs x,
    // that index plus bias is the exponent of the single float
    // Left shifted that clears all left zero bits of abs x
    // right shifted and masked that leave 9 slots for symbol and exponent,
    // see that if the lost part equals or greater than 128,
    // two situations: greater; equal and the last bit of shifted value is 1,
    // both that the shifted value should plus 1
    // Determine if there's a bit 1 in index 23,
    // if so, fraction is 0 and exponent increases by 1
    // Determine the bias
    unsigned exponent_bias = 0;
    if(x)
    {
        exponent_bias = 0x7f;
    }
    // Get the symbol and abs of x
    unsigned symbol = x & 0x80000000;
    unsigned x_absoulte = x;
    if(symbol)
    {
        x_absoulte = ~ x + 1;
    }
    // A while loop to right shift abs x by 1 until the value is 0,
    // record the shifted setps, which is index of top most bit 1
    int index = 0;
    unsigned temp = x_absoulte;
    while(temp)
    {
        temp = temp >> 1;
        index = index + (temp && 0x1);
    }
    // Calculate exponent and left shift setps that could clear left 0 bits
    unsigned exponent = index + exponent_bias;
    int left_shift = 31 + (~ index + 1);
    unsigned fraction = x_absoulte << left_shift;
    // Keep the lost part
    unsigned tail = fraction & 0xff;
    // Leave 9 slots for symbol and exponent
    fraction = (fraction >> 8) & 0x7fffff;
    // Determine if it's necessary to increase fraction by 1
    // If greater than 0.5, increment;
    // equals to 0.5 and the last bit is 1, increment, round up to even
    int tail_7th_bit = tail & 0x80;
    int tail_left_bits = tail & 0x7f;
    int tail_l_128 = tail_7th_bit && tail_left_bits;
    fraction = fraction + (tail_l_128 || (tail_7th_bit && (fraction & 1)));
    // Determine if fraction has a carry after a possible increment
    // if so, fraction is 0 and exponent increases by 1
    if(fraction >> 23)
    {
        fraction = 0;
        exponent = exponent + 1;
    }
    unsigned result = symbol | (exponent << 23) | fraction;
    return result;
}}
