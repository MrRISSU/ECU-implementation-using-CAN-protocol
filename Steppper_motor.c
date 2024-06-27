#include <LPC21xx.H>
int i,j,k;
unsigned int var1;

void clock_wise()
{
var1=0x80;
for(i=0;i<=3;i++)
{
var1<<=1;
IOCLR0|=0xF00;
IOSET0=var1;
delay_ms(10);
//for(k=0;k<3000;k++);
}
}
/////////////////
void anti_clock_wise()
{
var1=0x1000;
for(i=0;i<=3;i++)
{
var1>>=1;
IOCLR0=0xF00;
IOSET0=var1;
delay_ms(10);
//for(k=0;k<3000;k++);
}
}
///////////
int main()
{
IODIR0|=0xF00;
IOCLR0=0xF00;
while(1)
{
for(j=0;j<270;j++)
clock_wise();
delay_ms(1000);
//for(k=0;k<65000;k++);
for(j=0;j<270;j++)
anti_clock_wise();
delay_ms(1000);
//for(k=0;k<65000;k++);
}
}