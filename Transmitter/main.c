#include "msp430.h"
int sayac = 0;

int main(void)
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ; // Saat frekansý 1MHZ 'e ayarlanýyor.
    DCOCTL = CALDCO_1MHZ;

    P1SEL = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // UART Ayarlarý, Saat kaynaðý SMCLK
    UCA0BR0 = 104; // 1MHz 9600 bud ayarý
    UCA0BR1 = 0; // 1MHz 9600 baud ayarý
    UCA0MCTL = UCBRS0; // UART Baud hassas ayar
    UCA0CTL1 &= ~UCSWRST; // USCI birimini hazýrla
    IE2 |= UCA0TXIE; // Gönderme kesmesini aç
    __bis_SR_register(GIE); // Genel kesmeleri aç LPM0 moduna gir

    while (1)
    {
        IE2 |= UCA0TXIE; // Gönderme kesmesini aç
        UCA0TXBUF = sayac++; // Alýnan karakteri geri gönder
        _delay_cycles(1000000);
    }
}
// USCIAB0TX kesme vektörü
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{

    IE2 &= ~UCA0TXIE; // Evet ise gönderme kesmesini kapat
}
