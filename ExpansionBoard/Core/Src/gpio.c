/*
|P0^0|RX3       |P1^0|level3_H  |P2^0|DC24_1     |P3^0|RX1       |P4^0|level5_H   |P5^0|level7_H     
|P0^1|TX3       |P1^1|T_H       |P2^1|DC24_2     |P3^1|TX1       |P4^1|level10_L  |P5^1|level8_L     
|P0^2|RX4       |P1^2|          |P2^2|PWM1       |P3^2|level6_L  |P4^2|level10_H  |P5^2|level1_L     
|P0^3|TX4       |P1^3|level4_H  |P2^3|PWM2       |P3^3|level6_H  |P4^3|level11_L  |P5^3|level1_H     
|P0^4|DR4       |P1^4|NTC1      |P2^4|level12_L  |P3^4|level7_L  |P4^4|level11_H  |P5^4|level5_L
|P0^5|level2_L  |P1^5|NTC2      |P2^5|level12_H  |P3^5|level8_H  |P4^5|level14_L  |P5^5|             
|P0^6|level2_H  |P1^6|NTC3      |P2^6|level13_L  |P3^6|level9_L  |P4^6|level14_H  |P5^6|     
|P0^7|level3_L  |P1^7|level4_L  |P2^7|level13_H  |P3^7|level9_H  |P4^7|DC24_3     |P5^7|     
*/ 
#include "gpio.h"

/**
 * @brief	GPIO初始化
 *
 * @param   void
 *
 * @return  void
 */
void GPIO_Init( void )
{
    P0M0 = 0x1A;    P0M1 = 0x00;        //P0.1、P0.3、P0.4为推挽输出
    P0PU = 0xE0;                        //P0.5、P0.6、P0.7为上拉电阻

    P1M0 = 0x00;    P1M1 = 0x70;        //P0.4、P0.5、P0.6为高阻输入
    P1PU = 0x89;                        //P1.0、P1.3、P1.7为上拉电阻

    P2M0 = 0x0F;    P2M1 = 0x00;        //P2.0、P2.1、P2.2、P2.3为推挽输出
    P2PU = 0xF0;                        //P2.4、P2.5、P2.6、P2.7为上拉电阻

    P3M0 = 0x02;    P3M1 = 0x00;        //P3.1为推挽输出
    P3PU = 0xFC;                        //P3.2、P3.3、P3.4、P3.5、P3.6、P3.7为上拉电阻

    P4M0 = 0x80;    P4M1 = 0x00;        //P4.7
    P4PU = 0x7F;                        //P4.0、P4.1、P4.2、P4.3、P4.4、P4.5、P4.6为上拉电阻

    P5M0 = 0x00;    P5M1 = 0x00;        
    P5PU = 0x1F;                        //P5.0、P5.1、P5.2、P5.3、P5.6为上拉电阻
}