#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
    FILE *f;
    f = fopen("fpthihi.txt", "r");
    if(f == NULL){
        printf("Cannot open file !\n");
    }
    else{
        char s[1000];
        fgets(s, 1000, f);
        //Xoa enter
        s[strlen(s) - 1] = '\0';
        printf("Data : %s", s);
        fclose(f);
    }
    return 0;
}
