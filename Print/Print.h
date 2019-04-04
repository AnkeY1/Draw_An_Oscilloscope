#ifndef __Print_H
#define __Print_H		

#include "lcd.h"
#include "delay.h"
#include "usart.h"

/**
 * ��ӡ��Ҫ�����в�����
 * Todo:1��Sample_Rate��Ҫ�ڻ���ʱ����
 *      2����ʼ��ӡ�ĵ���Ҫ����
 */
typedef struct{
		u16 Array_Size; 	//<�����С
		u16* Array;				//<������ʼ��ַ
		u16 Start_Position;//<��ʼ��ʾ��λ��(�����±�)
		u8 Horizontal_Gap;//<ˮƽ���򱳾������м���
		u8 Vertical_Gap;  //<��ֱ���򱳾������м���
		u8 Framex_Start;  //<����������ʼ���x����    ������������ϵ�������ʾ
		u8 Framey_Start;	//<����������ʼ���y����    ������������ϵ�������ʾ
		u8 Sample_Rate;		//<������(�漰�ӿڣ���u8��ʾ����״̬)
	  u16 V_Scale;  //<���ȵĵ�λ ��ȡֵ��Χ:mV100,mV200,mV500,V1,V2,V5    ��λΪmv
	  u32 H_Scale; //<ʱ��ĵ�λ��ȡֵ��Χ:ns10,ns20,ns50,ns100,ns200,ns500,ms1,ms2,ms5,ms10,ms20,ms50,ms100,ms200,ms500   ��λΪns
		u16 gnd; //<��������λ�ã�(��LCD�ϵ�λ��)
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
