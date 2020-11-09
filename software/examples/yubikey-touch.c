#include <stdio.h>
#include <stdlib.h>
#include "littleWire.h"
#include "littleWire_util.h"

#define TOUCH PIN2

unsigned char version;
int total_lwCount;
int i;

int main(int argc, char **argv) {
    littleWire *lw = NULL;
	
    total_lwCount = littlewire_search();

    if (total_lwCount == 1) {
	printf("> 1 Little Wire device is found with serialNumber: %d\n", lwResults[0].serialNumber);
    } else if(total_lwCount > 1) {
	printf("> %d Little Wire devices are found\n", total_lwCount);
	printf("> #id - serialNumber\n");
	for (i = 0; i < total_lwCount; i++) {
	    printf(">  %2d - %3d\n", i, lwResults[i].serialNumber);
	}
    } else if (total_lwCount == 0) {
	printf("> Little Wire could not be found!\n");
	exit(EXIT_FAILURE);
    }	

    /* Connects to the first littleWire device the computer can find. */
    // lw = littleWire_connect();

    /* Connects to the spesific littleWire device by array id. */
    lw = littlewire_connect_byID(0);

    /* Connects to the spesific littleWire with a given serial number. */
    /* If multiple devices have the same serial number, it connects to the last one it finds */
    // lw = littlewire_connect_bySerialNum(126);

    if (lw == NULL) {
	printf("> Little Wire connection problem!\n");
	exit(EXIT_FAILURE);
    }
	
    version = readFirmwareVersion(lw);
    printf("> Little Wire firmware version: %d.%d\n", ((version & 0xF0) >> 4), (version&0x0F));	
    if (version < 0x12) {
	printf("> This example requires the new 1.2 version firmware. Please update soon.\n");
	return 0;
    }	

    /* In order to change the serial number of the current connected device, use the following function. */
    /* You need to unplug-plug to see the change. */
    /* Serial numbers have to be between 100-999 */
    // changeSerialNumber(lw,152);

    if (argc == 0) {
        return 0;
    }

    pinMode(lw, TOUCH, INPUT);
    digitalWrite(lw, TOUCH, LOW);
    pinMode(lw, TOUCH, OUTPUT);
    delay(atoi(argv[1]));
    pinMode(lw, TOUCH, INPUT);
	
    if (lwStatus < 0) {
	printf("> lwStatus: %d\n", lwStatus);
	printf("> Connection error: %s\n", littleWire_errorName());
	return 0;
    }
    return 0;
}
