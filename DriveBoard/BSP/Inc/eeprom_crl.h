#ifndef __EEPROM_CRL_H_
#define __EEPROM_CRL_H_

#include "eeprom.h"
#include "sys.h"
#include "power_crl.h"
#include "ntc.h"
#include "stdio.h"
#include "modbus_rtu.h"

#define ROLLER_ADDR1        0x0000      //低字节：开关  
#define ROLLER_ADDR2        0x0001      //高字节：停止温度
#define LED_ADDR            0x0002        //开关
#define FAN_ADDR            0x0003       //档位
#define BOARD_ADDR1         0x0004        //低字节：开关 
#define BOARD_ADDR2         0x0005        //高字节：停止温度
#define INKSAC_ADDR         0X0006      //开关
#define CIR_ADDR1           0X0007        //level
#define CIR_ADDR2           0X0008      //启动时间
#define CIR_ADDR3           0X0009        //停止时间
#define CIR_ADDR4           0X000A        //开关
#define STIR_ADDR1          0X000B
#define STIR_ADDR2          0X000C
#define STIR_ADDR3          0X000D
#define STIR_ADDR4          0X000E
#define INK_OUT_ADDR        0X000F
#define INK_DIS             0X0010

#define EEPROM_STATU_JUDGE    0X0015         

typedef struct 
{
    uint8_t  pwm_info;
    uint8_t  led_info;         
    uint8_t  ac220_switch;  
    uint8_t  ac220_level; 
    uint8_t  sync_info;
    uint8_t  mode_info;     
    uint8_t  temp_alarm_value;       
    uint8_t  gonglv_min;
    uint8_t  gonglv_h_H;
    uint8_t  gonglv_h_L;
}EEPROM_INFO;

extern EEPROM_INFO eeprom;

void eeprom_statu_judge( void );
void eeprom_data_record( void );
void eeprom_data_init( void );

#endif