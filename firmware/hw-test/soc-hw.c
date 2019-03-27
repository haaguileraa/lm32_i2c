#include "soc-hw.h"
#include "fuente_6x8.h"


timer_st *timer0 = (timer_st *)  0x20000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
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
 *
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
*/

/***************************************************************************
 * I2C Functions
 */
 

 
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
   
   	 
   i2c0->TxRx=(addrReg); 				// 4 COMMAND/INDEX Byte
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


//msleep(1);
}



void send_command_display(uint8_t addrDev, uint8_t command){
	i2c_write(addrDev, DISPLAY_COMMAND, command);
}

void send_data_display(uint8_t addrDev, uint8_t dat){
	i2c_write(addrDev, DISPLAY_INDEX, dat);
}




void sec_on_display(void){
	send_command_display(DISPLAY_ADDR,0xAE); //OFF PANTALLA 
	send_command_display(DISPLAY_ADDR,0X20); // MODO DE DIRECCIONAMIENTO
	send_command_display(DISPLAY_ADDR,0x00);
	send_command_display(DISPLAY_ADDR,0xB0); // CUADRAR DIRECCIÓN INICIAL DE PAGINA
        send_command_display(DISPLAY_ADDR,0xC8); //OUTPUT SCAN COM DIRECTORY
        send_command_display(DISPLAY_ADDR,0x00); // --- SET LOW COLUMN ADDR ADDRES       
        send_command_display(DISPLAY_ADDR,0x10); // --- SET HIGH COLUMN ADDR
        send_command_display(DISPLAY_ADDR,0x40); // --- SET STAR LINE ADDR
        send_command_display(DISPLAY_ADDR,0x81); // SET CONTRAST
        send_command_display(DISPLAY_ADDR,0x3F); //
        send_command_display(DISPLAY_ADDR,0xA1); // SET SEGMENT RE-MAP. A1=addr 127 MAPPED
        send_command_display(DISPLAY_ADDR,0xA6); // SET DISPLAY MODE. A6=NORMAL, A7=INVERSE
        send_command_display(DISPLAY_ADDR,0xA8); // SET MUX RATIO
        send_command_display(DISPLAY_ADDR,0x3F);
        send_command_display(DISPLAY_ADDR,0xA4); // OUTPUT RAM TO DISPLAY
     //  send_command_display(DISPLAY_ADDR,0xA5); // ENTIRE DISPLAY ON
        send_command_display(DISPLAY_ADDR,0xD3); // DISPLAY OFFSET. 00= NO
        send_command_display(DISPLAY_ADDR,0x00);
        send_command_display(DISPLAY_ADDR,0xD5); //---SET DISPLAY CLOCK  DIVIDE RATIO /OSCILATOR
        send_command_display(DISPLAY_ADDR,0xF0); //-- SET DIVIDE RATIO
        send_command_display(DISPLAY_ADDR,0xD9); //SET PRE-CHARGUE PERIOD
        send_command_display(DISPLAY_ADDR,0x22);
        send_command_display(DISPLAY_ADDR,0xDA); //SET COM PINS 
        send_command_display(DISPLAY_ADDR,0x12);
        send_command_display(DISPLAY_ADDR,0xDB); //--SET VCOMH
        send_command_display(DISPLAY_ADDR,0x20); //0x20,0.77xVcc
        send_command_display(DISPLAY_ADDR,0x8D); //SET DC-DC ENABLE
        send_command_display(DISPLAY_ADDR,0x14); 
        send_command_display(DISPLAY_ADDR,0xAF); //ON PANTALLA
}



void clear_display(void){
uint8_t v, b;
        set_position(0x00, 0x00);
	for(b=1;b<9;b++){
          	for (v=1;v<129;v++) {
            		send_data_display(DISPLAY_ADDR, 0x00);
          	}
        }
	
}


void set_position(uint8_t posx, uint8_t posy){
	send_command_display(DISPLAY_ADDR,0x21); //Configurar el direccionamiento por columna
	send_command_display(DISPLAY_ADDR,posx); //start address
	send_command_display(DISPLAY_ADDR,0x7F); //end address
	send_command_display(DISPLAY_ADDR,0x22); //Configurar el direccionamiento por página
	send_command_display(DISPLAY_ADDR,posy); //start address
	send_command_display(DISPLAY_ADDR,0x07); //page address (datasheet p.36)
}

	




void i2c_char(uint8_t fila){
	
	uint8_t letra, j;
	  for(j = 6; j>0; j--){
          //for(j = 0; j<6; j++){
	    letra = fuente[fila][j];
            send_data_display(DISPLAY_ADDR, letra);
          }
}
      
void i2c_all_word(char* texto){

	//uint8_t mx = sizeof(texto);
	uint8_t l;

		//for(l=mx+1; texto[l]!='\0'; l--){
		for(l=0; texto[l]!='\0'; l++){
			i2c_char(texto[l]-32);	
			
					
			
	}
}

void print_bar(void){
	//clear_display();
	set_position(64,2); //190
	i2c_all_word("RAB");


}


	/*
	uint8_t k;
   
  	for(k = 0; texto[k] !='\0'; k++){   	
    		i2c_char(texto[k]-1); 
  	} //
} //*/

void gpio_configuration_dir(uint8_t pin, uint8_t inout){
	uint8_t val = gpio0 -> dir;
	if(inout) {
		gpio0 ->dir = val | (1 << (pin-1));
	} 
	else{
		gpio0 ->dir = val & (~(1 << (pin-1)));

	}
}

uint8_t gpio_get(uint8_t pin){

	uint8_t val = gpio0 -> gpio_io;
	return (val >> (pin-1))  & (0x01);

}

void gpio_put(uint8_t pin, uint8_t value){
	uint8_t val = gpio0 -> gpio_io;
	if (value){
		gpio0 -> gpio_io = val | (1<< (pin-1));
	}else {
		gpio0 -> gpio_io = val && (~(1<< (pin-1)));
		

}

}






   

