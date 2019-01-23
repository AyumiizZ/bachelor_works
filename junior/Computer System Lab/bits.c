#include<stdio.h>
int bitAnd(int x, int y){
    /*
     * ใช้คุณสมบัติของ ~(~p or ~q) สมมูลกับ p and q
     */
    return ~(~x|~y);
}

int getByte(int x,int n){
    /*
     *  n << 3 เพื่อเปลี่ยนค่าจาก byte เป็น bits (1 byte = 8 bits และ << 3 มีค่าเท่ากับ * 8)
     *  x >> (n << 3) เพื่อ shift ให้ 8 bits ที่ต้องการไปอยู่ในตำแหน่งของ 8 bits ทางด้านขวาสุด
     *  x >> (n << 3) & 255 เพื่อที่จะตัด bits ทั้งหมดทิ้งให้หมด เหลือไว้แค่ 8 bits ที่ซ็ายที่สุด
     */
    return x >> (n << 3) & 255;
}

int logicalShift(int x, int n){
    /*
     * (1 << 31) จะทำให้เกิด ค่า 10000...000 
     * ซึ่งเมื่อ right shift (1 << 31) >> (n - 1) จะได้ 111...110000...000 โดยเราจะได้ 1 เป็นจำนวนทั้งสิ้น n-1 ตัว
     * แล้วเรานำมา invert เพื่อที่จะได้เป็น mask แบบ 000...000111...111 เพื่อที่จะนำมา and กับค่าที่ shift แล้ว
     * ติด 1 ที่มาจากการ shift แบบ arithmetic shift ให้ตัวที่เป็น 1 ข้างหน้าหายไป 
     */
    return (x >> n) & ~((1 << 31) >> (n - 1));
}

int binCount(int x){
    /*
     * เนื่องจากการที่เราจะทำ count += x & 1 แล้ว x = x >> 1 เพื่อนับทีละตัวจนครบ มันทำให้
     * operation ที่ต้องใช้มันเยอะเกิน (โจทย์กำหนดไว้ว่าห้ามเกิน 40 operation ซึ่งถ้าทำข้างต้นต้องใช้อย่างน้อย 3 * 31 ครั้ง ซึ่งมันเกิน 40)
     * ดังนั้นเราจึงทำการ mask ทุก ๆ 8 bit (ถ้าถามว่าทำไมถึงเป็น 8 เพราะว่า 32 หาร 8 ลงตัว ซึ่งตอนแรกมีทางเลือกคือ 4 กับ 8
     * ผมจึงเลือก 8 เพราะว่าจากข้างล่างจะใช้ operation เป็น 4+8+4 แต่ถ้าเลือก 4 จะเป็น 8+4+8 ซึ่งคาดว่าเยอะกว่า 
     * แต่ผมไม่ได้ลองทำและนับจริงครับ จึงตอบไม่ได้ว่าใช้ไปกี่ operation ในแบบที่เลือก 4)
     * mask คือ 1 ทุกๆตัวที่ 0,8,16,24 เพื่อที่จะลด operation ในการนับเลข 1
     * c คือ count ซึ่งคือการบวกเลข 1 ใน 8 bit ซึ่งค่าจะได้เท่ากับการนับที่ bit ที่ 24-31 แล้วนำค่ามาไว้ที่ 24, bit ที่ 16-23 แล้วนำค่ามาไว้ที่ 16
     * bit ที่ 8-15 แล้วนำค่ามาไว้ที่ 8, bit ที่ 0-7 แล้วนำค่ามาไว้ที่ 0
     * จาก count เราจึงนับค่าที่ได้จากการนับมา shift แล้วบวกกัน เพื่อนำค่ามารวมกันและเก็บที่ bit ที่ 0
     * หลังจากนั้นเราจะทำการตัดเอาแค่ผลจาก 8 bit ซ้ายสุดเพื่อออกเป็นผลลัพท์ที่ต้องการ
     * (ถ้าไม่ตัดออกจะทำให้มีค่าขยะที่เกิดจากการนับ เช่นค่า c ที่ไม่ได้ shift จะมีค่าอื่นที่นับไว้อยู่ใน bit อื่น ดังนั้นเราต้องตัดขยะทิ้งไป)
     */
    int mask = 1 | 1 << 8 | 1 << 16 | 1 << 24;
    int c = (x & mask) + ((x >> 1) & mask) + ((x >> 2) & mask) + ((x >> 3) & mask) + ((x >> 4) & mask) + ((x >> 5) & mask) + ((x >> 6) & mask) + ((x >> 7) & mask);
    return (c + (c >> 8) + (c >> 16) + (c >> 24)) & 0xFF;
}

int odd_ones(unsigned x){
    /*
     *
     */
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    return x & 1;
}

int tmin(){
    /*
     *
     */
    return 1 << 31;
}

