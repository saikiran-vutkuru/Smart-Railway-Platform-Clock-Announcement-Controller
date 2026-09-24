#include "lcd_defines(2).h"
#include "types.h"
#include "kpm(2).h"
#include "kpm_defines.h"
#include "delay.h"
#include "lcd(2).h"

u32 ReadNum(void)
{
	u8 key;
	u32 num=0,pos=0,i;
	while(1)
	{
		 CmdLCD(DSP_ON_CUR_BLK);
		key=keyscan();
		         
		if(key == 'E' && pos == 0)
		{
		 	CmdLCD(DSP_ON_CUR_OFF);
			return 1;
		}
		else if(key>='0'&&key<='9')
		{
			 pos++;
			num=(num*10)+(key-48);
			U32LCD(num%10);
		}
		else if(key =='B')
		{
			 num=num/10;
			  i=pos;
			  while(i--)
				 CmdLCD(SHIFT_DSP_LEFT);
			 StrLCD("                ");
			 i=16;
			  while(i--)
				 CmdLCD(SHIFT_DSP_LEFT);
		//	 delay_s(1);
//	 	 CmdLCD(GOTO_LINE2_POS0);												   4
			pos--;
			if(num!=0)
			 U32LCD(num);
		}
		else if( key =='E' )
			break;
		if(pos>6)
				break;
	//delay  for one input
	   	delay_ms(200);
	}
	 CmdLCD(DSP_ON_CUR_OFF);
	return num;
}
