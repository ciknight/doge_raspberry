#include <wiringPi.h>

int main(void) {
    wiringPiSetup();
    pinMode(4, OUTPUT);
    for (;;)
    {
        digitalWrite (4, HIGH); delay (3000);
        digitalWrite (4,  LOW); delay (500);
    }
    return 0;
}
