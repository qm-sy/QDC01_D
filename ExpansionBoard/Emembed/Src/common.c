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
    static uint16_t level1_cnt = 0;
    static uint16_t level2_cnt = 0;
    static uint16_t level3_cnt = 0;
    static uint16_t level4_cnt = 0;
    static uint16_t level5_cnt = 0;
    static uint16_t level6_cnt = 0;
    static uint16_t level7_cnt = 0;
    static uint16_t cir_delay_cnt  = 0;
    static uint16_t stir_delay_cnt = 0;
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
    /* 2, LEVEL Scan                            */
    /* 2.1, LEVEL   1                          */
    if( level1_H == 0 )
    {
        level1_cnt++;
        if( level1_cnt >= level.level_delay )
        {
            level1_cnt = 0;
            level.level1_down_flag = 1;
        }
    }else
    {
        level1_cnt = 0;
        level.level1_down_flag = 0;
    }

    /* 2.2, LEVEL   2                          */
    if( level2_H == 0 )
    {
        level2_cnt++;
        if( level2_cnt >= level.level_delay )
        {
            level2_cnt = 0;
            level.level2_down_flag = 1;
        }
    }else
    {
        level2_cnt = 0;
        level.level2_down_flag = 0;
    }

    /* 2.3, LEVEL   3                          */
    if( level3_H == 0 )
    {
        level3_cnt++;
        if( level3_cnt >= level.level_delay )
        {
            level3_cnt = 0;
            level.level3_down_flag = 1;
        }
    }else
    {
        level3_cnt = 0;
        level.level3_down_flag = 0;
    }
    /* 2.4, LEVEL   1                          */
    if( level4_H == 0 )
    {
        level4_cnt++;
        if( level4_cnt >= level.level_delay )
        {
            level4_cnt = 0;
            level.level4_down_flag = 1;
        }
    }else
    {
        level4_cnt = 0;
        level.level4_down_flag = 0;
    }

    /* 2.5, LEVEL   2                          */
    if( level5_H == 0 )
    {
        level5_cnt++;
        if( level5_cnt >= level.level_delay )
        {
            level5_cnt = 0;
            level.level5_down_flag = 1;
        }
    }else
    {
        level5_cnt = 0;
        level.level5_down_flag = 0;
    }

    /* 2.6, LEVEL   3                          */
    if( level6_H == 0 )
    {
        level6_cnt++;
        if( level6_cnt >= level.level_delay )
        {
            level6_cnt = 0;
            level.level6_down_flag = 1;
        }
    }else

    {
        level6_cnt = 0;
        level.level6_down_flag = 0;
    }

    /* 2.7, LEVEL   3                          */
    if( level7_H == 0 )
    {
        level7_cnt++;
        if( level7_cnt >= level.level_delay )
        {
            level7_cnt = 0;
            level.level7_down_flag = 1;
        }
    }else
    {
        level7_cnt = 0;
        level.level7_down_flag = 0;
    }

    /* 3. 循环和搅拌电机延时 */
    if( dc_ctrl.cir_switch == 1 )
    {
        cir_delay_cnt++;
        if( cir_delay_cnt <= dc_ctrl.cir_start_time )
        {
            pwm_ctrl(CIR_CTRL,dc_ctrl.cir_level);
        }
        if((cir_delay_cnt < (dc_ctrl.cir_start_time + dc_ctrl.cir_stop_time)) && ( cir_delay_cnt > dc_ctrl.cir_start_time ))
        {
            pwm_ctrl(CIR_CTRL,0);
        }
        if(cir_delay_cnt >= (dc_ctrl.cir_start_time + dc_ctrl.cir_stop_time))
        {
            cir_delay_cnt = 0;
        }
    }
    
    if( dc_ctrl.stir_switch == 1 )
    {
        stir_delay_cnt++;
        if( stir_delay_cnt <= dc_ctrl.stir_start_time )
        {
            pwm_ctrl(STIR_CTRL,dc_ctrl.stir_level);
        }
        if((stir_delay_cnt < (dc_ctrl.stir_start_time + dc_ctrl.stir_stop_time)) && ( stir_delay_cnt > dc_ctrl.stir_start_time ))
        {
            pwm_ctrl(STIR_CTRL,0);
        }
        if(stir_delay_cnt >= (dc_ctrl.stir_start_time + dc_ctrl.stir_stop_time))
        {
            stir_delay_cnt = 0;
        }
    }  
}
