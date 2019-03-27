//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module i2c_master_wb_top_TB;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 2;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
reg [2:0] wb_adr;
reg  stb, cyc,we;
reg [7:0] wb_dati;

//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------

i2c_master_wb_top uut(.wb_clk_i(clk), .wb_rst_i(rst), .arst_i(1), .wb_adr_i(wb_adr), .wb_dat_i(wb_dati), .wb_we_i(we), .wb_stb_i(stb), .wb_cyc_i(cyc));


/* Clocking device */
initial begin
         clk <= 0;
cyc=0;
stb=0;
rst=1;
#(2*tck) rst=0;
end
always #(tck/2) clk <= ~clk;

initial begin

// config prescale low
wb_adr = 00; 
wb_dati =8'h0A;
we=1;   //flujo de datos (1: R, 0: W)
#(5*tck);
cyc=1;
stb=1;
#(5*tck);
cyc=0;
stb=0;

// config prescale  HI
wb_adr = 01; 
wb_dati =8'h00;
we=1;
#(8*tck);
cyc=1;
stb=1;
#(5*tck);
cyc=0;
stb=0;


// config ctr 
wb_adr = 02; 
wb_dati =8'h80;
we=1;
#(8*tck);
cyc=1;
stb=1;
#(8*tck);
cyc=0;
stb=0;

// config tx
wb_adr = 03; 
wb_dati =8'h85;
we=1;
#(8*tck);
cyc=1;
stb=1;
#(5*tck);
cyc=0;
stb=0;


// config cr 
wb_adr = 04; 
wb_dati =8'h90;
we=1;
#(5*tck);
cyc=1;
stb=1;
#(8*tck);
cyc=0;
stb=0;


// config sr (3)
wb_adr = 04; 
we=1;
#(10*tck);
cyc=1;
stb=1;
#(8*tck);
cyc=0;
stb=0;


//  tx
wb_adr = 03; 
wb_dati =8'h3C;
we=1;
#(8*tck);
cyc=1;
stb=1;
#(5*tck);
cyc=0;
stb=0;



// config cr (5)
wb_dati =8'h10;
we=1;
#(5*tck);
cyc=1;
stb=1;
#(8*tck);
cyc=0;
stb=0;

// config sr (6)
wb_adr = 04; 
we=1;
#(10*tck);
cyc=1;
stb=1;
#(8*tck);
cyc=0;
stb=0;

//  tx
wb_adr = 03; 
wb_dati =8'h41;
we=1;
#(8*tck);
cyc=1;
stb=1;
#(5*tck);
cyc=0;
stb=0;















end

/* Simulation setup */
initial begin



	$dumpfile("i2c_master_wb_top_TB.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, uut);
	//$dumpvars(-1,clk,rst,uart_txd);
	// reset

	#(tck*500000) $finish;
end



endmodule
