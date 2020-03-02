/*
 * TMU_Project.c
 *
 * Created: 1/11/2020 6:27:18 PM
 * Author : Johnny
 */ 

#include "TMU.h"
#include "DIO.h"
#include "registers.h"
#include "interrupts.h"
#include "Timer.h"
#include "Sleep.h"

void cbk1(void)
{
	DIO_Toggle(GPIOA,BIT0);
}

void cbk2(void)
{
	DIO_Toggle(GPIOA,BIT1);
}

void cbk3(void)
{
	DIO_Toggle(GPIOA,BIT2);
}

void cbk4(void)
{
	DIO_Toggle(GPIOA,BIT3);
}

int main(void)
{
	GIE();
	
	DIO_Cfg_s DIO;
	DIO.dir=OUTPUT;
	DIO.GPIO=GPIOA;
	DIO.pins=FULL_PORT;
	DIO_init(&DIO);
		
	TMU_Init();
	
	TMU_Task_cfg_t TMU0;
	TMU0.current_time=0;
	TMU0.Period_Time=1;
	TMU0.ptrfu_Timer_Cbk=cbk1;
	TMU0.Repetition=PERIODIC;
	TMU_Start(&TMU0);
	
	TMU_Task_cfg_t TMU2;
	TMU2.current_time=0;
	TMU2.Period_Time=2;
	TMU2.ptrfu_Timer_Cbk=cbk2;
	TMU2.Repetition=PERIODIC;
	TMU_Start(&TMU2);	
	
	TMU_Task_cfg_t TMU3;
	TMU3.current_time=150;
	TMU3.Period_Time=3;
	TMU3.ptrfu_Timer_Cbk=cbk3;
	TMU3.Repetition=PERIODIC;
	TMU_Start(&TMU3);
	
	TMU_Task_cfg_t TMU4;
	TMU4.current_time=0;
	TMU4.Period_Time=1;
	TMU4.ptrfu_Timer_Cbk=cbk4;
	TMU4.Repetition=PERIODIC;
	TMU_Start(&TMU4);
	
	
	
	Tmu_Stop(cbk4);
	//Tmu_Stop(cbk3);
	//TMU_DeInit();
	
	/*Timer_cfg_s Timer;
	Timer.Timer_Cbk_ptr=cbk;
	Timer.Timer_CH_NO=1;
	Timer.Timer_Mode=TIMER_MODE;
	Timer.Timer_Polling_Or_Interrupt=TIMER_INTERRUPT_MODE;
	Timer.Timer_Prescaler=TIMER_PRESCALER_64;
	Timer_Init(&Timer);
	Timer_Start(1,2500);*/
	Sleep_Init();
		
    while (1) 
    {
		PORTA_DATA|=0x80;
		TMU_Dispatcher();
		PORTA_DATA&=~(0x80);
		Sleep_Start(Idle);
			
    }
}

