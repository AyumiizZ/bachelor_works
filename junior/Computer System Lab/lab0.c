#include<stdio.h>
int bitAnd(int x, int y){

}

int getByte(int x,int n){

}

int logicalShift(int x, int n){

}

int binCount(int x){

}

int odd_ones(unsigned x){

}

int tmin(){

}

int fitBits(int x,int n){

}

int negate(int x){

}

int isPositive(int x){

}

int isLessOrEqual(int x,int y){

}

void print(int predict,int ans){
    if(predict == ans){
        printf("CORRECT: Ans is %d\n",ans);
    }
    else{
        printf("WRONG: Predict is %d Ans is %d\n",predict,ans);
    }
}

int main(){
    print(4,bitAnd(6,5));
    print(0x56,getByte(0x12345678,1));
    print(0x08765432,logicalShift(0x87654321,4));
    print(2,binCount(5));
    print(3,binCount(7));
    print(1,odd_ones(4));
    print(0,odd_ones(0xff000000));
    print(-2147483648,tmin());
    print(0,fitBits(5,3));
    print(1,fitBits(-4,3));
    print(-1,negate(1));
    print(0,isPositive(-1));
    print(1,isLessOrEqual(4,5));
    return 0;
}