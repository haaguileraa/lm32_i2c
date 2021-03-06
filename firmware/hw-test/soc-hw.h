#ifndef SPIKEHW_H
#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x400
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000

#define FCPU      100000000

//#define UART_RXBUFSIZE 32



/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit

/****************************************************************************
 * Interrupt handling
 */
typedef void(*isr_ptr_t)(void);

void     irq_enable();
void     irq_disable();
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak();

void     isr_init();
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);

/****************************************************************************
 * General Stuff
 */
void     halt();
void     jump(uint32_t addr);


/****************************************************************************
 * Timer
 */
#define TIMER_EN     0x08    // Enable Timer
#define TIMER_AR     0x04    // Auto-Reload
#define TIMER_IRQEN  0x02    // IRQ Enable
#define TIMER_TRIG   0x01    // Triggered (reset when writing to TCR)

typedef struct {
	volatile uint32_t tcr0;
	volatile uint32_t compare0;
	volatile uint32_t counter0;
	volatile uint32_t tcr1;
	volatile uint32_t compare1;
	volatile uint32_t counter1;
} timer_st;

void msleep(uint32_t msec);
void nsleep(uint32_t nsec);

void prueba();
void tic_init();


/***************************************************************************
 * GPIO0
 */
typedef struct {
	volatile uint32_t gpio_io;
	volatile uint32_t dir;

} gpio_t;

/***************************************************************************
 * UART0
 */
#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar(char c);
void uart_putstr(char *str);
char uart_getchar();

/***************************************************************************
 * SPI0
 */

typedef struct {
   volatile uint32_t rxtx;
   volatile uint32_t run;
   volatile uint32_t cs;
   volatile uint32_t nop2;
   volatile uint32_t divisor;
} spi_t;

void spi_init();
void spi_putchar(char c);
char spi_getchar();


/***************************************************************************
 * I2C0
 */
#define I2C_TIP 0x02
#define DISPLAY_ADDR	0X3C
#define DISPLAY_COMMAND	0X00
#define DISPLAY_INDEX	0X40
typedef struct {
   volatile uint8_t PRERlo;
   volatile uint8_t PRERhi;
   volatile uint8_t ctr;
   volatile uint8_t TxRx;
   volatile uint8_t crsr;
} i2c_t;
void i2c_init();
void i2c_write(char addrDev, char addrReg, char dat);


/* 
Funciones Display
*/
void clear_display(void);
void set_position(uint8_t posx, uint8_t posy);
void send_command_display(uint8_t addrDev, uint8_t command);
void send_data_display(uint8_t addrDev, uint8_t dat);
void sec_on_display(void);
void i2c_char(uint8_t fila);
void i2c_all_word(char* texto);
void print_bar(void);

//char i2c_read();


/***************************************************************************



/*** gpio functions 
****/

void gpio_configuration_dir(uint8_t pin, uint8_t inout);
void gpio_put(uint8_t pin, uint8_t val);
uint8_t gpio_get(uint8_t pin);


/* Pointer to actual components
 */
extern timer_st  *timer0;
extern gpio_t	 *gpio0;
//extern uart_t   *uart0; 
extern i2c_t   *i2c0; 
extern uint32_t *sram0; 

#endif // SPIKEHW_H
