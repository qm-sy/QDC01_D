#ifndef __POWER_CRL_H_
#define __POWER_CRL_H_

#include "sys.h"
#include "gpio.h"
#include "ntc.h"
#include "eeprom_crl.h"

#define FAN_ON    1
#define FAN_OFF   0

typedef struct 
{
    uint8_t  ac220_out_enable;     //通道1输出使能
}AC_DC;

extern AC_DC ac_dc;

void led_ctrl( uint8_t on_off );
void fan_ctrl( uint8_t level );
void rubber_roller_ctrl();
void temp_scan( void );

#endif