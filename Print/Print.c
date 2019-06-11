# include "Print.h"

#define gear 4


/**
 * 初始化打印过程，对结构体内的变量赋值
 */
void Print_Init(Print_State * State , u16* array){
		delay_init();
		uart_init(115200);
		LCD_Init();
		LCD_Display_Dir(1);			//Horizontal
		POINT_COLOR=RED;	
		State->Horizontal_Gap = 8;
	  	State->Array = array;
		State->Vertical_Gap = 5;
		State->Framex_Start = 0;
		State->Framey_Start = 40;
		State->H_Scale = 100000;    //1000ns=1us
		State->V_Scale = 5000;     //500mv一格
		
		///外部传入
		State->Start_Position = 0;
		State->Sample_Rate = 11;
		State->gnd = 140;
}


/**
 * 根据各种参数显示一屏的数据
 * Demo:以目前初始化的数据计算，即假设一个网格的长和宽都是40
 */
void Print_Frame(Print_State * State){    
		u16 true_Sample_Rate;
		double Sample_t;
		double Y_Co = 200/4096.0;
		u16 Print_Gap;
		u16 count = 0;
		int i = 0;
		if(State->Sample_Rate == 11)true_Sample_Rate = 857;//<   kHz
		if(State->Sample_Rate == 12)true_Sample_Rate = 10;
    		if(State->Sample_Rate == 21)true_Sample_Rate = 1;
		POINT_COLOR=YELLOW;
		Sample_t = 1.0/true_Sample_Rate;                  //<  ms
		if(State->H_Scale/(40*1000000.0) > Sample_t){                //< 抛弃数组内的点
				Print_Gap = (State->H_Scale/(40*1000000.0))/Sample_t + 0.5;
				for(i = State->Start_Position ; i < 800 ; i+=Print_Gap){
						LCD_DrawPoint(count,get_Y(State, State->Array[i]));
						if(count == 320)	return;
						count++;
				}
		}
		else{                                             //< 抛弃屏幕上的点
				Print_Gap = Sample_t/(State->H_Scale/(40*1000000.0)) + 0.5;
				for(i = State->Start_Position ; i < 800 ; ++i){
						LCD_DrawPoint(count,get_Y(State, State->Array[i]));
						if(count == 320)	return;
						count+=Print_Gap;
				}
		}
}


/**
 * 显示黑色背景，背景网格线，和坐标轴
 */
void Print_Grid(Print_State * State){
		LCD_Clear(BLACK);
		Print_Horizional_Grid(State);
		Print_Vertical_Grid(State);
		display_Axis();
		display_AxisPoint();
}

/**
 * 显示水平网格虚线
 */
void Print_Horizional_Grid(Print_State * State){
			u16 y = State->Framey_Start;
			u16 tmp = State->Framex_Start;
			POINT_COLOR=GRAY;
			for(;y <=240;y+=(240-State->Framey_Start)/State->Vertical_Gap){//(240-State->Framey_Start)/State->Horizontal_Gap
					for(;tmp<=320;tmp+=10){   //<虚线间距为10
							LCD_DrawLine(tmp,y,tmp+5,y);
					}
					tmp = State->Framex_Start;
			}
}

/**
 * 显示网格虚线
 */
void Print_Vertical_Grid(Print_State * State){
			u16 x = State->Framex_Start;
			u16 tmp = State->Framey_Start;
			POINT_COLOR=GRAY;
			for(;x <=320;x+=(320-State->Framex_Start)/State->Horizontal_Gap){//(240-State->Framex_Start)/State->Horizontal_Gap
					for(;tmp<=320;tmp+=10)
						LCD_DrawLine(x,tmp,x,tmp+5);
					tmp = State->Framey_Start;
			}
}

/**
 * 显示坐标轴
 */
void display_Axis(void)
{
	POINT_COLOR=WHITE;
	LCD_DrawLine(0,140,320,140);   //y = 140
	LCD_DrawLine(160,40,160,240);  //x = 160
}


/**
 * 显示坐标轴刻度
 */
void display_AxisPoint(void)
{
	int i;
	for (i=0;i<36;++i){
		POINT_COLOR=WHITE;
		LCD_DrawLine(10*i,137,10*i,140); //<间距为10，长度为140-137=3
	}
		for (i=4;i<24;++i){
			POINT_COLOR=WHITE;
			LCD_DrawLine(160,10*i,163,10*i); //<间距为10，长度为163-160=3
		}
}


double get_Y(Print_State * State, u16 raw_y){
		if(gear == 1){return State->gnd + (0.5/1.465/2) * (3300.0/4096) * (raw_y-2048) / (State->V_Scale / 40.0);}
		else if(gear == 2){return State->gnd + (1.0 / 0.98) * (3300.0/4096) * (raw_y-2048) / (State->V_Scale / 40.0);}
			else if(gear == 3){return State->gnd + (2 / 1.014) * (3300.0/4096) * (raw_y-2048) / (State->V_Scale / 40.0);}
				else if(gear == 4){return State->gnd + (10.0/3/0.898) * (3300.0/4096) * (raw_y-2048) / (State->V_Scale / 40.0);}
}

/**
 * 改变采样率参数
 */
void change_Sample_Rate(Print_State * State, u8 New_Sample_rate){
		State->Sample_Rate = New_Sample_rate;
}

/**
 * 改变起始位置参数
 */
void change_Start_Position(Print_State * State, u16 New_Start_Position){
		State->Start_Position = New_Start_Position;
}
