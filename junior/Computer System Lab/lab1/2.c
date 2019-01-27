// C Program for counting sort
#include <stdio.h>
#include <string.h>
#define RANGE 255
#define N 1000
int main()
{
    char str[] = "cadljgarhtoxAHdgdsJKhYEasduwBRLsdgHoptxnaseurh";
    char output[N];
    int count[RANGE + 1], i;
    for (i = 0; i < RANGE + 1; i++)
        count[i] = 0;
    for (i = 0; str[i]; ++i)
        ++count[str[i]];
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
    for (i = 0; str[i]; ++i)
    {
        output[count[str[i]] - 1] = str[i];
        --count[str[i]];
    }
    for (i = 0; str[i]; ++i)
        str[i] = output[i];
    printf("Sorted string is %s\n", str);
    return 0;
}