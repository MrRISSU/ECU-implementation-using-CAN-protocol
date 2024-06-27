#include"header_CAN2.h"
extern int flag;
void CAN2_RX_INTR_ISR(void) __irq{
	  flag=1;
	   ////////////////////////////////
   
    //int id=C2RID;
	  if(C2RID==0x3FA)
	 {
	 Rx_HL.id=C2RID;
	 Rx_HL.dlc=(C2RFS>>16)&0xF;
	 Rx_HL.rtr=(C2RFS>>30)&1;
	 if(Rx_HL.rtr==0)
	 {
	  Rx_HL.byteA=C2RDA;
	  Rx_HL.byteB=C2RDB;
	 }
	 }
	 else if(C2RID==0x3FB)
	 {
	 Rx_IND.id=C2RID;
	 Rx_IND.dlc=(C2RFS>>16)&0xF;
	 Rx_IND.rtr=(C2RFS>>30)&1;
	 if(Rx_IND.rtr==0)
	 {
	  Rx_IND.byteA=C2RDA;
	  Rx_IND.byteB=C2RDB;
	 }
	 }
	C2CMR=(1<<2); //Release recever Buffer
	///////////////////////////////
	VICVectAddr=0;
}


void can2_init()
{
int *p=(unsigned int*)0xE0038000;
 PINSEL1|=0x14000;
 VPBDIV=1; //PCLK=60Mhz
 C2MOD=0x1; //select reset mode
 C2BTR=0x001C001D; //speed 125kbps 
 AFMR=0x2;	 //Acceptance Filter is 
 
 *p=0x23FA23FB;//Accept only messages Havind ID= 0x3FA & 0x3FB
 SFF_sa=0x0;
 SFF_GRP_sa=EFF_sa=EFF_GRP_sa=ENDofTable=0x4;
 
 C2MOD=0x0; //disable reset mode
}

void CAN2_Rx_intr_config(void)
{
 VICIntSelect=0;
 VICVectCntl0=27|(1<<5);
 VICVectAddr0=(int)CAN2_RX_INTR_ISR;
 VICIntEnable=(1<<27);
 C2IER=0x1;//Enable Rx interrupt ox CAN2
}