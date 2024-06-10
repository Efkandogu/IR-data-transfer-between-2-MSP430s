#include "msp430.h"
#include "LCD.h" // LCD ba�l�k dosyas�
#include "strings.h"
#include "stdlib.h"
    int rx_data = 0;
char samples[10];
int main(void)
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;



    P1SEL = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // UART Ayarlar�, Saat kayna�� SMCLK
    UCA0BR0 = 104; // 1MHz 9600 bud ayar�
    UCA0BR1 = 0; // 1MHz 9600 baud ayar�
    UCA0MCTL = UCBRS0; // UART Baud hassas ayar
    UCA0CTL1 &= ~UCSWRST; // USCI birimini haz�rla
    IE2 |= UCA0RXIE; // USCI_A0 RX kesmesini a�
    __bis_SR_register(GIE); // Genel kesmeleri a� LPM0 moduna gir


    while (1)
    {
        LCD_Ayarla(); // Ba�lang��ta LCD ayarlar�n� yap.
        LCD_Git_XY(1,1); // Kurs�r� 1.sat�r 1.s�tuna g�t�r.
        LCD_Yazi_Yaz("Pot De�eri");
        LCD_Git_XY(2,1); // Kurs�r� 2.sat�r 1.s�tuna g�t�r.
        sprintf(samples,"%d",rx_data);
        LCD_Yazi_Yaz(samples);
    }
}

// USCIAAB0 RX Kesme vekt�r�
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
   rx_data = UCA0RXBUF;
}
