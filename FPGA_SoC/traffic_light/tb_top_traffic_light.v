`timescale 1ns/1ps

`define T_CLK 10.0
module tb_top_traffic_light;

reg clk;
reg sclk;
reg n_rst;
reg sensor;
wire [2:0] t_g_wait;
wire [2:0] t_r_wait;

wire [1:0] main_light;
wire [1:0] country_light;
//wire [2:0] s_data;
//wire [1:0] s_addr;
initial begin
	sclk = 1'b1;
	clk = 1'b1;
	n_rst = 1'b0;

	#(`T_CLK) n_rst = 1'b1;
end

always #(`T_CLK/2) sclk = ~sclk;
always #(`T_CLK/8) clk = ~clk;

assign t_r_wait = 3'h2;
assign t_g_wait = 3'h5;

wire 		spi_sclk;
wire 		spi_mosi;
wire  		spi_miso;
wire 		spi_ss_n;

reg [7:0] addr;
reg 	  wen;
reg [7:0] data;

parameter A_TX_START = 8'h00;
parameter A_TX_CMD   = 8'h01;
parameter A_TX_ADDR  = 8'h02;
parameter A_TX_DATA  = 8'h03;
parameter A_T_R_WAIT = 2'h0;
parameter A_T_G_WAIT = 2'h1;

initial begin
	addr = A_TX_CMD;
	wen = 1'b0;
	data = 8'h0;
	sensor = 1'b0;
	wait(n_rst == 1'b1);
	#(`T_CLK * 0.1);
	#(`T_CLK * 4) addr = A_TX_CMD;
			  wen = 1'b1;
			  data = {7'h00,1'b1};
	#(`T_CLK) addr = A_TX_ADDR;
			  wen = 1'b1;
			  data = {6'h00,A_T_R_WAIT}; 
	#(`T_CLK) addr = A_TX_DATA;
			  wen = 1'b1;
			  data = {5'h00,t_r_wait};
	#(`T_CLK) addr = A_TX_START;
			  wen = 1'b1;
			  data = {7'h00,1'b1};
	#(`T_CLK*2) addr = A_TX_START;
			  wen = 1'b1;
			  data = {7'h00,1'b0};	
			  
	#(`T_CLK) wen = 1'b0;

	wait(u_top_traffic_light.t_r_wait == t_r_wait);

	#(`T_CLK * 4) addr = A_TX_CMD;
			  wen = 1'b1;
			  data = {7'h00,1'b1};
	#(`T_CLK) addr = A_TX_ADDR;
			  wen = 1'b1;
			  data = {6'h00,A_T_G_WAIT}; 
	#(`T_CLK) addr = A_TX_DATA;
			  wen = 1'b1;
			  data = {5'h00,t_g_wait};
	#(`T_CLK) addr = A_TX_START;
			  wen = 1'b1;
			  data = {7'h00,1'b1};
	#(`T_CLK*2) addr = A_TX_START;
			  wen = 1'b1;
			  data = {7'h00,1'b0};		
	#(`T_CLK) wen = 1'b0;

	wait(u_top_traffic_light.t_g_wait== t_g_wait);

	#(`T_CLK) sensor = 1'b0;
	#(`T_CLK * 4) sensor = 1'b1;
	#(`T_CLK * 15) sensor = 1'b0;	
	#(`T_CLK * 12) $stop;
end

master u_master(
	.clk(sclk),
	.n_rst(n_rst),

	.addr(addr),
	.wen(wen),
	.data(data),
	
    .spi_sclk(spi_sclk),
    .spi_mosi(spi_mosi),
    .spi_miso(spi_miso),
    .spi_ss_n(spi_ss_n)
);

top_traffic_light u_top_traffic_light(
    .clk(clk),
    .spi_sclk(spi_sclk),
    .n_rst(n_rst),
    
    .spi_mosi(spi_mosi),
    .spi_ss_n(spi_ss_n),
    .spi_miso(spi_miso),

    .sensor(sensor),
    .main_light(main_light),
   .country_light(country_light)
    
);




/*
spi_slave u_spi_slave(
	.clk(clk),
	.n_rst(n_rst),
	.addr(s_addr),
	.data(s_data),
	
    .spi_sclk(spi_sclk),
    .spi_mosi(spi_mosi),
    .spi_miso(spi_miso),
    .spi_ss_n(spi_ss_n)

	//.sensor(sensor),
	//.main_light(main_light),
	//.country_light(country_light)
);
*/
endmodule


