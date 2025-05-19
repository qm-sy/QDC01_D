#ifndef __MODBUS_RTU_H_
#define __MODBUS_RTU_H_

#include "communication.h"
#include "ntc.h"
#include "gpio.h"
#include "power_crl.h"
#include "eeprom_crl.h"

#define ADDR_485     0xEB
#define ADDR_SATA    0xDC

typedef struct 
{
    uint8_t  byte_info_H;                //DATA_H
    uint8_t  byte_info_L;                //DATA_L
    uint8_t  byte_cnt;                   //BYTE NUM*2
    uint8_t  send_value_addr;            //DATA1 H 位置
    uint8_t  rcv_value_addr;             //DATA1 H 位置
    uint16_t start_addr;                 //查询起始位置
}MODBIS_INFO;


extern MODBIS_INFO modbus;

void Modbus_Event_485( void );
void Modbus_Event_Sata( void );

void Modbus_Fun3_485( void );
void Modbus_Fun4_485( void );
void Modbus_Fun6_485( void );
void Modbus_Fun16_485( void );

void Modbus_Fun3_Sata( void );
void Modbus_Fun4_Sata( void );
void Modbus_Fun6_Sata( void );
void Modbus_Fun16_Sata( void );



void slave_to_master_485(uint8_t code_num,uint8_t length);
void slave_to_master_Sata(uint8_t code_num,uint8_t length);

uint16_t MODBUS_CRC16(uint8_t *buf, uint8_t length);

void waste_ink_scan( void );
void send_to_EB_16( void );
void send_to_EB_06( uint8_t addr, uint8_t val_H, uint8_t val_L);
void send_to_EB_04( void );

#endif