#include <wiringPi.h>

int main(void) {
    wiringPiSetup();
    pinMode(0, OUTPUT);
    for (;;)
    {
        digitalWrite (0, HIGH); delay (200);
        digitalWrite (0,  LOW); delay (200);
    }
    return 0;
}
