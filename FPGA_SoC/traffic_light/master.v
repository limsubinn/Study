module master (
    clk,
    n_rst,

	addr,
	wen,
	data,
	
    spi_sclk,
    spi_mosi,
    spi_miso,
    spi_ss_n
);

input 		clk;
input 		n_rst;

input  [7:0] 	addr;
input 			wen;
input  [7:0]	data;

output 		spi_sclk;
output 		spi_mosi;
input  		spi_miso;
output 		spi_ss_n;

wire 		start;
wire 		tx_cmd;
wire [1:0]      tx_addr;
wire [2:0]	tx_data;

master_regfiles u_master_regfiles (
    .clk(clk), 
	.n_rst(n_rst),

	.addr(addr),
	.wen(wen),
	.data(data),

    .start(start),
	.tx_cmd(tx_cmd),
	.tx_addr(tx_addr),
	.tx_data(tx_data)
);

spi_master u_spi_master (
    .clk(clk), 
	.n_rst(n_rst),

    .start(start),
	.tx_cmd(tx_cmd),
	.tx_addr(tx_addr),
	.tx_data(tx_data),
	
    .spi_sclk(spi_sclk),
    .spi_mosi(spi_mosi),
    .spi_miso(spi_miso),
    .spi_ss_n(spi_ss_n)
);

endmodule

