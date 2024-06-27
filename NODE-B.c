#include"header_CAN2.h"
#define HL (1<<17)
#define L_IND (1<<18)
#define R_IND (1<<19)
#define BUSSER (1<<21)
MSG Rx_HL,Rx_IND;
int flag=0;


main()
{
unsigned char cgram[]={0x00,0x04,0x0C,0x1F,0x1F,0x0C,0x04,0x00,0x00,0x04,0x06,0x1F,0x1f,0x06,0x04,0x00,0x00,0x11,0x0E,0x0A,0x0A,0x0E,0x11,0x00,0,0,0,0,0,0,0,0};
IODIR0|=HL|L_IND|R_IND|BUSSER;	  //Output Dir.
IOSET0=HL|L_IND|R_IND;
can2_init();
CAN2_Rx_intr_config();
lcd_init();
lcd_string("HL   R-IND L-IND");
cgram_init(cgram);
while(1)
 {
  if(flag)
  {
    flag=0;
	if(Rx_HL.id==0x3FA)
	{
	 if(Rx_HL.byteA==0xAA)
	 {
		  lcd_cmd(0xC0);
		  lcd_data(2);
	 	  IOCLR0=HL;
	 }
	 else if(Rx_HL.byteA==0xBB)
	 {
	  IOSET0=HL;
	  lcd_cmd(0xC0);
	  lcd_data(3);	 

	 }
	}
	 if(Rx_IND.id==0x3FB)
	{
	 
	 if(Rx_IND.byteA==0xCC)
	 {
	  IOSET0=R_IND;
	  lcd_cmd(0xCC);
	  lcd_data(3);
	 
	  while(flag==0)
	  {
	    lcd_cmd(0xCC);
	    lcd_data(0);
	   IOCLR0=L_IND|BUSSER;
	   delay_ms(500);
	   IOSET0=L_IND|BUSSER;
	   lcd_cmd(0xCC);
	    lcd_data(3);
	   delay_ms(500);

	  }
	 }
	 else if(Rx_IND.byteA==0xDD)
	 {
	  IOSET0=L_IND;
	  IOCLR0=BUSSER;
	  lcd_cmd(0xCC);
	  lcd_data(3); 
	   
	 }
	 else if(Rx_IND.byteA==0xEE)
	 {
	  IOSET0=L_IND;	
	  IOSET0=R_IND;
	  lcd_cmd(0xCC);
	  lcd_data(3);
	  
	  while(flag==0)
	  {
	  lcd_cmd(0xC6);
	  lcd_data(1); 
	   IOCLR0=R_IND|BUSSER;
	   delay_ms(500);
	   IOSET0=R_IND|BUSSER;
	   lcd_cmd(0xC6);
	   lcd_data(3); 
	   delay_ms(500);
	  }
	 }
	 else if(Rx_IND.byteA==0xFF)
	 {
	  IOSET0=R_IND;
	  IOCLR0=BUSSER;
	  lcd_cmd(0xC6);
	  lcd_data(3); 
	 }
	}
  }
 }

}