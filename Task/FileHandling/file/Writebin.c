#include <stdio.h>

typedef struct {
    char name[100];
    char dep[100];
    int id;
} Student;

int main()
{
   
   Student st = {
    "Pawan",
    "OS Department",
    1433
   };

   FILE *fp = fopen("pawan.bin","wb"); // Write Binary

   if(fp == NULL) {
    printf("Error file not found");
    return 1;
   }

   fwrite(&st, sizeof(Student), 1, fp);
//    fwrite(&s1, sizeof(Student), 1, fp);

   fclose(fp);

//    printf("completed");
   printf("Data written successfully.\n");


    return 0;
}