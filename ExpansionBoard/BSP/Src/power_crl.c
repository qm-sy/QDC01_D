#include "power_crl.h"

DC_CTRL dc_ctrl;


/**
 * @brief	24V PWM风扇档位控制函数
 *
 * @param   level :风扇档位 0~6档
 *
 * @return  void
**/
void pwm_ctrl( uint8_t device, uint8_t level )
{
    if( device  == CIR_CTRL )
    {
        PWMB_CCR7= 1104 - level * 184;
    }
    if( device == STIR_CTRL )
    {
        PWMB_CCR8= 1104 - level * 184;
    }
}

void output_statu_init( void )
{
    DC24_1 = DC24_2 = DC24_3 = 0;
    DC_PWM1 = DC_PWM2 = 1;
    dc_ctrl.cir_level = 0;
    dc_ctrl.stir_level = 0;
}
/**
 * @brief 温度扫描，DHT11温湿度扫描 1s/次 控制220V输出使能
 *
 * @param[in] 
 * 
 * @return  
 * 
**/
void temp_scan( void )
{
    if( temp.temp_scan_flag == 1)
    {
        temp.temp_value1 =  get_temp(NTC);

        Read_DHT11();

        board_ctrl();
        
        temp.temp_scan_flag = 0;
    }
}

void board_ctrl()
{
    if( dc_ctrl.board_out_allow == 1 )
    {
        if( temp.temp_value1 < dc_ctrl.board_alarm_temp )  
        {
            DC24_1 = 1;   
        }else
        {
            DC24_1 = 0;
        }
    }else
    {
        DC24_1 = 0;
    }
}

void inksac_ctrl( uint8_t on_off )
{
    if( on_off == 1 )
    {
        DC24_2 = 1;
    }else
    {
        DC24_2 = 0;
    }
}
