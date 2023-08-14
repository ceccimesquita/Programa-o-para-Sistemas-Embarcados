#include <stdio.h>

#define gpio_enabled (1 << 0)
#define gpio_direction (1 << 1)
#define gpio_level (1 << 2)
#define gpio_reset (1 << 3)

int abilitado(char* gpioREG){
    return *gpioREG | gpio_enabled; //item a
}

int teste_saida(char gpioREG){                 //item b
    if(gpioREG & gpio_direction){
        return gpioREG & ~(gpio_enabled);
    }else{
        return gpioREG;
    }
}

int setInput(char gpioREG){
    return gpioREG | gpio_direction; //item c
}

int setContrario(char gpioREG){
    return gpioREG ^ gpio_level; //item d
}


int main(){
    unsigned char gpioREG;
    scanf("%hhu", &gpioREG);

    printf("%hhu\n", abilitado(&gpioREG));
    printf("%hhu\n", teste_saida(gpioREG));
    printf("%hhu\n", setInput(gpioREG));
    printf("%hhu\n", setContrario(gpioREG));
}