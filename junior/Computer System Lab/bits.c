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
    return 0;
}