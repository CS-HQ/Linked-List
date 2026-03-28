#include<stdio.h>

void convert_binary(int value){
    for(int i=31; i>=0;i--){
        int bit=(value>>i) & 1;
        printf("%d", bit);
        if(i%8==0) printf(" ");
    }
    printf("\n");
}

int main(){
    int integer;
    printf(" Enter INT Value: ");
    scanf("%d", &integer);
    convert_binary(integer);
    return 0;
}