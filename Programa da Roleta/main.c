
#include "io430.h"
#define ROLETAS 3
char rol[ROLETAS];
unsigned char cod[]={0X3F,0X21,0X76,0X73,0X69,0X5B,0X5F,0X31,0X7F,0X7B};

/*---------------------------------------------------------------------------
Função: Configura_IOs
Descrição: Configura os I/Os.
Entrada: -
Saída: -
---------------------------------------------------------------------------*/
void Configura_IOs (void)
{
  P1SEL&=0x00;
  P2SEL&=0x00;
  P1DIR|=0X03;
  P1DIR&=0xC7;
  P1REN|=0XF8;
  P1OUT|=0xFB;
  P2DIR|=0X7F;
}
/*---------------------------------------------------------------------------
Função: Zera_Roletas
Descrição: Zera os elementos do vetor ROLETAS.
Entrada: *roletas (quantidade de roletas)
Saída: -
---------------------------------------------------------------------------*/
void Zera_Roletas (char *roletas)
{
  int cont;
  for(cont=0; cont<ROLETAS; cont++)
  roletas[cont]=0;
}
/*---------------------------------------------------------------------------
Função: Total
Descrição: Soma os elementos do vetor ROLETAS.
Entrada: *roletas (quantidade de roletas)
Saída: soma (total das roletas)
---------------------------------------------------------------------------*/
char Total (char *roletas)
{
  char soma=0;
  int cont;
  
  for(cont=0; cont<ROLETAS; cont++)
  soma=soma+roletas[cont];
  
  return(soma);
}
/*------------------------------------------------------------------------------
NOME: Mostra_Display
DESCRICAO: Apresenta em dois displays de 7 segmentoso valor da dezena e unidade
           de qualquer número de 2 dígitos decimal
ENTRADA: valor (número em hexadecimal que será mostrado)
SAIDA: -                
------------------------------------------------------------------------------ */	
void Mostra_Display(unsigned char valor)
{
  unsigned char unidade=valor,dezena=0;
  while(unidade > 9)
	{
  	dezena=dezena+1;
	unidade=unidade-10;
	}
  P1OUT&=0XFE;
  P1OUT&=0XFD;
  P1OUT|=0X01;
  P2OUT=cod[unidade];
  __delay_cycles(10000);
  
  P1OUT&=0XFE;
  P1OUT&=0XFD;
  P1OUT|=0X02;
  P2OUT=cod[dezena];
  __delay_cycles(10000);
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  Configura_IOs();                              // configura I/Os
  
  Zera_Roletas(rol);                            // chama sub-rotina que zerará as roletas
  char total=Total(rol);                        // cria variável que informará o total
  unsigned char valor=0;                        // zera o valor a ser mostrado no display
  
  while(total<=99)                              // enquanto o total for menor ou igual a 99
    {  
   // Leitura das roletas
      
      switch(P1IN&0x38)
      {
      case 0x18:                                // ROL0 pressionado
          total++;                              // incrementa o valor total
          __delay_cycles(150000);               // tempo de repique
          rol[0]++;                             // incrementa o valor da roleta 1
          __delay_cycles(150000);               // tempo de repique
          break;
          
      case 0x28:                                // ROL1 pressionado
          total++;                              // incrementa o valor total
          __delay_cycles(150000);               // tempo de repique
          rol[1]++;                             // incrementa o valor da roleta 2
          __delay_cycles(150000);               // tempo de repique
          break;

      case 0x30:                                // ROL2 pressionado
          total++;                              // incrementa o valor total
          __delay_cycles(150000);               // tempo de repique
          rol[2]++;                             // incrementa o valor da roleta 3
          __delay_cycles(150000);               // tempo de repique
          break;
      }
      
   // Leitura das chaves p/ exibição no display
      
      switch(P1IN&0xC0)
      {
      case 0x40:                                // apenas SEL0 selecionado
        valor=rol[0];                           // envia o valor da roleta 1 para o display
        Mostra_Display(valor);
        break;
      
      case 0x80:                                // apenas SEL1 selecionado
        valor=rol[1];                           // envia o valor da roleta 2 para o display
        Mostra_Display(valor);
        break;
      
      case 0xC0:                                // ambas as chaves selecionadas
        valor=rol[2];                           // envia o valor da roleta 3 para o display
        Mostra_Display(valor);
        break;
      
      case 0x00:                                // nenhuma das chaves selecionadas
        valor=Total(rol);                       // envia o valor total das roletas para o display
        Mostra_Display(valor);
        break;
      }
    }
   // Mostra dois 'X' no display, indicando que o limite foi atingido
  
  P1OUT&= 0xFE;
  P1OUT&= 0xFD;
  P2OUT=0x6D;
  __delay_cycles(10000);
  P1OUT|= 0x01;
  P1OUT|= 0x02;
  P2OUT=0x6D;
 __delay_cycles(10000); 
 
  }