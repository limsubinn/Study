module master_regfiles (
    clk,
    n_rst,

	addr,
	wen,
	data,

    start,
	tx_cmd,
	tx_addr,
	tx_data
);

input 			clk;
input 			n_rst;

input  [7:0] 	addr;
input 			wen;
input  [7:0]	data;

output 			start;
output 			tx_cmd;
output [1:0]	tx_addr;
output [2:0]	tx_data;


parameter A_TX_START = 8'h00;
parameter A_TX_CMD   = 8'h01;
parameter A_TX_ADDR  = 8'h02;
parameter A_TX_DATA  = 8'h03;

reg 		r_tx_start;
reg 		r_tx_cmd;
reg [1:0]	r_tx_addr;
reg [2:0]	r_tx_data;

reg			tx_start_d;

always @(negedge n_rst or posedge clk)
    if(!n_rst) begin
    	r_tx_start <= 1'b0; 
    end
    else begin
		r_tx_start <= ((addr==A_TX_START)&&(wen))? data[0] : r_tx_start;
    end

always @(negedge n_rst or posedge clk)
    if(!n_rst) begin
    	tx_start_d <= 1'b0; 
    end
    else begin
		tx_start_d <= r_tx_start;
    end

assign start = ((r_tx_start== 1'b1)&&(tx_start_d == 1'b0))? 1'b1 : 1'b0;

always @(negedge n_rst or posedge clk)
    if(!n_rst) begin
    	r_tx_cmd <= 1'b0; 
    end
    else begin
		r_tx_cmd <= ((addr==A_TX_CMD)&&(wen))? data[0] : r_tx_cmd;
    end

assign tx_cmd = r_tx_cmd;

always @(negedge n_rst or posedge clk)
    if(!n_rst) begin
    	r_tx_addr <= 2'h0;
    end
    else begin
		r_tx_addr <= ((addr==A_TX_ADDR)&&(wen))? data[1:0] : r_tx_addr;
    end

assign tx_addr = r_tx_addr;

always @(negedge n_rst or posedge clk)
    if(!n_rst) begin
    	r_tx_data <= 1'b0;
    end
    else begin
		r_tx_data <= ((addr==A_TX_DATA)&&(wen))? data[2:0] : r_tx_data;
    end

assign tx_data = r_tx_data;


endmodule

