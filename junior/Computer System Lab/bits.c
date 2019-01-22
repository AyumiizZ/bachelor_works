#include<stdio.h>
int bitAnd(int x, int y){
    return ~(~x|~y);
}

int getByte(int x,int n){
    return x >> (n << 3) & 255;
}

int logicalShift(int x, int n){
    return (x >> n) & ~((1 << 31) >> (n - 1));
}

int binCount(int x){
    int mask = 1 | 1 << 8 | 1 << 16 | 1 << 24;
    int c = (x & mask) + ((x >> 1) & mask) + ((x >> 2) & mask) + ((x >> 3) & mask) + ((x >> 4) & mask) + ((x >> 5) & mask) + ((x >> 6) & mask) + ((x >> 7) & mask);
    return (c + (c >> 8) + (c >> 16) + (c >> 24)) & 0xFF;
}

int odd_ones(unsigned x){
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    return x & 1;
}

int tmin(){
    return 1 << 31;
}

int fitBits(int x,int n){
    int check = 1 & ~((x >> n) ^ (x >> (n-1)));
    x = x >> n;
	return check & (!x || !(~x)) & ~!n;
}

int negate(int x){
    return ~x + 1;
}

int isPositive(int x){
    return !(x>>31 & 1) ;
}

int isLessOrEqual(int x,int y){
    return !(((y-x) >> 31) & 1);
}

void print(int predict,int ans){
    if(predict == ans){
        printf("CORRECT: Ans is %d\n",ans);
    }
    else{
        printf("WRONG: Predict is %d Ans is %d\n",predict,ans);
    }
}

void printhex(int predict,int ans){
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
    print(getByte(0x22cfdd5c,0),0x5c); // สี่เคสแรกจะเป็นการนำเลขสุ่ม 1 ตัวมาทดสอบทุก byte ว่าตรงไหม
    print(getByte(0x22cfdd5c,1),0xdd);
    print(getByte(0x22cfdd5c,2),0xcf);
    print(getByte(0x22cfdd5c,3),0x22);
    print(getByte(0x401c52f4,0),0xf4); // สองเทสเคสท้าย จะเป็นการนำเลขสุ่มมาดู byte ที่ 0 กับ byte ที่ไม่ใช่ 0 อย่างละหนึ่งเคส
    print(getByte(0x765ce811,3),0x76);

    printf("\n");
    /*
     *
     * 
     */ 
    



    return 0;
}