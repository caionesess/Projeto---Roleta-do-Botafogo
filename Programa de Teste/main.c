
#include "io430.h"
/*----------------------------------------------------------------------------
NOME: Conta
DESCRICAO: Conta de 0 a 65535.
ENTRADA: -
SAIDA: -
-----------------------------------------------------------------------------*/
void Conta(void)
{
unsigned int cont=0xFFFF;
while(cont!=0)
cont=cont-1;
}

/*----------------------------------------------------------------------------
NOME: PUSH
DESCRICAO: Testa os push bottons e mostra no display a sua numeração.
ENTRADA: -
SAIDA: -
-----------------------------------------------------------------------------*/
void PUSH (void) 
{
  switch(P1IN&0X38)                    // lê os push bottons
  {   
 case (0x18):                          // roleta 1(ROL0)
  P2OUT=0X21;                          // mostra 1 no display 
  Conta();
  P2OUT&=0x00;
    break;
    
 case (0x28):                          // roleta 2 (ROL1)       
  P2OUT=0X76;                          // mostra 2 no display
  Conta();
  P2OUT&=0x00;
    break;
    
 case (0x30):                          // roleta 3 (ROL2) 
  P2OUT=0X73;                          // mostra 3 no display
  Conta();
  P2OUT&=0x00;
    break;
  
 case (0x38):                          // nenhuma roleta
  P2OUT=0X3F;                          // mostra 0 no display
  Conta();
    break;
  }
}

int main( void )
{
// Stop watchdog timer to prevent time out reset
WDTCTL = WDTPW + WDTHOLD;

    P1SEL&=0X00;
    P2SEL&=0X00;
    P1REN|=0XF8;                        // habilita os resistores de pull up/down
    P1DIR|=0X03;                        // configura os pinos (transistores) como saída
    P1DIR&=0X07;                        // configura os pinos (switch) como entrada
    P2DIR|=0X7F;                        // configura os displays
    P1OUT|=0XFB;

while(1)
  {
  switch(P1IN&0XC0)                     // lê as duas chaves 
    {
  case (0X00):                          // sel0 = 0 e sel1 = 0
    PUSH();
    P2OUT&=0x00;                        // zera display 
    break;
    
  case (0X40):                          // sel1 = 1
    P2OUT=0X21;                         // mostra 1 no display 
    Conta();
    P2OUT&=0X00;                        // zera display
    break;
    
  case (0X80):                          // sel0 = 1
    P2OUT=0X76;                         // mostra 2 no display
    Conta();
    P2OUT&=0X00;                        // zera display 
    break;
    
  case (0XC0):                          // sel0 = 1 e sel1 = 1
    P2OUT=0X73;                         // mostra 3 no display
    Conta();
    P2OUT&=0X00;                        // zera display 
    break;
    }  
  }
}