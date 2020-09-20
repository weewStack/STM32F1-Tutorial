#include "i2c_drive.h"
#include "systick_time.h"

#define ACK 0
#define NACK 1

#define Yaw 0
#define Roll 1
#define Pitch 2

void bno55_init(char i2c);
void bno055_eul(char i2c,short * angle);
