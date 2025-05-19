#include "level.h"

LEVEL level;

void level_info_init( void )
{
    level.level_info_L = 0;                //DATA_H
    level.level_info_H = 0;                //DATA_L             
    level.level_delay = 2000;
    level.level1_down_flag = 0;
    level.level2_down_flag = 0;
    level.level3_down_flag = 0;
    level.level4_down_flag = 0;
    level.level5_down_flag = 0;
    level.level6_down_flag = 0;
    level.level7_down_flag = 0;
}
void ink_scan( void )
{
    /*  LEVEL    1   */
    if( level1_H == 1 )
    {
        level.level_info_L &= 0xFC;
        level.level_info_L |= 0X03;
    }
    if(( level1_H == 0 ) && ( level.level1_down_flag == 0 ))
    {
        level.level_info_L &= 0xFC;
        level.level_info_L |= 0X02;
    }
    if(( level1_H == 0 ) && ( level.level1_down_flag == 1 ))
    {
        level.level_info_L &= 0xFC;
        level.level_info_L |= 0X01;
    }

    /*  LEVEL    2   */
    if( level2_H == 1 )
    {
        level.level_info_L &= 0xF3;
        level.level_info_L |= 0X0C;
    }
    if(( level2_H == 0 ) && ( level.level2_down_flag == 0 ))
    {
        level.level_info_L &= 0xF3;
        level.level_info_L |= 0X08;
    }
    if(( level2_H == 0 ) && ( level.level2_down_flag == 1 ))
    {
        level.level_info_L &= 0xF3;
        level.level_info_L |= 0X04;
    }
    
    /*  LEVEL    3   */
    if( level3_H == 1 )
    {
        level.level_info_L &= 0xCF;
        level.level_info_L |= 0X30;
    }
    if(( level3_H == 0 ) && ( level.level3_down_flag == 0 ))
    {
        level.level_info_L &= 0xCF;
        level.level_info_L |= 0X20;
    }
    if(( level3_H == 0 ) && ( level.level3_down_flag == 1 ))
    {
        level.level_info_L &= 0xCF;
        level.level_info_L |= 0X10;
    }
    
    /*  LEVEL    4   */
    if( level4_H == 1 )
    {
        level.level_info_L &= 0x3F;
        level.level_info_L |= 0XC0;
    }
    if(( level4_H == 0 ) && ( level.level4_down_flag == 0 ))
    {
        level.level_info_L &= 0x3F;
        level.level_info_L |= 0X80;
    }
    if(( level4_H == 0 ) && ( level.level4_down_flag == 1 ))
    {
        level.level_info_L &= 0x3F;
        level.level_info_L |= 0X40;
    }
    
    /*  LEVEL    5   */
    if( level5_H == 1 )
    {
        level.level_info_H &= 0xFC;
        level.level_info_H |= 0X03;
    }
    if(( level5_H == 0 ) && ( level.level5_down_flag == 0 ))
    {
        level.level_info_H &= 0xFC;
        level.level_info_H |= 0X02;
    }
    if(( level5_H == 0 ) && ( level.level5_down_flag == 1 ))
    {
        level.level_info_H &= 0xFC;
        level.level_info_H |= 0X01;
    }
    
    /*  LEVEL    6   */
    if( level6_H == 1 )
    {
        level.level_info_H &= 0xF3;
        level.level_info_H |= 0X0C;
    }
    if(( level6_H == 0 ) && ( level.level6_down_flag == 0 ))
    {
        level.level_info_H &= 0xF3;
        level.level_info_H |= 0X08;
    }
    if(( level6_H == 0 ) && ( level.level6_down_flag == 1 ))
    {
        level.level_info_H &= 0xF3;
        level.level_info_H |= 0X04;
    }
    
    /*  LEVEL    7   */
    if( level7_H == 1 )
    {
        level.level_info_H &= 0xCF;
        level.level_info_H |= 0X30;
    }
    if(( level7_H == 0 ) && ( level.level7_down_flag == 0 ))
    {
        level.level_info_H &= 0xCF;
        level.level_info_H |= 0X20;
    }
    if(( level7_H == 0 ) && ( level.level7_down_flag == 1 ))
    {
        level.level_info_H &= 0xCF;
        level.level_info_H |= 0X10;
    }
}