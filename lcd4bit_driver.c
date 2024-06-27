#include<LPC21xx.h>
#include"header_CAN2.h"
#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)


void lcd_cmd(unsigned char cmd){
int temp;
IOCLR1=0xFE0000;
temp=(cmd&0xF0)<<16;
IOSET1=temp;
IOCLR1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;

IOCLR1=0xFE0000;
temp=(cmd&0x0F)<<20;
IOSET1=temp;
IOCLR1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;

}
void lcd_data(unsigned char data){
int temp;
IOCLR1=0xFE0000;
temp=(data&0xF0)<<16;
IOSET1=temp;
IOSET1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;

IOCLR1=0xFE0000;
temp=(data&0x0F)<<20;
IOSET1=temp;
IOSET1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;
}

void lcd_init(void){
IODIR1|=0xFE0000;
PINSEL2|=0x0;
lcd_cmd(0x03);
lcd_cmd(0x02);
lcd_cmd(0x28);
//lcd_cmd(0x0E);
lcd_cmd(0x01);
}
void lcd_string(char *p)
{
while(*p){
lcd_data(*p);
p++;
}
}
/*
void lcd_integer(int num)
{
int arr[10];
int i=0;
if(num==0){
lcd_data('0');
return;
}
		   if(num<0){
		   lcd_data('-');
		   num=-num;
		   }
while(num>0){
arr[i]=(num%10)+48;
i++;
num=num/10;
}
for(i--;i>=0;i--)
 lcd_data(arr[i]);

}
*/ 
void cgram_init(char const *p)
{
unsigned int i;
lcd_cmd(0x40);
for(i=0;i<32;i++)
{
lcd_data(p[i]);
}
}
// void lcd_float(float f)
//{
//unsigned char buf[10];
//sprintf(buf,"%.1f",f);
//lcd_string(buf);
//} */

























