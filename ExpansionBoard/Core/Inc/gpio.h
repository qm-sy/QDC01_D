/*
|P0^0|RX3       |P1^0|level3_H  |P2^0|DC24_1     |P3^0|RX1       |P4^0|level5_H   |P5^0|level7_H     
|P0^1|TX3       |P1^1|Temp_Hum  |P2^1|DC24_2     |P3^1|TX1       |P4^1|level10_L  |P5^1|level8_L     
|P0^2|RX4       |P1^2|          |P2^2|PWM1       |P3^2|level6_L  |P4^2|level10_H  |P5^2|level1_L     
|P0^3|TX4       |P1^3|level4_H  |P2^3|PWM2       |P3^3|level6_H  |P4^3|level11_L  |P5^3|level1_H     
|P0^4|DR4       |P1^4|NTC1      |P2^4|level12_L  |P3^4|level7_L  |P4^4|level11_H  |P5^4|level5_L
|P0^5|level2_L  |P1^5|NTC2      |P2^5|level12_H  |P3^5|level8_H  |P4^5|level14_L  |P5^5|             
|P0^6|level2_H  |P1^6|NTC3      |P2^6|level13_L  |P3^6|level9_L  |P4^6|level14_H  |P5^6|     
|P0^7|level3_L  |P1^7|level4_L  |P2^7|level13_H  |P3^7|level9_H  |P4^7|DC24_3     |P5^7|     
*/ 
#ifndef _GPIO_H_
#define _GPIO_H_

#include "sys.h"

sbit RX3            = P0^0;
sbit TX3            = P0^1;
sbit RX4            = P0^2;
sbit TX4            = P0^3;
sbit DR4            = P0^4;
sbit level2_L       = P0^5;
sbit level2_H       = P0^6;
sbit level3_L       = P0^7;

sbit level3_H       = P1^0;
sbit Temp_Hum       = P1^1;
sbit level4_H       = P1^3;
sbit NTC1           = P1^4;
sbit NTC2           = P1^5;
sbit NTC3           = P1^6;
sbit level4_L       = P1^7;

sbit DC24_1         = P2^0;
sbit DC24_2         = P2^1;
sbit DC_PWM1           = P2^2;
sbit DC_PWM2           = P2^3;
sbit level12_L      = P2^4;
sbit level12_H      = P2^5;
sbit level13_L      = P2^6;
sbit level13_H      = P2^7;

sbit RX1            = P3^0;
sbit TX1            = P3^1;
sbit level6_L       = P3^2;
sbit level6_H       = P3^3;
sbit level7_L       = P3^4;
sbit level8_H       = P3^5;
sbit level9_L       = P3^6;
sbit level9_H       = P3^7;

sbit level5_H       = P4^0;
sbit level10_L      = P4^1;
sbit level10_H      = P4^2;
sbit level11_L      = P4^3;
sbit level11_H      = P4^4;
sbit level14_L      = P4^5;
sbit level14_H      = P4^6;
sbit DC24_3         = P4^7;

sbit level7_H       = P5^0;
sbit level8_L       = P5^1;
sbit level1_L       = P5^2;
sbit level1_H       = P5^3;
sbit level5_L       = P5^4;


void GPIO_Init( void );

#endif