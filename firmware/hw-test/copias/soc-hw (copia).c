#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_st *timer0 = (timer_st *)  0x40000000;
i2c_t   *i2c0   = (i2c_t *)    0x60000000;

isr_ptr_t isr_table[32];

void tic_isr();
/***************************************************************************
 * IRQ handling
 */
void isr_null()
{
}

void irq_handler(uint32_t pending)
{
	int i;

	for(i=0; i<32; i++) {
		if (pending & 0x01) (*isr_table[i])();
		pending >>= 1;
	}
}

void isr_init()
{
	int i;
	for(i=0; i<32; i++)
		isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
	isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
	isr_table[irq] = &isr_null;
}

/***************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


uint32_t tic_msec;

void tic_isr()
{
	tic_msec++;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init()
{
	tic_msec = 0;

	// Setup timer0.0
	timer0->compare0 = (FCPU/10000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

	isr_register(1, &tic_isr);
}


/***************************************************************************
 * UART Functions
 */
void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}


/***************************************************************************
 * I2C Functions
 */
 
void set_position(uint8_t posx, uint8_t posy){
	send_command_display(DISPLAY_ADDR,0x21); //Configurar el direccionamiento por columna
	send_command_display(DISPLAY_ADDR,posx);
	send_command_display(DISPLAY_ADDR,0x7F);
	send_command_display(DISPLAY_ADDR,0x22); //Configurar el direccionamiento por página
	send_command_display(DISPLAY_ADDR,posy);
	send_command_display(DISPLAY_ADDR,0x07);
};
 
 
void i2c_init()
{
	i2c0->PRERlo = 0x00; //0x00
	i2c0->PRERhi = 0x0A; //0x0A
	i2c0->ctr = 0x80;
}


void i2c_write(char addrDev, char addrReg, char dat)
{



   i2c0->TxRx=((addrDev<<1) +0);	 		// 1 7'bite slave address + bit r/w 
   i2c0->crsr =0x90;					// 2
   
   while(((i2c0->crsr)& I2C_TIP)) ; 			// 3 
  // while(((i2c0->crsr<<6)>>7));	 
   i2c0->TxRx=(addrReg); 				// 4 Control Byte
   i2c0->crsr =0x10;     				// 5
   while(((i2c0->crsr)& I2C_TIP));  			// 6
   
   i2c0->TxRx=(dat);  					// 7 Data Byte
   i2c0->crsr =0x10; 					// 8
   while(((i2c0->crsr)& I2C_TIP)); 			// 9


//........... todo byte 70 9

//Repeat steps 7 to 9

   i2c0->TxRx=(dat);  					// 7 Data Byte
   i2c0->crsr =0x10; 					// 8
   while(((i2c0->crsr)& I2C_TIP)); 			// 9


   i2c0->TxRx=(dat); 					// 11 Data Byte
   i2c0->crsr =0x50;					// 12
   while(((i2c0->crsr)& I2C_TIP));			// 12

 //Comandos prendido pantalla #107
/*	i2c0->TxRx=0xAE;
	i2c0->crsr =0x10; 					// 8
	while(((i2c0->crsr)& I2C_TIP)); 

	i2c0->TxRx=0x20;
	i2c0->crsr =0x10; 					// 8
	while(((i2c0->crsr)& I2C_TIP)); 

	i2c0->TxRx=0x00;
	i2c0->crsr =0x10; 					// 8
	while(((i2c0->crsr)& I2C_TIP)); 

	i2c0->TxRx=0xB0;
	i2c0->crsr =0x10; 					// 8
	while(((i2c0->crsr)& I2C_TIP)); 

	i2c0->TxRx=0xC8;
	i2c0->crsr =0x10; 					// 8
	while(((i2c0->crsr)& I2C_TIP)); 
	
	i2c0->TxRx=0x00;
	i2c0->crsr =0x10; 					// 8
	while(((i2c0->crsr)& I2C_TIP)); 

*/
}
