#include "power_crl.h"

AC_DC ac_dc;

/**
 * @brief	24V LED开关控制函数
 *
 * @param   on_off：0：关闭 1：开启
 *
 * @return  void
**/
void led_ctrl( uint8_t on_off )
{
    if( on_off == FAN_ON )
    {
        LED = 0;
    }else
    {
        LED = 1;
    }
}

/**
 * @brief	24V PWM风扇档位控制函数
 *
 * @param   level :风扇档位 0~6档
 *
 * @return  void
**/
void fan_ctrl( uint8_t level )
{
    PWMB_CCR7= level * 184;
}

void rubber_roller_ctrl()
{
    if( qdc_info.roller_enable == 1 )
    {
        if( qdc_info.thermopile_temp < qdc_info.roller_temp )  
        {
            AC_Out1 = 0; 
        }else
        {
            AC_Out1 = 1;
        }
    }else
    {
        AC_Out1 = 1;
    }
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

        qdc_info.thermopile_temp = get_temp(THERMOPILE);
        
        rubber_roller_ctrl();
        
        temp.temp_scan_flag = 0;
    }
}
