#include "eeprom_crl.h"

EEPROM_INFO eeprom;

/**
 * @brief	eeprom状态判定，是否写入过
 *
 * @param   
 *
 * @return  void
**/
void eeprom_statu_judge( void )
{
    uint8_t eeprom_statu_flag;

    eeprom_statu_flag = ISP_Read(EEPROM_STATU_JUDGE);

    if( eeprom_statu_flag == 0xFF)
    {
        qdc_info.roller_enable   = 1;
        qdc_info.roller_temp     = 60;
        qdc_info.led_switch      = 1;
        qdc_info.fan_level       = 3;
        qdc_info.board_switch    = 1;
        qdc_info.board_temp      = 60;
        qdc_info.inksac_switch   = 1;

        qdc_info.cir_switch      = 1;
        qdc_info.cir_start_time  = 10;
        qdc_info.cir_stop_time   = 20;

        qdc_info.stir_switch     = 2;
        qdc_info.stir_start_time = 15;
        qdc_info.stir_stop_time  = 25;

        qdc_info.ink_out_time    = 50;

        qdc_info.ink7_dis         = 1;

        eeprom_data_record(); 
    }
    eeprom_data_init();    
}

/**
 * @brief	eeprom 数据写入
 *
 * @param   
 *
 * @return  void
**/
void eeprom_data_record( void )
{
    ISP_Earse(0x0000);

    ISP_Write(ROLLER_ADDR1,qdc_info.roller_enable);
    ISP_Write(ROLLER_ADDR2,qdc_info.roller_temp);
    ISP_Write(LED_ADDR,qdc_info.led_switch);
    ISP_Write(FAN_ADDR,qdc_info.fan_level);
    ISP_Write(BOARD_ADDR1,qdc_info.board_switch);
    ISP_Write(BOARD_ADDR2,qdc_info.board_temp);
    ISP_Write(INKSAC_ADDR,qdc_info.inksac_switch);

    ISP_Write(CIR_ADDR1,qdc_info.cir_switch);
    ISP_Write(CIR_ADDR2,qdc_info.cir_start_time);
    ISP_Write(CIR_ADDR3,qdc_info.cir_stop_time);

    ISP_Write(STIR_ADDR1,qdc_info.stir_switch);
    ISP_Write(STIR_ADDR2,qdc_info.stir_start_time);
    ISP_Write(STIR_ADDR3,qdc_info.stir_stop_time);
    
    ISP_Write(INK_OUT_ADDR,qdc_info.ink_out_time);

    ISP_Write(INK_DIS,qdc_info.ink7_dis);

    ISP_Write(EEPROM_STATU_JUDGE,0x58);
}

/**
 * @brief	eeprom 数据初始化
 *
 * @param   
 *
 * @return  void
**/
void eeprom_data_init( void )
{
    qdc_info.roller_enable = ISP_Read(ROLLER_ADDR1);
    qdc_info.roller_temp = ISP_Read(ROLLER_ADDR2);

    rubber_roller_ctrl();

    qdc_info.led_switch = ISP_Read(LED_ADDR);
    led_ctrl(qdc_info.led_switch);

    qdc_info.fan_level = ISP_Read(FAN_ADDR);
    fan_ctrl(qdc_info.fan_level);

    qdc_info.board_switch = ISP_Read(BOARD_ADDR1);
    qdc_info.board_temp   = ISP_Read(BOARD_ADDR2);

    qdc_info.inksac_switch = ISP_Read(INKSAC_ADDR);

    qdc_info.cir_switch = ISP_Read(CIR_ADDR1);
    qdc_info.cir_start_time = ISP_Read(CIR_ADDR2);
    qdc_info.cir_stop_time = ISP_Read(CIR_ADDR3);

    qdc_info.stir_switch = ISP_Read(STIR_ADDR1);
    qdc_info.stir_start_time = ISP_Read(STIR_ADDR2);
    qdc_info.stir_stop_time = ISP_Read(STIR_ADDR3);

    qdc_info.ink_out_time = ISP_Read(INK_OUT_ADDR);

    qdc_info.ink7_dis = ISP_Read(INK_DIS);
}
