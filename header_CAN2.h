#include <LPC21xx.H>

typedef unsigned int U32;
typedef unsigned short int U16;
typedef unsigned char U8;

typedef struct CAN2_MSG
{
U16 id:11;
U8 dlc:4;
U8 rtr:1;
U32 byteA;
U32 byteB;
}MSG;
extern MSG HL_Tx,IND_Tx;
extern U8 HL_flag,R_IND_flag,L_IND_flag;

#define TCS ((C2GSR>>3)&1)
#define START_TX (1<<0)
#define SELECT_TX_BUF1 (1<<5)

extern MSG Rx_HL,Rx_IND;

extern void can2_init(void);
extern void can2_tx(MSG V);
extern void CAN2_Rx_intr_config(void);
extern void delay_ms(U32);	
extern void INTR_init(void);
/*extern void lcd_cmd(U8);
extern void lcd_data(U8);
extern void lcd_init(void);
extern void lcd_string(char const *);
*/