#include <stdio.h>

#define maior_Que_0(value)  (value > 0 ? 1 : 0)
#define mask(value, num, i) if(value & (1<<0)){num = num | 1<<(i); i--;}

int move(int value) {
     int num = 0;
     int i = 31;
     while (maior_Que_0(value))
     {
          mask(value, num, i)
          value = value >> 1;
     }
     return num;
}


int main(){
    int num;
    scanf("%d", &num);
    for(int i = 31 ; i >= 24 ; i--){
        printf("%d", ((move(num)) >> i) & (1 >> 0));
    }
}