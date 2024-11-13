#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "KEYPAD_int.h"
#include "KEYPAD_Cfg.h"


#define F_CPU  8000000
#include <util/delay.h>


int main(void)
{
	DIO_Init();
	LCD_Init();
	
	c8 str1[20]="Basic Calculator";
	LCD_WriteStringCursor(0,0,str1);
  	 LCD_SetCursor(1,0);
	LCD_WriteString("by Omar Mohamed");
	_delay_ms(200);
	LCD_Clear();  
	
	u8 flag =0, k, op =0;
	u32 num1 =0, num2 =0,  res =0;
	
	while (1)
	{
		k= KEYPAD_GetKey();
		
				 if (k>='0' && k<='9' && flag == 0)
				 {
					  LCD_WriteChar(k);
					  num1 =num1 *10+ (k-'0');
			 }
		 switch ( k )
		 {
			 case '+' :
			 LCD_WriteChar('+');
			 flag=1;
			 op ='+';
			 break ;
			 case '-':
			 LCD_WriteChar('-');
			 flag=1;
			 op = '-';
			 break ;
			 case '*':
			 LCD_WriteChar('*');
			 flag=1;
			 op ='*';
			 break;
			 case '/':
			 LCD_WriteChar('/');
			 flag=1;
			 op='/';
			 break;	 
		 }
		 
		 if ( k>= '0' && k <= '9' && flag == 1)
		 {
			 LCD_WriteChar(k);
			 num2 =  num2 * 10 + (k - '0');
		 }	 
	
		 if (k=='=')
		{
			LCD_SetCursor(1,6);
			  switch (op)
			  {
				  case '+' :
				  res = (num1 + num2) ;
				  break ;
				  case '-':
				  res = (num1 - num2);
				  break ;
				  case '*':
				  res = (num1 * num2);
				  break;
				  case '/':
				  if ( num2 == 0)
				  {
					  LCD_WriteString("ERROR");
				  }
				  else
				  {
					  res = (num1 / num2);
				  }
				  break;
			  }
			  LCD_WriteNumber(res);	
			  
			 
			  
		}
		 if (k == 'c'){
			 k ='T' ;
			 num1 = 0;
			 num2 = 0;
			 flag = 0;
			 res = 0;
			 op = 0;
			 LCD_Clear();
			 LCD_SetCursor(0,0);
			 
		 
		 }
		 }
	}