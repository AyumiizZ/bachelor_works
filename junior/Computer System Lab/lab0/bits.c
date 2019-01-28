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
     *  ขั้นแรกเราก็นำ x = x ^ (x >> 16)
     *  ให้คิดว่าเหมือนพับกระดาษครึ่งหนึ่ง คือเรานำ x 16 ตัวแรกกับ 16 ตัวท้ายมา xor ซึ่งเมื่อ 1 xor 1 จะได้ 0
     *  ก็ให้คิดเหมือนว่าเราตัดตัวที่ซ้ำไป ดังนั้น 1 ที่เหลืออยู่ใน 16 bit ท้ายจะเป็น 1 ที่ไม่มีคู่
     *  ดังนั้นเราจึงพับครึ่งเป็น 8 กับ 8 และเหมือน 16 ดังนั้นจะได้ตัวที่ไม่มีคู่เหลือที่ 8 bit ท้าย
     *  ทำเรื่อยๆจนเหลือเป็น ครึ่งที่พับ 1 กับ 1 เข้าด้วยกัน
     *  ดังนั้นถ้า bit หนึ่งเป็นเลขคี่ จะทำให้ bit สุดท้ายจะเป็น 1 เพราะพับแล้วไม่มีคู่ (1 xor 0 == 1 หรือ 0 xor 1 == 1)
     *  ดังนั้นเมื่อเราตัดมาแค่ bit ท้ายสุด เราจะได้ว่า x ของเรามี bit 1 เป็นจำนวนคู่หรือคี่
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
     * ค่าลบที่น้อยที่สุดเมื่อเขียนแล้วจะเป็น 100...000 ซึ่งก็คือ 1 << 31
     */
    return 1 << 31;
}

int fitBits(int x,int n){
    /*
     * shift = 32 - n เพื่อที่จะ shift เลขไปให้สุดขอบของ 32-bit integer
     * แล้วเมื่อ shift กลับมาแล้วจะต้องไม่มีตัวไหนเปลี่ยนค่า ดังนั้นเราจึงนำมา xor 
     * และผลลัพธ์ที่หวังไว้ก็ควรจะ xor กันแล้วได้ 0 (x ^ ((x << shift) >> shift))
     * ซึ่งเราต้องการแสดงออกเป็น 1 ดังนั้นเราจึงทำการ !
     * แต่การทำเช่นนี้จะมีช่องโหว่คือ 0
     * ดังนั้นเราจึงทำการ !!n ซึ่งเมื่อไม่เป็น 0 -> !!n = 1 แต่ถ้าเป็น 0 -> !!n = 0
     */
    int shift = 32 - n;
    return !(x ^ ((x << shift) >> shift)) & !!n;
}

int negate(int x){
    /*
     * เนื่องจาก c เก็บค่าด้วยระบบ 2' complement ดังนั้นจะส่งค่าตรงข้ามก็แค่ทำ 2' complement
     */
    return ~x + 1;
}

int isPositive(int x){
    /*
     * (x>>31) ทำเพื่อจะเช็คว่า bit ที่ 31 เป็น 1 หรือ 0 ซึ่งเรานำมา & x เพื่มเพื่อกันเคสที่ x เป็น 0
     * แต่ด้วยความที่ว่าถ้าเป็น positive จะ return 1 แต่ผลลัพธ์จากบรรทัดแรกเป็น 0
     * และ negative จะ return 0 แต่ผลลัพธ์จากบรรทัดแรกเป็น อะไรก็ได้ที่ไม่ใช่ 0
     * ซึ่งพบว่าได้ค่าตรงข้ามกับผลลัพธ์ที่ต้องการ
     * ดังนั้นเราจึงทำการ invert ก่อนที่จะ return
     */
    return !(x>>31) & x;
}

int isLessOrEqual(int x,int y){
    /*
     * อันนี้คล้ายๆ isPositive โดยการเช็คว่า y-x เป็นลบหรือบวก
     * จาก ((y-x) >> 31) จะได้ว่า
     * เมื่อ y > x แล้ว bit ขวาสุดจะเป็น 0
     * เมื่อ y = x แล้ว bit ขวาสุดจะเป็น 0
     * เมื่อ y < x แล้ว bit ขวาสุดจะเป็น 1 (y-x แล้วติดลบ)
     * ดังนั้นเมื่อ y น้อยกว่าหรือเท่ากับ x จะได้ผลลัพธ์คือ 0
     * แล้วเมื่อ y มากกว่า x จะได้ผลลัพธ์คือ 1
     * ซึ่งพบว่าได้ค่าตรงข้ามกับผลลัพธ์ที่ต้องการ
     * ดังนั้นเราจึงทำการ invert ก่อนที่จะ return
     */
    return !(((y-x) >> 31) & 1);
}

