#include "common.h"

/**
 * @brief	一些定时执行的事件   Timer3：10ms
 *
 * @param   
 *
 * @return  void
**/
void Tim3_ISR( void ) interrupt 19
{

    static uint16_t temp_scan_cnt = 0;
    static uint16_t scan_04_cnt = 0;
    /* 1, temp 上报 1s/次                             */
    if( temp.temp_scan_flag == 0 )
    {
        temp_scan_cnt++;
        if( temp_scan_cnt == 100 )
        {
            temp.temp_scan_flag = 1;
            temp_scan_cnt = 0;
        }
    }
    if( rs485.scan_04_flag == 0 )
    {
        scan_04_cnt++;
        if( scan_04_cnt == 100 )
        {
            scan_04_cnt = 0;
            rs485.scan_04_flag = 1;
        }
    }
}
