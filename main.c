#include  <msp430x14x.h>

unsigned char Seg_code[]={0xC0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
// SEG 数字0—9   共阳
unsigned char Seg_Wei[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};   
// 位选


void delay(unsigned int timer)
{
  for(;timer>0;timer--);
}


void WR_595(unsigned char Data)     //要写入的数据
{
   unsigned char i;
  
   for(i=0;i<8;i++)
   { 
     if(Data&0x80)
       P5OUT|=0x02;
     else  
       P5OUT&=0xfd;
    
                  
     P5OUT|=0x08;                   // SHCP=1;  上升沿
     P5OUT&=0xf7;                   // SHCP=0; 
     Data<<=1;                      //从高位开始取数据 
   } 
    P5OUT|=0x01;                    //STCP=1;
    P5OUT&=0xfe;                   // STCP=0;
}



void display()
{

   unsigned char i;
   for(i=0;i<8;i++)
   {
       WR_595(Seg_Wei[i]);
       WR_595(Seg_code[i]);
       
       P5OUT&=0xfe;  
       P5OUT|=0x01;                       //STCP=1;
   }


}

void main( void )
{
  
  WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer to prevent time out reset
  P5DIR=0x0b;                  // P5.0=STCP  P5.1=DS  P5.3=SHCP  为输出口         
  P5OUT&=0xf6;     
  P5SEL&=0xf6;

 
  while(1)
  { 
    display();
  }
}


 