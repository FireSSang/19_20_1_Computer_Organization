#include <iostream>
using namespace std;

unsigned srl(unsigned x,int k) {
    /*Perform shift arithmetically*/
    unsigned xsra = (int) x >> k;

    int w = 8 * sizeof(int);
    int mask = (1 << (w - k)) - 1; //前k位为0，后w-k位为1
    return xsra & mask; //前k位置为0，后k位不变
}

int sra(int x, int k) {
    /*Perform shift logically*/
    int xsrl = (unsigned) x >> k;

    int w = 8 * sizeof(int);
    int sign_mask = xsrl & (1 << (w - k - 1)); //若符号位为0，该值为0
    //否则为000...001000...000形式
    int mask = ~((sign_mask << 1) - 1);
    //如果符号位为1，mask为111...1100000...000000
    //如果符号位为0，mask为000...0000000...000000
    return xsrl | mask; //前k为改为mask前k位，实现符号位扩展
}

int main()
{
    int date = 19200000 + 60817; //一个比较大的常用素数
    cout << (date >> 7) << endl;
    cout << srl(date, 7) << endl;
    cout << sra(date, 7) << endl;

    int datee = -1 * date;
    cout << (datee >> 7) << endl;
    cout << srl(datee, 7) << endl;
    cout << sra(datee, 7) << endl;

    return 0;
}