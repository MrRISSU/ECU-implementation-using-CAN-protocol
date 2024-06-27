#include "header_CAN2.h"

void can2_init()
{
PINSEL1|=0x14000;
VPBDIV=1; //PCLK=60Mhz
C2MOD=0x1; //select reset mode
C2BTR=0x001C001D; //speed 125kbps
AFMR=0x00;	 //Didn't Accept any messages
C2MOD=0x0; //disable reset mode
}
////EINT0
void HL_SW_ISR(void) __irq
{
  HL_flag=!HL_flag;
   if(HL_flag){
    HL_Tx.byteA=0xAA;
	can2_tx(HL_Tx);
    }
   else if(HL_flag==0){
    HL_Tx.byteA=0xBB;
	can2_tx(HL_Tx);
  	}
 EXTINT|=0x1;
 VICVectAddr=0;
}
////EINT1 
void R_IND_SW_ISR(void) __irq
{
  R_IND_flag=!R_IND_flag;
   if(R_IND_flag)
   {
    L_IND_flag=0;
    IND_Tx.byteA=0xCC;
    can2_tx(IND_Tx);
   }
   else if(R_IND_flag==0)
   {
    IND_Tx.byteA=0xDD;
	can2_tx(IND_Tx);
   }
 EXTINT=0x2;
 VICVectAddr=0;
}
////EINT2
void L_IND_SW_ISR(void) __irq
{
 L_IND_flag=!L_IND_flag;
   if(L_IND_flag)
    {
	 R_IND_flag=0;
	 IND_Tx.byteA=0xEE;
	 can2_tx(IND_Tx);
	}
   else if(L_IND_flag==0)
   {
	IND_Tx.byteA=0xFF;
	can2_tx(IND_Tx);
   }
 EXTINT=0x4;
 VICVectAddr=0;
}


void INTR_init()
{
PINSEL0|=0XA0000000;
PINSEL1|=0X1;//EINT0 selected
VICIntSelect=0;
VICVectCntl0=14|1<<5;
VICVectCntl1=15|1<<5;
VICVectCntl2=16|1<<5;
VICVectAddr0=(int)HL_SW_ISR;
VICVectAddr1=(int)R_IND_SW_ISR;
VICVectAddr2=(int)L_IND_SW_ISR;
VICIntEnable=(1<<14)|(1<<15)|(1<<16);
									 
EXTMODE=0X7;
EXTPOLAR=0x0;

}



void can2_tx(MSG Tx)
{
C2TID1=Tx.id;
C2TFI1=(Tx.dlc<<16);
if(Tx.rtr==0){	   //if Data frame
C2TFI1&=~(1<<30);
C2TDA1=Tx.byteA;
C2TDB1=Tx.byteB;
}
else if(Tx.rtr==1){ //if Remote Frame
C2TFI1=1<<30;
}
C2CMR=START_TX|SELECT_TX_BUF1;//
while(TCS==0);	  //waitin till Transmit complete
}


