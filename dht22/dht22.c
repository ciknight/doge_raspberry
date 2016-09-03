#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>


#define MAXTIMINGS 85
static int dht22_dat[5] = {0,0,0,0,0};

static uint8_t sizecvt(const int read)
{
    /* digitalRead() and friends from wiringpi are defined as returning a value
       < 256. However, they are returned as int() types. This is a safety function */

    if (read > 255 || read < 0)
    {
        printf("Invalid data from wiringPi library\n");
        exit(EXIT_FAILURE);
    }
    return (uint8_t)read;
}

static int read_dht22_dat(int iPin, int* piHumidity, int* piTemp)
{
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    dht22_dat[0] = dht22_dat[1] = dht22_dat[2] = dht22_dat[3] = dht22_dat[4] = 0;

    // pull pin down for 18 milliseconds
    pinMode(iPin, OUTPUT);
    digitalWrite(iPin, LOW);
    delay(18);

    // then pull it up for 40 microseconds
    digitalWrite(iPin, HIGH);
    delayMicroseconds(40);

	// prepare to read the pin
    pinMode(iPin, INPUT);

    // detect change and read data
    for ( i=0; i< MAXTIMINGS; i++)
	{
        counter = 0;
        while (sizecvt(digitalRead(iPin)) == laststate)
		{
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
			{
                break;
            }
        }
        laststate = sizecvt(digitalRead(iPin));

        if (counter == 255) break;

        // ignore first 3 transitions
        if ((i >= 4) && (i%2 == 0))
		{
            // shove each bit into the storage bytes
            dht22_dat[j/8] <<= 1;
            if (counter > 16)
                dht22_dat[j/8] |= 1;
            j++;
        }
    }

    // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
    // print it out if data is good
    if ((j >= 40) && (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF)) )
	{
		*piHumidity = dht22_dat[0] * 256 + dht22_dat[1];
		*piTemp = (dht22_dat[2] & 0x7F)* 256 + dht22_dat[3];
        if ((dht22_dat[2] & 0x80) != 0)
			*piTemp *= -1;

		return 1;
    }
    else
    {
        return 0;
    }
}

int main( int argc, char * argv[])
{
    int iPin = 7;
    int iErr = 0;

	iErr = wiringPiSetup ();
    if (iErr == -1)
        exit(1);

	int iHumidity = -1;
	int iTemp = -1;

    while(1)
    {
        if (read_dht22_dat(iPin, &iHumidity, &iTemp) == 1)
            printf("    Humidity = %.2f %% Temperature = %.2f *C \n", (float)(iHumidity/10.0), (float)(iTemp/10.0) );
        delay(2000);
    }
}
