#include <stdio.h>
int main()
{
    FILE* ptr = fopen("test.txt","r");
    char str[100];

    while(fgets(str,100,ptr) != NULL){
        printf("%s",str);
    }
    return 0;
}