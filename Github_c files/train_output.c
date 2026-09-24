#include "lcd(2).h"
#include "input.h"
#include "types.h"
#include "lcd_defines(2).h"
#include "delay.h"
#include <LPC21xx.H>
#include <string.h>

//buzzer
#define BUZZER 21 //po.20

//leds
#define LED_green 22	//po.21
#define LED_red 23	//po.22
#define LED_yellow 24	//po.23

extern char week[][4];
//rtc variables
extern u32 H,M,S,D,MON,Y,DW;
//train1
extern 	u32 n1,a1,d1,pl1,ah1,am1,lh1,lm1;
//train2
extern	u32 n2,a2,d2,pl2,ah2,am2,lh2,lm2;
//train 3
extern	u32 n3,a3,d3,pl3,ah3,am3,lh3,lm3;
//leds
extern u32 cnt1,cnt2,cnt3;

extern s32 t1,t2,t3;

     s32 pos,c;
    s8 str1[ ]="Hyderabad X Gujarat";
	 s8 str2[ ]="lb nagarX Hyd";
	 s8 str3[ ]="Vizag X Hyd";

	 s8 i;
	 s32 len1,len2,len3;

//leds enable
void leds(void)
{
IODIR0|=(1<<LED_yellow)|(1<< LED_red)|(1<< LED_green)|(1<<BUZZER);
IOCLR0=	(1<<LED_yellow)|(1<< LED_red)|(1<< LED_green);	
}
 //train display before arrival
u32 current_time_min(void)
{
    return (HOUR*60) + MIN;
}

