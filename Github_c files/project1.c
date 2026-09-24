 #include <LPC21xx.H>
#include "lcd_defines(2).h"
#include "lcd(2).h"
#include "input.h"
#include "kpm(2).h"
#include "kpm_defines.h"
#include "delay.h"
//intrrupt
#define EINT0_VIC_CHNO 14
//#define EINT0_STATUS_LED 30 //@p1.16
#define EINT0_PIN_FUNC   0x0000000C

char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

 u32 H,M,S,D,MON,Y,DW,a,b,z; 

 u32 n1,a1,d1,pl1,ah1,am1,lh1,lm1;
 u32 n2,a2,d2,pl2,ah2,am2,lh2,lm2;
 u32 n3,a3,d3,pl3,ah3,am3,lh3,lm3;
 //count for leds
 u32 cnt1=0,cnt2=0,cnt3=0;
 s32 t1,t2,t3;
 //interrupt
//void eint0_isr(void) __irq;
int main()
{
	//intrrupt
	//Cfg p0.1 as EINT0 input pins
	PINSEL0&=~(3<<(1*2));
	PINSEL0|=EINT0_PIN_FUNC;
	//cfg VIC	let eint0 be irq type	default all are anyway irq type//VICIntSelect=0;
	//enable eint0 via vic
	VICIntEnable=1<<EINT0_VIC_CHNO;
	//cfg eint0 as v.irq with priority 0
	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
	//load isr addr into irq slot 0
	VICVectAddr0=(u32 )eint0_isr;
	//cfg External Interrupt Peripheral(EIP)
	//enable EINT0 ,all are default enabled
	//EXTINT=0;
	//cfg eint0 as edge triggered,
	EXTMODE=1<<0;
	//cfg eint0 for falling edge trigger
	//default all are falling edge
	//EXTPOLAR=0;



     leds( );
	//reset clock tick counter
	CCR = 1<<1;
	//set the 1 second tick time
	PREINT = 456;
	PREFRAC = 25024;
	
	//enable RTC
	CCR = 1<<0;
	
	InitLCD();
	Init_KPM();
	input1( );
	input2( );
   HOUR =H;
	MIN = M;
	SEC = S;
	DOM = D;
	MONTH =MON ;
	YEAR = Y;
	DOW = DW;
	while(1)
	{
	    CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		CharLCD((HOUR/10)+48);
		CharLCD((HOUR%10)+48);
		CharLCD(':');
		CharLCD((MIN/10)+48);
		CharLCD((MIN%10)+48);
		CharLCD(':');
		CharLCD((SEC/10)+48);
		CharLCD((SEC%10)+48);
				
		CmdLCD(GOTO_LINE2_POS0);
		CharLCD((DOM/10)+48);
		CharLCD((DOM%10)+48);
		CharLCD('/');
		CharLCD((MONTH/10)+48);
		CharLCD((MONTH%10)+48);
		CharLCD('/');
		U32LCD(YEAR);

		CmdLCD(GOTO_LINE1_POS0 + 10);		
		StrLCD(week[DOW]);
	    delay_ms(1000);
		CmdLCD(CLEAR_LCD);
		output( );
	}
}
