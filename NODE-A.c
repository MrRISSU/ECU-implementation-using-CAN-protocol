 #include "header_CAN2.h"
 MSG HL_Tx,IND_Tx;
 U8 HL_flag=0,R_IND_flag=0,L_IND_flag=0;
 int main()
 {
 
  HL_Tx.id=0x3FA;
  HL_Tx.dlc=1;
  HL_Tx.rtr=0;
  IND_Tx.id=0x3FB;
  IND_Tx.dlc=1;
  IND_Tx.rtr=0;
 
   can2_init();
   INTR_init();

  while(1){
  //Dummy while
	 	 
  }
}



