#include "power_crl.h"

AC_DC ac_dc;


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
        PWMB_CCR7= level * 184;
    }
    if( device == STIR_CTRL )
    {
        PWMB_CCR8= level * 184;
    }
}

void output_statu_init( void )
{
    DC24_1 = DC24_2 = DC24_3 = 0;
    DC_PWM1 = DC_PWM2 = 1;
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

        // if( temp.temp_value1 >= temp.temp_alarm_value )  
        // {
        //     ac_dc.ac220_out_temp_allow = 0;     
        // }else
        // {
        //     ac_dc.ac220_out_temp_allow = 1;     
        // }
        
        temp.temp_scan_flag = 0;
    }
}

void board_ctrl( uint8_t on_off )
{
    if( on_off == 1 )
    {
        DC24_1 = 1;
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
