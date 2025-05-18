#ifndef __MAIN_H_
#define __MAIN_H_

#include "stc8h.h"
#include "stdio.h"
#include "STRING.H"
#include "intrins.h"

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

sbit RX_485      = P0^2;
sbit TX_485      = P0^3;
sbit DR_485      = P0^4;

sbit Temp_Hum    = P1^0;
sbit Analog2     = P1^1;
sbit Signal_IN   = P1^3;
sbit NTC1        = P1^4;
sbit NTC2        = P1^5;
sbit NTC3        = P1^6;
sbit WASTE_INK   = P1^7;

sbit Signal_OUT  = P2^1;
sbit PWM         = P2^2;
sbit LED         = P2^3;

sbit RX1         = P3^0;
sbit TX1         = P3^1;
sbit ZERO        = P3^2;
sbit FAN_TMEP    = P3^6;
sbit Signal_3V3  = P3^7;

sbit AC_Out1     = P4^1;
sbit AC_Out2     = P4^2;
sbit AC_Out3     = P4^3;
sbit Buzzer      = P4^7;

void GPIO_Init( void );
void Uart4_Init(void);
void Timer0_Init( void );
void Uart4_Send_Statu_Init( void );
void Modbus_Event_485( void );
void Modbus_Fun6_485( void );
void slave_to_master_485(uint8_t code_num,uint8_t length);
void delay_ms(uint16_t time);
uint16_t MODBUS_CRC16(uint8_t *buf, uint8_t length);

#endif