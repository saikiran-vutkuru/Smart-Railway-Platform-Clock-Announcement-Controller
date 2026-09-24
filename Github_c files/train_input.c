#include <LPC21xx.H>
#include "types.h"
#include "lcd(2).h"
#include "lcd_defines(2).h"
#include "kpm(2).h"
#include "kpm_defines.h"
#include "delay.h"
//#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16 //@p1.16
extern char week[][4];
//rtc variables
extern u32 H,M,S,D,MON,Y,DW,a,b,z;
//train1
extern 	u32 n1,a1,d1,pl1,ah1,am1,lh1,lm1;
//train2
extern	u32 n2,a2,d2,pl2,ah2,am2,lh2,lm2;
//train 3
extern	u32 n3,a3,d3,pl3,ah3,am3,lh3,lm3;
//leds count
extern u32 cnt1,cnt2,cnt3;
void eint0_isr(void) __irq
{
	u32 password;
	u32 p=301;
	input3:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.RTC  2.TRAIN");
	CmdLCD
	(GOTO_LINE2_POS0);
	a=ReadNum();
	CmdLCD(CLEAR_LCD);
	if(a==1)
	{
		g1:CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("1.HOUR 2.MIN");
     	CmdLCD(GOTO_LINE2_POS0);
       z=ReadNum();
    	CmdLCD(CLEAR_LCD);
    if(z==1)
		{
		r1:	CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("hours:");
		H=ReadNum();
		  if (H==1)
		      goto r1;
		}
	else if(z==2)
		{
		r2:CmdLCD(CLEAR_LCD);
     CmdLCD(GOTO_LINE1_POS0);
  	StrLCD("mins:");
 		M=ReadNum();
		    if (M==1)
		      goto r2;
			}
		else
		{
			CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("wrong selection ");
				delay_ms(500);
				goto g1;
		}
     	HOUR=H;
    	MIN=M;
	    CCR=1<<0;
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("UPDATED RTC");
		delay_ms(1000);
		CmdLCD(CLEAR_LCD);
	}
	else if(a==2)
{
		input2:CmdLCD(CLEAR_LCD);
		//trains inputs starting
		CmdLCD(GOTO_LINE1_POS0);
    StrLCD("PASSWORD:");
    CmdLCD(GOTO_LINE2_POS0);
    password=ReadNum();
    if(password==p)
    {
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("1.train 2.train");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("3.train");
			CmdLCD(GOTO_LINE2_POS0+9);
			b=ReadNum();


			if(b==1)
			{
				//train1
				//arrive time
				cnt1++;
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("train1 arrive");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Time");
				delay_ms(500);

				r4:CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("arrive hours:");	  
          CmdLCD(GOTO_LINE2_POS0);
         		ah1=ReadNum();
           if(ah1==1)
				    goto r4;

				r5:CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("arrive min:")	;  
				CmdLCD(GOTO_LINE2_POS0);
				am1=ReadNum(); 
				   if(am1==1)
				    goto r5;
				a1=ah1*100+am1;
				CmdLCD(CLEAR_LCD);

				 //levaving time
	  			CmdLCD(CLEAR_LCD);
			    CmdLCD(GOTO_LINE1_POS0);
 			    StrLCD("train1 leaving");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("time");
 			   delay_ms(500);
 			   r6:CmdLCD(CLEAR_LCD);
			   CmdLCD(GOTO_LINE1_POS0);
			  StrLCD("leave hours:");	  
			  CmdLCD(GOTO_LINE2_POS0);
			  lh1=ReadNum();
			     if(lh1==1)

				    goto r6;
		      r7:CmdLCD(CLEAR_LCD);
			  CmdLCD(GOTO_LINE1_POS0);
		 	  StrLCD("leave min:")	;  
			  CmdLCD(GOTO_LINE2_POS0);
			  lm1=ReadNum();
			  if(lm1==1)
				    goto r7; 

			  d1=lh1*100+lm1;
			  //updated
			  CmdLCD(CLEAR_LCD);
			  CmdLCD(GOTO_LINE2_POS0);
		    	StrLCD("train1 updated");
		    	delay_ms(1000);
		    	CmdLCD(CLEAR_LCD);
			}
			else if(b==2)
			{
				//train2
				//train2 arrive time
				cnt2++;
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("train2 arriving");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("time");
				delay_ms(500);
				r8:CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("arrive hours:");	  
				CmdLCD(GOTO_LINE2_POS0);
				ah2=ReadNum();
				  if(ah2==1)

				    goto r8;

				r9:CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("arrive min:");  
				CmdLCD(GOTO_LINE2_POS0);

				am2=ReadNum();
				 if(am2==1)
				    goto r9; 

				a2=ah2*100+am2;
				CmdLCD(CLEAR_LCD);
				//train2 leaving
				 CmdLCD(CLEAR_LCD);
	 		 	CmdLCD(GOTO_LINE1_POS0);
      			StrLCD("train2 leaving");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("time");
 	  			delay_ms(500);

 	  			r11:CmdLCD(CLEAR_LCD);
 	  			CmdLCD(GOTO_LINE1_POS0);
	  			StrLCD("leave hours:");	  
	  			CmdLCD(GOTO_LINE2_POS0);
	  			lh2=ReadNum();
				  if(lh2==1)
				    goto r11;

      			r12:CmdLCD(CLEAR_LCD);
 	  			CmdLCD(GOTO_LINE1_POS0);
 	  			StrLCD("leave min:")	;  
	  			CmdLCD(GOTO_LINE2_POS0);
	  			lm2=ReadNum();
				if(lm2==1)
				    goto r12; 
	  			d2=lh2*100+lm2;
				//train2 updated
				 CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("train2 updated");
				delay_ms(1000);
				CmdLCD(CLEAR_LCD);
			}
			else if(b==3)
			{
				//train3
				//train3 arrive time
				cnt3++;
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("train3 arriving");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("time");
				delay_ms(500);

				r13:CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("arrive hours:");	  
				CmdLCD(GOTO_LINE2_POS0);
				ah3=ReadNum();
				   if(ah3==1)
				    goto r13;

				r14:CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("arrive min:")	;  
				CmdLCD(GOTO_LINE2_POS0);
				am3=ReadNum();
				if(am3==1)
				    goto r14; 

				a3=ah3*100+am3;
				CmdLCD(CLEAR_LCD);


				//train2 leaving


				 CmdLCD(CLEAR_LCD);
	  			CmdLCD(GOTO_LINE1_POS0);
      			StrLCD("train3 lev tim:");
 	  			delay_ms(500);
 	  			r15:CmdLCD(CLEAR_LCD);
 	  			CmdLCD(GOTO_LINE1_POS0);
	  			StrLCD("leave hours:");	  
	  			CmdLCD(GOTO_LINE2_POS0);
	  			lh3=ReadNum();
				if(lh3==1)
				    goto r15;

      			r16:CmdLCD(CLEAR_LCD);
 	  			CmdLCD(GOTO_LINE1_POS0);
 	  			StrLCD("leave min:")	;  
	  			CmdLCD(GOTO_LINE2_POS0);
	  			lm3=ReadNum();
				   if(lm3==1)
				    goto r16; 

	  			d3=lh3*100+lm3;
				//train3 updated
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("train3 updated");
			delay_ms(1000);
			CmdLCD(CLEAR_LCD);
			}
		}
			 else 
			{
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("wrong password");
				delay_ms(500);
				goto input2;
			}
		}
	  else{
        		CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("wrong selection ");
				delay_ms(500);
				goto input3;
}
 	VICVectAddr=0;
   //clear eint0 status in EIP
    EXTINT=1<<0;

} 
//keypad input

