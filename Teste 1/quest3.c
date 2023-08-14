#include <stdio.h>

#define bool int
#define TRUE 1
#define FALSE 0
#define true TRUE
#define false FALSE

#define TESTE(w) (w == 1 ? 1 : 0)
#define contar1(count, value) if((value & 0x1) == 1){count++;}
#define contar0(count, value) if((value & 0x1) == 0){count++;}


int coutBits(bool w, unsigned int value){
    int count1 = 0;
    int count0 = 0;
    for(int i = 0; i < 32; i++){
        if(TESTE(w)){
            contar1(count1, value);
            value = value >> 1;
        }else{
            contar0(count0, value);
            value = value >> 1;
        }
    }
    

    if (TESTE(w)){
        return count1;
    }else{
        return count0;
    }
    
}

int main(){
    unsigned int value;
    int w;
    scanf("%d", &w);
    scanf("%d", &value);
    printf("%d\n", coutBits(w , value));
    return 0;
}


