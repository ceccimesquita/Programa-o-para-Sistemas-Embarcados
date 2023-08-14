#include <stdio.h>

#define bool int
#define TRUE 1
#define FALSE 0
#define true TRUE
#define false FALSE

#define TESTE(w) (w == 1 ? 1 : 0)
#define setbit1(value, k) value = value | (0x1 << k);
#define setbit0(value, k) value = value & ~(0x1 << k);

void setBits(bool w, unsigned int i, unsigned int j, unsigned int value){
    for(int k = i; k <= j; k++){     
        if(TESTE(w)){                  
            setbit1(value, k);
        }else{
            setbit0(value, k);
        }
    }
    printf("%d", value);
}


int main(){
    int i;
    int j;
    int value;
    int w;
    scanf("%d %d %d %d", &w, &i, &j, &value);
    setBits(w, i, j, value);
    
}