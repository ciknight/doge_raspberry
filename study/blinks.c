#include <wiringPi.h>
#include <stdio.h>

int main(void) {
    wiringPiSetup();
    
    int i = 0;
    
    for(i=0; i<8; i++){
        pinMode(i, OUTPUT);
    }
    for(;;){
        for(i=0; i<8; i++){
            printf("this is mode %d\n", i);
            digitalWrite (i, HIGH); delay (100);
            digitalWrite (i,  LOW); delay (100);
        }
    }
    return 0;
}