/* Returns 1 when RTC is from 2 minutes before  arrival minute*/
u32 train_window(u32 arrival_hour, u32 arrival_min)
{
    u32 now;
    u32 arrival;
    u32 start;
    now = current_time_min();
    arrival = (arrival_hour*60) + arrival_min;
    if(arrival >= 2)
    {
        start = arrival - 2;
        if((now >= start) && (now <= arrival-1))
            return 1;
    }
    else
    {
        /* Handles arrival around midnight
           Ex 00:01 -> 23:59, 00:00, 00:01 */
        start =(24*60)+arrival-2;
        if((now >= start) || (now <= arrival))
            return 1;
    }
    return 0;
}
void output(void)
{
				len1=strlen(str1);
				len2=strlen(str2);
				len3=strlen(str3);
        /* Train 1: arrival-2 min through arrival */
        if(train_window(ah1,am1))
        {
            //display_train(n1,pl1,ah1,am1);
						//train1 display
							for(pos=15;pos>=(6-(len1-1));pos--)
							{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE2_POS0);
								CharLCD('p');
								U32LCD(pl1);
								CmdLCD(GOTO_LINE2_POS0+5);
								StrLCD("arr");
								CharLCD('-');
								CharLCD((ah1/10)+48);
								CharLCD((ah1%10)+48);
								CharLCD(':');
								CharLCD((am1/10)+48);
								CharLCD((am1%10)+48);
								IOSET0=1<<LED_yellow;
								//line1
								CmdLCD(GOTO_LINE1_POS0);
								U32LCD(n1);
								i=0;
									while(str1[i])
									{
										c=pos+i;
											if(c>=6&&c<16)
											{
													CmdLCD(GOTO_LINE1_POS0+c);
													CharLCD(str1[i]);
											}
													i++;
									}

								delay_ms(1000);

							}
					delay_ms(100);
					IOCLR0=1<<LED_yellow;  
					CmdLCD(CLEAR_LCD);
		}
   		else if(HOUR==ah1&&MIN==am1)
			{
						t1=1;
						for(pos=15;pos>=(6-(len1-1));pos--)
						{
								
								IOSET0=1<<BUZZER;
								delay_ms(500);
								IOCLR0=1<<BUZZER;
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("Train1 arrived");
								CmdLCD(GOTO_LINE1_POS0);
								U32LCD(n1);
								i=0;
								while(str1[i])
								{
									c=pos+i;
									if(c>=6&&c<16)
									{
										CmdLCD(GOTO_LINE1_POS0+c);
										CharLCD(str1[i]);
									}
									i++;
								}
							delay_ms(1000);
						}
						if(cnt1==0)
						IOSET0=1<<LED_green;
						else
						IOSET0=1<<LED_red;
		}
	    else if(HOUR==lh1&&MIN==lm1)
			  {
			  		t1=0;
					 for(pos=15;pos>=(6-(len1-1));pos--)
	    			{
						
						CmdLCD(CLEAR_LCD);
						IOSET0=1<<BUZZER;
				 	    CmdLCD(GOTO_LINE2_POS0);
					    StrLCD("Train1 leaving");
						//line1
						CmdLCD(GOTO_LINE1_POS0);
		        		U32LCD(n1);
					  	i=0;
		       			while(str1[i])
						{
	       		 			c=pos+i;
         					if(c>=6&&c<16)
        					{
										CmdLCD(GOTO_LINE1_POS0+c);
		   		    					CharLCD(str1[i]);
							}
   								i++;
						}
					delay_ms(1000);
				  }
			  		delay_ms(500);
			  		IOCLR0=1<<BUZZER;
						if(cnt1==0)
						IOCLR0=1<<LED_green;
					  	else
						IOCLR0=1<<LED_red;
						CmdLCD(CLEAR_LCD);
			}

        /* Train 2: arrival-2 min through arrival */
        else if(train_window(ah2,am2))
        {
           // display_train(n2,pl2,ah2,am2);
			   //train2 display
						  for(pos=15;pos>=(6-(len2-1));pos--)
							{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE2_POS0);
								CharLCD('p');
								U32LCD(pl2);
								CmdLCD(GOTO_LINE2_POS0+5);
								StrLCD("arr");
								CharLCD('-');
								CharLCD((ah2/10)+48);
								CharLCD((ah2%10)+48);
								CharLCD(':');
								CharLCD((am2/10)+48);
								CharLCD((am2%10)+48);
								IOSET0=1<<LED_yellow;
								CmdLCD(GOTO_LINE1_POS0);
								U32LCD(n2);
								i=0;	    	
								while(str2[i])
								{	
									c=pos+i;
									if(c>=6&&c<16)
									{
										CmdLCD(GOTO_LINE1_POS0+c);
										CharLCD(str2[i]);
			         				}
									i++;
								}
								delay_ms(1000);
   		 				}	
						delay_ms(100);
						IOCLR0=1<<LED_yellow;
						CmdLCD(CLEAR_LCD);
		}
		else if(HOUR==ah2&&MIN==am2)
				{
							t2=1;
						for(pos=15;pos>=(6-(len2-1));pos--)
						{
								IOSET0=1<<BUZZER;
								delay_ms(500);
								IOCLR0=1<<BUZZER;
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("Train2 arrived");
								CmdLCD(GOTO_LINE1_POS0);
								U32LCD(n2);
								i=0;
								while(str2[i])
								{
									c=pos+i;
									if(c>=6&&c<16)
									{
										CmdLCD(GOTO_LINE1_POS0+c);
										CharLCD(str2[i]);
									}
									i++;
								}
							delay_ms(1000);
						}
						if(cnt2==0)
						IOSET0=1<<LED_green;
						else
						IOSET0=1<<LED_red;
			 	}
		  else if(HOUR==lh2&&MIN==lm2)
			  {
			   		t2=0;
			  for(pos=15;pos>=(6-(len2-1));pos--)
	    		{
						CmdLCD(CLEAR_LCD);
						IOSET0=1<<BUZZER;
				 	    CmdLCD(GOTO_LINE2_POS0);
					    StrLCD("Train2 leaving");
						//line1
						CmdLCD(GOTO_LINE1_POS0);
			       		U32LCD(n2);
				  	i=0;
	      			while(str2[i])
					{
       		 			c=pos+i;
         					if(c>=6&&c<16)
        					{
										CmdLCD(GOTO_LINE1_POS0+c);
		   		    					CharLCD(str2[i]);
							}
  								i++;
					}
					delay_ms(1000);
					}
			  		delay_ms(500);
			  		IOCLR0=1<<BUZZER;
						if(cnt2==0)
						IOCLR0=1<<LED_green;
					  	else
						IOCLR0=1<<LED_red;
						CmdLCD(CLEAR_LCD);
			  }


        /* Train 3: arrival-2 min through arrival */
        else if(train_window(ah3,am3))
        {
            //display_train(n3,pl3,ah3,am3);
			   //train3 display
		    for(pos=15;pos>=(6-(len3-1));pos--)
	    	{
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE2_POS0);
						CharLCD('p');
						U32LCD(pl3);
				   	   	CmdLCD(GOTO_LINE2_POS0+5);
						StrLCD("arr");
						CharLCD('-');
						CharLCD((ah3/10)+48);
						CharLCD((ah3%10)+48);
						CharLCD(':');
						CharLCD((am3/10)+48);
						CharLCD((am3%10)+48);
						IOSET0=1<<LED_yellow;
						CmdLCD(GOTO_LINE1_POS0);
			       		U32LCD(n3);
						i=0;
       		 		while(str3[i])
        			{
								c=pos+i;
	         				if(c>=6&&c<16)
								{
									CmdLCD(GOTO_LINE1_POS0+c);
		   		    				CharLCD(str3[i]);
								}
   							i++;
					}
						delay_ms(1000);
   		 	}
				delay_ms(100);
				IOCLR0=1<<LED_yellow;
				CmdLCD(CLEAR_LCD);
		}
		else if(HOUR==ah3&&MIN==am3)
				{
						t3=1;
					for(pos=15;pos>=(6-(len3-1));pos--)
						{
								IOSET0=1<<BUZZER;
								delay_ms(500);
								IOCLR0=1<<BUZZER;
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("Train3 arrived");
								CmdLCD(GOTO_LINE1_POS0);
								U32LCD(n3);
								i=0;
								while(str3[i])
								{
									c=pos+i;
									if(c>=6&&c<16)
									{
										CmdLCD(GOTO_LINE1_POS0+c);
										CharLCD(str3[i]);
									}
									i++;
								}
							delay_ms(1000);
						}
						if(cnt3==0)
						IOSET0=1<<LED_green;
						else
						IOSET0=1<<LED_red;
			 	}

		  else if(HOUR==lh3&&MIN==lm3)
			  {
			  		t3=0;
			  for(pos=15;pos>=(6-(len3-1));pos--)
	    		{
						CmdLCD(CLEAR_LCD);
						IOSET0=1<<BUZZER;
				 	    CmdLCD(GOTO_LINE2_POS0);
					    StrLCD("Train3 leaving");
						//line1
						CmdLCD(GOTO_LINE1_POS0);
		        		U32LCD(n3);
				  	i=0;
	       			while(str3[i])
						{
	      		 			c=pos+i;
         					if(c>=6&&c<16)
	       					{
										CmdLCD(GOTO_LINE1_POS0+c);
		   		    					CharLCD(str3[i]);
							}
  								i++;
						}
					delay_ms(1000);
				}
			  		delay_ms(500);
			  		IOCLR0=1<<BUZZER;
						if(cnt3==0)
						IOCLR0=1<<LED_green;
					  	else
						IOCLR0=1<<LED_red;
						CmdLCD(CLEAR_LCD);
			  }
        else
        {
		   CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("NO TRAIN");
			delay_ms(500);
        }
}
	 