#ifndef __POWER_CRL_H_
#define __POWER_CRL_H_

#include "sys.h"
#include "gpio.h"
#include "ntc.h"
#include "dht11.h"

#define FAN_ON    1
#define FAN_OFF   0

#define CIR_CTRL  1
#define STIR_CTRL 2

typedef struct 
{
    uint8_t  board_out_allow;
    uint8_t  board_alarm_temp;
    uint16_t cir_start_time;
    uint16_t cir_stop_time;
    uint16_t stir_start_time;
    uint16_t stir_stop_time;  
    uint8_t  cir_level;
    uint8_t  stir_level;
    uint8_t  cir_switch;
    uint8_t  stir_switch;
}DC_CTRL;

extern DC_CTRL dc_ctrl;

void output_statu_init( void );
void pwm_ctrl( uint8_t device, uint8_t level );
void board_ctrl();
void inksac_ctrl( uint8_t on_off );
void rubber_roller_ctrl( uint8_t on_off );
void temp_scan( void );

#endif