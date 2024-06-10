#include "msp430.h"
#include "LCD.h" // LCD baþlýk dosyasý
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
    UCA0CTL1 |= UCSSEL_2; // UART Ayarlarý, Saat kaynaðý SMCLK
    UCA0BR0 = 104; // 1MHz 9600 bud ayarý
    UCA0BR1 = 0; // 1MHz 9600 baud ayarý
    UCA0MCTL = UCBRS0; // UART Baud hassas ayar
    UCA0CTL1 &= ~UCSWRST; // USCI birimini hazýrla
    IE2 |= UCA0RXIE; // USCI_A0 RX kesmesini aç
    __bis_SR_register(GIE); // Genel kesmeleri aç LPM0 moduna gir


    while (1)
    {
        LCD_Ayarla(); // Baþlangýçta LCD ayarlarýný yap.
        LCD_Git_XY(1,1); // Kursörü 1.satýr 1.sütuna götür.
        LCD_Yazi_Yaz("Pot Deðeri");
        LCD_Git_XY(2,1); // Kursörü 2.satýr 1.sütuna götür.
        sprintf(samples,"%d",rx_data);
        LCD_Yazi_Yaz(samples);
    }
}

// USCIAAB0 RX Kesme vektörü
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
   rx_data = UCA0RXBUF;
}
