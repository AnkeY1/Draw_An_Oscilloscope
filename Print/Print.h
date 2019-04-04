#ifndef __Print_H
#define __Print_H		

#include "lcd.h"
#include "delay.h"
#include "usart.h"

/**
 * 打印需要的所有参数：
 * Todo:1、Sample_Rate需要在换挡时调整
 *      2、开始打印的点需要传入
 */
typedef struct{
		u16 Array_Size; 	//<数组大小
		u16* Array;				//<数组起始地址
		u16 Start_Position;//<开始显示的位置(数组下标)
		u8 Horizontal_Gap;//<水平方向背景网格有几列
		u8 Vertical_Gap;  //<垂直方向背景网格有几行
		u8 Framex_Start;  //<背景网格起始点的x坐标    背景网格从左上到右下显示
		u8 Framey_Start;	//<背景网格起始点的y坐标    背景网格从左上到右下显示
		u8 Sample_Rate;		//<采样率(涉及接口，用u8表示三种状态)
	  u16 V_Scale;  //<幅度的档位 ，取值范围:mV100,mV200,mV500,V1,V2,V5    单位为mv
	  u32 H_Scale; //<时间的档位，取值范围:ns10,ns20,ns50,ns100,ns200,ns500,ms1,ms2,ms5,ms10,ms20,ms50,ms100,ms200,ms500   单位为ns
		u16 gnd; //<地线所在位置，(在LCD上的位置)
}Print_State;

void Print_Init(Print_State * State, u16* array);
void Print_Frame(Print_State * State);
void Print_Grid(Print_State * State);
void Print_Horizional_Grid(Print_State * State);
void Print_Vertical_Grid(Print_State * State);
void display_Axis(void);
void display_AxisPoint(void);
double get_Y(Print_State * State, u16 raw_y);
void change_Sample_Rate(Print_State * State, u8 New_Sample_rate);
void change_Start_Position(Print_State * State, u16 New_Start_Position);
















#endif
