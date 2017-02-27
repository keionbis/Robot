#ifndef ENCODER_TRANSMISSION_H
#define ENCODER_TRANSMISSION_H

#define SLAVE_ADDRESS 0x60
#define SLAVE_ADDRESS_2 0x70

void Read_Encoder_Ticks();
extern int ticks_Right, ticks_Left;
#define Turn_Ticks 6021

#endif
