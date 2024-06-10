#include "msp430.h"
int sayac = 0;

int main(void)
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ; // Saat frekans� 1MHZ 'e ayarlan�yor.
    DCOCTL = CALDCO_1MHZ;

    P1SEL = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // UART Ayarlar�, Saat kayna�� SMCLK
    UCA0BR0 = 104; // 1MHz 9600 bud ayar�
    UCA0BR1 = 0; // 1MHz 9600 baud ayar�
    UCA0MCTL = UCBRS0; // UART Baud hassas ayar
    UCA0CTL1 &= ~UCSWRST; // USCI birimini haz�rla
    IE2 |= UCA0TXIE; // G�nderme kesmesini a�
    __bis_SR_register(GIE); // Genel kesmeleri a� LPM0 moduna gir

    while (1)
    {
        IE2 |= UCA0TXIE; // G�nderme kesmesini a�
        UCA0TXBUF = sayac++; // Al�nan karakteri geri g�nder
        _delay_cycles(1000000);
    }
}
// USCIAB0TX kesme vekt�r�
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{

    IE2 &= ~UCA0TXIE; // Evet ise g�nderme kesmesini kapat
}
