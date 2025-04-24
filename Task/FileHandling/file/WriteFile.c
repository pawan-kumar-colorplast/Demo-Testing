#include <stdio.h>
int main()
{
    FILE *fp = fopen("write.txt","w");
    if(fp == NULL){
        printf("Error in opening file");
        return 1;
    }

    fprintf(fp,
        "#include <stdio.h>\n"
        "int main()\n"
        "{\n"
        "    printf(\"Hello World\");\n"
        "    return 0;\n"
        "}\n"
    );
    fclose(fp);
    return 0;
}