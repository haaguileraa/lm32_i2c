module TouchPrimitivePP (Pin, Op_gpio, SS);
	 
  input [6:0] Pin; //Vector de entradas tamaño Opciones GPIO del 1 al 7 serán enviados a la pantalla
  reg Op_gpio=0; //Opciones enviadas a la pantalla
  output SS =1'b1; //Señal de salida, siempre en 1 para tener una referencia de salida

  always @ ( * ) begin

/*
Estructura general
always @ ( sensitivity list )
	statement;
Whenever the event in the sensitivity list occurs, the statement is executed
*/

    case (Pin)
                    		           
			7'b1000000: Op_gpio = 1; // Opción 1
			7'b0100000: Op_gpio = 2; // Opción 2
      			7'b0010000: Op_gpio = 3; // Opción 3
      			7'b0001000: Op_gpio = 4; // Opción 4
      			7'b0000100: Op_gpio = 5; // Opción 5
      			7'b0000010: Op_gpio = 6; // Opción 6
      			7'b0000001: Op_gpio = 7; // Opción 7


                default:
      			Op_gpio = 0; // Opción 0
		endcase
	end

endmodule


