#include <stdio.h>
#include <wiringPi.h>

int main(void) {
    wiringPiSetup();
    pinMode(2, OUTPUT);
    for (;;)
    {
        digitalWrite (2, HIGH); delay (500);
        digitalWrite (2,  LOW); delay (500);
    }
    return 0;
}