void input1(void)
{
    InitLCD();
	Init_KPM();
	 r17:CmdLCD(CLEAR_LCD);
	INPUTH1:CmdLCD(GOTO_LINE1_POS0);
	StrLCD("hours:");
	H=ReadNum();
	if(H==1)
		goto r17;
	if(H>23)
	{
	CmdLCD(CLEAR_LCD);
	StrLCD("wrong input");
	delay_ms(500);
	CmdLCD(CLEAR_LCD);
	goto INPUTH1;
	}

	r18:CmdLCD(CLEAR_LCD);
	INPUTM1:CmdLCD(GOTO_LINE1_POS0);
	StrLCD("mins:");
    M=ReadNum();
	if(M==1)
		goto r18;
	if(M>60)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("wrong input");
		delay_ms(500);
		CmdLCD(CLEAR_LCD);
		goto INPUTM1;
	}

	r19:CmdLCD(CLEAR_LCD);
	INPUTS1:CmdLCD(GOTO_LINE1_POS0);
	StrLCD("secs:");
	S=ReadNum();
	 if(S==1)
		goto r19;
	if(S>60)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("wrong input");
		delay_ms(500);
		CmdLCD(CLEAR_LCD);
		goto INPUTS1;
	}

	r21:CmdLCD(CLEAR_LCD);
	INPUTD1:CmdLCD(GOTO_LINE1_POS0);
	StrLCD("date of mon:");
	D=ReadNum();
	if(D==1)
		goto r21;
			if(D<1&&M>31)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("wrong input");
		delay_ms(500);
		CmdLCD(CLEAR_LCD);
		goto INPUTD1;
	}
	r22:CmdLCD(CLEAR_LCD);
	INPUTMON1:CmdLCD(GOTO_LINE1_POS0);
	StrLCD("month:");
	MON=ReadNum();
	if(MON==1)
		goto r22;
    if(MON<1&&MON>12){
		CmdLCD(CLEAR_LCD);
		StrLCD("wrong input");
		delay_ms(500);
		CmdLCD(CLEAR_LCD);
		goto INPUTMON1;
	}

	r23:CmdLCD(CLEAR_LCD);
	INPUTY1:CmdLCD(GOTO_LINE1_POS0);
	StrLCD("year:");
	Y=ReadNum();
	 if(Y==1)
		goto r23;
	if(Y<1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("wrong input");
		delay_ms(500);
		CmdLCD(CLEAR_LCD);
		goto INPUTY1;
	}
	r20:CmdLCD(CLEAR_LCD);
	INPUTDW1:CmdLCD(GOTO_LINE1_POS0);
	StrLCD("week:");
	DW=ReadNum();
	 if(DW==1)
		goto r20;
	if(DW<1&&DW>7)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("wrong input");
		delay_ms(500);
		CmdLCD(CLEAR_LCD);
		goto INPUTDW1;
	}}
