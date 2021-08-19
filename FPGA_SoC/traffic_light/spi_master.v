module spi_master (
    clk,
    n_rst,

    start,
	tx_cmd,
	tx_addr,
	tx_data,
	
    spi_sclk,
    spi_mosi,
    spi_miso,
    spi_ss_n
);

input 		clk;
input 		n_rst;

input 		start;
input 		tx_cmd;
input [1:0] tx_addr;
input [2:0]	tx_data;

output 		spi_sclk;
output 		spi_mosi;
input  		spi_miso;
output 		spi_ss_n;

parameter S_IDLE   = 4'h0;
parameter S_ACTIVE = 4'h1;
parameter S_END    = 4'h9;

reg [6:0] 	mosi;
reg 		ss_n;
reg [3:0]	cnt;

always @(negedge n_rst or posedge clk)
    if(!n_rst) begin
        cnt <= S_IDLE;
    end
    else begin
        cnt <= (ss_n==1'b0)? cnt + 4'h1 : S_IDLE;
    end

always @(negedge n_rst or posedge clk)
	if(!n_rst) begin
		ss_n <= 1'b1;
		mosi <= 7'h00;
	end
	else begin
		ss_n <= (start==1'b1)? 1'b0 :
				(cnt == S_END)? 1'b1 : ss_n;
		mosi <= (cnt == S_ACTIVE)? {1'b1,tx_cmd,tx_addr,tx_data} :
			    (ss_n==1'b0)? {mosi[5:0],1'b0} : 7'h00;
	end

assign spi_mosi = mosi[6];
assign spi_ss_n = ss_n;
assign spi_sclk = clk;

endmodule