void print(int ans,int predict){
    /*
     * อันนี้เป็นการพิมพ์เพื่อเช็คว่าคำตอบตรงกับ predict ไหม โดยมี format เป็น int
     */
    if(predict == ans){
        printf("CORRECT: Ans is %d\n",ans);
    }
    else{
        printf("WRONG: Predict is %d Ans is %d\n",predict,ans);
    }
}

void printhex(int ans,int predict){
    /*
     * อันนี้เป็นการพิมพ์เพื่อเช็คว่าคำตอบตรงกับ predict ไหม โดยมี format เป็น hex
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
     * ข้อนี้ทำการทดสอบด้วยการเทสทุก bit เป็น 0 และทุก bit เป็น 1 (ในสองเคสแรก)
     * ส่วนที่เหลือใช้วิธีการสุ่มเลข แล้วนำมานับมือเทียบว่าตรงกับที่ได้ไหม
     */
    print(binCount(0),0);
    print(binCount(0xffffffff),32);
    print(binCount(0xa01c465f),14);
    print(binCount(0xd2ee5670),17);
    print(binCount(0xafdce39d),21);
    print(binCount(0xbf4097a7),18);

    printf("\n");

    /*
     * odd_ones
     * ข้อนี้เนื่องจากว่าการทดสอบให้ครอบคลุมทำได้ยาก
     * ดังนั้นผมเลยใช้วิธีการสุ่มเลข โดยที่สุ่มมือเป็นเลขฐาน 2 (แต่เขียนแล้วมันยาวเลยแปลงเป็นฐาน16)
     * ซึ่งการสุ่มจะแบ่งเป็นเลข 1 เป็นจำนวนคี่ 3 ชุด และคู่ 3 ชุด
     */

    print(odd_ones(0),0);
    print(odd_ones(0xa1489133),0);
    print(odd_ones(0xe9b9f2b6),0);
    print(odd_ones(0xfffffffe),1);
    print(odd_ones(0x5cd079dc),1);
    print(odd_ones(0xec54fc68),1);

    printf("\n");
    /*
     * tmin
     * ฟังก์ชั่นนี้ไม่มี parameter ดังนั้นจะใช้วิธีเทส 6 รอบ ควรได้ค่าที่ถูกต้องทุกครั้ง (โจทย์สั่งให้มีเทสเคส 6 เคส)
     */
    print(tmin(),-2147483648);
    print(tmin(),-2147483648);
    print(tmin(),-2147483648);
    print(tmin(),-2147483648);
    print(tmin(),-2147483648);
    print(tmin(),-2147483648);

    printf("\n");

    /*
     * fitBits
     * ข้อนี้เราจะทดสอบตามขอบๆของจำนวน bits ต่างๆ ซึ่งในที่นี้จะยกเป็น 16
     * และทดสอบที่ 0 bit จะต้องเก็บอะไรไม่ได้เลยไม่เว้นแต่ 0
     */
    print(fitBits(32767,16),1);
    print(fitBits(32768,16),0);
    print(fitBits(-32768,16),1);
    print(fitBits(-32769,16),0);
    print(fitBits(0,0),0);
    print(fitBits(-1,0),0);

    printf("\n");

    /*
     * negate
     * เราจะทดสอบจากค่าสุ่ม 3 ชุดโดยที่เป็นค่าตรงข้ามกัน ซึ่งเมื่อทำแล้วควรได้คำตอบที่ตรงกับเลขตรงข้าม
     * และทดสอบกับเลข 0 ที่เมื่อเราทำการ negate แล้วควรเป็นค่าเดิม
     */
    print(negate(0),0);
    print(negate(-25),25);
    print(negate(25),-25);
    print(negate(-69),69);
    print(negate(2147483647),-2147483647);
    print(negate(-2147483647),2147483647);
    

    printf("\n");

    /*
     * isPositive
     * ทดสอบด้วยค่าบวก 3 ชุด 0 1 ชุด และค่าลบ 2 ชุด 
     */
    print(isPositive(0),0);
    print(isPositive(1),1);
    print(isPositive(0xffffffff),0);
    print(isPositive(0x7fffffff),1);
    print(isPositive(-1),0);
    print(isPositive(0xa0a0a0a0),0);

    printf("\n");

    /*
     * isLessOrEqual 
     * ทดสอบด้วยวิธีสุ่มชุดตัวเลขซึ่งประกอบด้วย
     * น้อยกว่า 2 ชุด
     * เท่ากับ 2 ชุด
     * และมากกว่า 2 ชุ
     */
    print(isLessOrEqual(0x7a62e179,0x7ff78f8f),1);
    print(isLessOrEqual(0xda5fdfd7,0x3febdac5),1);
    print(isLessOrEqual(0,0),1);
    print(isLessOrEqual(0x4eb9b28e,0x4eb9b28e),1);
    print(isLessOrEqual(0x44e1397f,0xfc559b96),0);
    print(isLessOrEqual(0x6b653d6a,0xf7f008c),0);

    return 0;
}