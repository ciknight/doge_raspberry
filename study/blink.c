#include <wiringPi.h>

int main(void) {
    wiringPiSetup();
    pinMode(0, OUTPUT);
    for (;;)
    {
        digitalWrite (2, HIGH); delay (200);
        digitalWrite (2,  LOW); delay (200);
    }
    return 0;
}