int fitBits(int x,int n){
    /*
     *
     */
    int check = 1 & ~((x >> n) ^ (x >> (n-1)));
    x = x >> n;
	return check & (!x || !(~x)) & ~!n;
}

int negate(int x){
    /*
     *
     */
    return ~x + 1;
}

int isPositive(int x){
    /*
     *
     */
    return !(x>>31 & 1) ;
}

int isLessOrEqual(int x,int y){
    /*
     *
     */
    return !(((y-x) >> 31) & 1);
}

void print(int predict,int ans){
    /*
     *
     */
    if(predict == ans){
        printf("CORRECT: Ans is %d\n",ans);
    }
    else{
        printf("WRONG: Predict is %d Ans is %d\n",predict,ans);
    }
}

void printhex(int predict,int ans){
    /*
     *
     */
    if(predict == ans){
        printf("CORRECT: Ans is 0x%x\n",ans);
    }
    else{
        printf("WRONG: Predict is 0x%x Ans is 0x%x\n",predict,ans);
    }
}

int main(){

    /*
     * bitAnd 
     * ทดสอบโดยเน้นหลัก 0 and อะไรก็ได้ 0 และ 1 and อะไรก็ได้ตัวนั้น
     */

    print(bitAnd(0xffffffff,0),0); // ทดสอบ 1111...111 and 0000...000 (ทดสอบทุกบิตเป็น 1 แล้ว and 0 ควรได้ 0)
    print(bitAnd(0,0xffffffff),0); // เหมือนเคสแรก แต่ทดสอบสลับ parameter
    print(bitAnd(0xaaaaaaa,0x11111111),0); // ทดสอบ 1010...010 and 0101...101 (ทดสอบ)
    printhex(bitAnd(0xffffffff,0x192702db),0x192702db);  // ทดสอบ 1111...111 and 1010...010 (ทดสอบว่า 1 ทุกตัว and อะไรควรได้ตัวนั้น โดยทดสอบด้วยการสุ่มค่ามา)
    printhex(bitAnd(0x451809c5,0xffffffff),0x451809c5);  // ทดสอบเหมือนเคสสี่ แต่สลับ parameter
    print(bitAnd(0,0),0); // ทดสอบ 0 and 0 (ทดสอบเคสสามัญที่ควรจะต้องถูก)

    printf("\n");
    /*
     * getByte 
     * เนื่องจากใช้ 0xffffffff 0xaaaaaaaa หรือ 0 มาทดสอบจะลำบากเพราะว่า byte มีค่าเหมือนกัน ทำให้ตอบยากว่าถูกหรือไม่
     * ดังนั้นจะใช้เลขสุ่มที่ไม่มีค่าใน byte ไหนเหมือนกันเลย แล้วคำตอบควรจะได้ค่าจาก byte นั้นจริงๆ
     */
    printhex(getByte(0x22cfdd5c,0),0x5c); // สี่เคสแรกจะเป็นการนำเลขสุ่ม 1 ตัวมาทดสอบทุก byte ว่าตรงไหม
    printhex(getByte(0x22cfdd5c,1),0xdd);
    printhex(getByte(0x22cfdd5c,2),0xcf);
    printhex(getByte(0x22cfdd5c,3),0x22);
    printhex(getByte(0x401c52f4,0),0xf4); // สองเทสเคสท้าย จะเป็นการนำเลขสุ่มมาดู byte ที่ 0 กับ byte ที่ไม่ใช่ 0 อย่างละหนึ่งเคส
    printhex(getByte(0x765ce811,3),0x76);

    printf("\n");
    /*
     * logicalShift
     * ใช้ค่าบวกเทสในสามเทสเคสแรกเพื่อทดสอบว่า shift ถูก (ค่าไม่ควรจะมี 1 เพื่มจากทางซ้าย)
     * และใช้ค่าลบเทสในสามเทสเคสท้ายเพื่อทดสอบว่า shift ถูก (เหมือนกับค่าบวก คือ ค่าไม่ควรจะมี 1 เพิ่มจากทางซ้าย)
     * ทั้งนี้ ผมได้ใช้ตัว python2.7 ช่วยในการสร้างและเช็คเทสเคส ( >> ใน python2.7 เป็น logical shift ซึ่งไม่เหมือนใน c)
     */ 
    printhex(logicalShift(0x8765abcd, 4),0x8765abc);
    printhex(logicalShift(0x8765abcd, 5),0x43b2d5e);
    printhex(logicalShift(0x8765abcd, 6),0x21d96af);
    printhex(logicalShift(0xabcd5678, 7),0x1579aac);
    printhex(logicalShift(0xabcd5678, 8),0xabcd56);
    printhex(logicalShift(0xabcd5678, 9),0x55e6ab);

    printf("\n");
    /*
     * binCount
     */


    return 0;
}