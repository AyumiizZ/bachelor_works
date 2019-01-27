// C Program for counting sort
#include <stdio.h>
#define RANGE 255
int main()
{
    char str[] = "cadljgarhtoxAHdgdsJKhYEasduwBRLsdgHoptxnaseurh";
    char output[1000];
    int count[RANGE + 1];

    int t0; // t0 = i

    int t1;
    int t2;
    int t3;

    initLoop1:
        t0 = 0;
    Loop1:
        if(t0 > RANGE)
            goto initLoop2;
        count[t0] = 0;
        t0 = t0 + 1;
        goto Loop1;

    initLoop2:
        t0 = 0;
    Loop2:
        if(str[t0] == 0)
            goto initLoop3;
        t1 = str[t0];
        count[t1] += 1;
        t0 = t0 + 1;
        goto Loop2;

    initLoop3:
        t0 = 1;
    Loop3:
        if(t0 > RANGE)
            goto initLoop4;
        t2 = t0 - 1;
        t1 = count[t2];
        count[t0] = count[t0] + t1;
        t0 = t0 + 1;
        goto Loop3;

    initLoop4:
        t0 = 0;
    Loop4:
        if(str[t0] == 0)
            goto initLoop5;
        t1 = str[t0];
        t2 = count[t1];
        t3 = t2 - 1;
        output[t3] = t1;
        count[t1] = count[t1] - 1;
        t0 = t0 + 1;
        goto Loop4;

    initLoop5:
        t0 = 0;
    Loop5:
        if(str[t0] == 0)
            goto printRes;
        t1 = output[t0];
        str[t0] = t1;
        t0 = t0 + 1;
        goto Loop5;


    printRes:
        printf("Sorted string is ");
        printf("%s",str);
        printf("\n");
    return 0;
}