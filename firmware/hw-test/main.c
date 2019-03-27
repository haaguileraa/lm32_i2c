#include "soc-hw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "fuente_6x8.h"


int main(void)
{
//  uint8_t j, n, letra; 

  
 
  	i2c_init();
  	sec_on_display();
  	
  	set_position(0,0);
	i2c_all_word("INITRAM");
  	 
  	clear_display();
  	
  	set_position(4,6);
	i2c_all_word("INITRAM");
  	
  	
	/*
	while(1){
	
	set_position(4,6);
	i2c_char(49);
	
	} // */
	
	
	while(1){
	//	set_position(2,2);
	//	i2c_all_word("INITRAM");
	print_bar();
	msleep(5000);
	 
	
       }
        
          
     
        if(gpio_get(0)){
        	clear_display();
       		set_position(4,6);
		i2c_all_word("REC");
		msleep(3000);
        }
        else if(gpio_get(1)){
        	clear_display();
        	set_position(4,6);
		i2c_all_word("ELA");
		msleep(3000);
        }
        else if(gpio_get(2)){
        	clear_display();
        	set_position(4,6);
		i2c_all_word("ABUC");
		msleep(3000);
        }
        else if(gpio_get(3)){
        	clear_display();
        	set_position(4,6);
		i2c_all_word("NOR");
		msleep(3000);
        }
        else if(gpio_get(4)){
        	clear_display();
        	set_position(4,6);
		i2c_all_word("INAM");
		msleep(3000);
        }
        else if(gpio_get(5)){
        	clear_display();
        	set_position(4,6);
		i2c_all_word("TRAM");
		msleep(3000);
        }
        else if(gpio_get(6)){
        	clear_display();
        	set_position(4,6);
		i2c_all_word("AUGA");
		msleep(3000);
        }
        else{
        	clear_display();
        	set_position(4,6);
		i2c_all_word("RIDEP");
		
        }
        
        
        }
        
      
      
      
      
      
     





















 /* n = 53;
	  for(j = 0; j<6; j++){
            letra = fuente[n][j];
            send_data_display(DISPLAY_ADDR, letra);
            //i2c_write(DISPLAY_ADDR,DISPLAY_INDEX,letra);
           
          }
        }  // */