void input2(void)
{	
	u32 password;
	u32 p=301;
//	InitLCD();
//	Init_KPM();

	input1:CmdLCD(CLEAR_LCD)	;
   //trains inputs starting
	CmdLCD(GOTO_LINE1_POS0);
    StrLCD("PASSWORD:");
    CmdLCD(GOTO_LINE2_POS0);
    password=ReadNum();
    if(password==p)
    {
	  //train1 
      r24:CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train1 num:");
	  CmdLCD(GOTO_LINE2_POS0);
	  n1=ReadNum();
	   if(n1==1)
		goto r24;

	  //arrive time
	  CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train1 ar time:");
 	  delay_ms(500);

 	  r25:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("arrive hours:");	  
	  CmdLCD(GOTO_LINE2_POS0);
	  ah1=ReadNum();
	   if(ah1==1)
		goto r25;
      r26:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
 	  StrLCD("arrive min:")	;  
	  CmdLCD(GOTO_LINE2_POS0);
	  am1=ReadNum();
	   if(am1==1)
		goto r26; 
	  a1=ah1*100+am1;
	  //levaving time

	  CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train1 lev tim:");
 	  delay_ms(500);
 	  r27:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("leave hours:");	  
	  CmdLCD(GOTO_LINE2_POS0);
	  lh1=ReadNum();
	   if(lh1==1)
		goto r27;

      r28:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
 	  StrLCD("leave min:")	;  
	  CmdLCD(GOTO_LINE2_POS0);
	  lm1=ReadNum();
	   if(lm1==1)
		goto r28; 
	  d1=lh1*100+lm1;
	  //platform
	  r29:CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train1 pf no:");
	  CmdLCD(GOTO_LINE2_POS0);
	  pl1=ReadNum();
	   if(pl1==1)
		goto r29;
	  //train2 

	  r31:CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train2 num:");
	  CmdLCD(GOTO_LINE2_POS0);
	  n2=ReadNum();
	   if(n2==1)
		goto r31;
	  //train2 arrive time
      CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train2 ar time:");
 	  delay_ms(500);

 	  r32:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("arrive hours:");	  
	  CmdLCD(GOTO_LINE2_POS0);
	  ah2=ReadNum();
	   if(ah2==1)
		goto r32;

      r33:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
 	  StrLCD("arrive min:")	;  
	  CmdLCD(GOTO_LINE2_POS0);
	  am2=ReadNum();
	     if(am2==1)
		   goto r33; 
	  a2=ah2*100+am2;

	  //train2 leaving time
	  CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train2 lev tim:");
 	  delay_ms(500);

 	  r34:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("leave hours:");	  
	  CmdLCD(GOTO_LINE2_POS0);
	  lh2=ReadNum();
	   if(lh2==1)
		goto r34;
      r35:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
 	  StrLCD("leave min:")	;  
	  CmdLCD(GOTO_LINE2_POS0);
	  lm2=ReadNum();
	   if(lm2==1)
		goto r35; 
	  d2=lh2*100+lm2;

	  //train2 platform
	  r36:CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train2 pf no:");
	  CmdLCD(GOTO_LINE2_POS0);
	  pl2=ReadNum();
	   if(pl2==1)
		goto r36;
	  //train3
	  r37:CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train3 num:");
	  CmdLCD(GOTO_LINE2_POS0);
	  n3=ReadNum();
	   if(n3==1)
		goto r37;
	  //train3 arrive time
	  	  CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train3 ar time:");
 	  delay_ms(500);
 	  r38:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("arrive hours:");	  
	  CmdLCD(GOTO_LINE2_POS0);
	  ah3=ReadNum();
	   if(ah3==1)
		goto r38;

      r39:CmdLCD(CLEAR_LCD);
     CmdLCD(GOTO_LINE1_POS0);
     StrLCD("arrive min:")	;  
     CmdLCD(GOTO_LINE2_POS0);
	  am3=ReadNum();
	   if(am3==1)
		goto r39; 
	  a3=ah3*100+am3;
	  //train3 leave time
	  CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
     StrLCD("train3 lev tim:");
     delay_ms(500);
     r41:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
	  StrLCD("leave hours:");	  
	  CmdLCD(GOTO_LINE2_POS0);
	  lh3=ReadNum();
	   if(lh3==1)
		goto r41;

      r42:CmdLCD(CLEAR_LCD);
 	  CmdLCD(GOTO_LINE1_POS0);
 	  StrLCD("leave min:")	;  
	  CmdLCD(GOTO_LINE2_POS0);
	  lm3=ReadNum();
	  	   if(lm3==1)
		goto r42; 

	  d3=lh3*100+lm3;
	  //train3 platform
      r43:CmdLCD(CLEAR_LCD);
	  CmdLCD(GOTO_LINE1_POS0);
      StrLCD("train3 pf no:");
	  CmdLCD(GOTO_LINE2_POS0);
	  pl3=ReadNum();
	   if(pl3==1)
		goto r43;  
		  }
	  else 
	  {
	    CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
	  	StrLCD("wrong password");
		delay_ms(500);
	  	goto input1;
	  }
}
