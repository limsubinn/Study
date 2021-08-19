`timescale 1ns/1ps
`define T_CLK 10
module tb_rcosine;

parameter DSIZE = 8;

reg clk, n_rst;
reg fast_clk;

reg din_en;

initial begin
 clk = 1'b0;
 fast_clk = 1'b0;
 n_rst = 1'b0;

 #(`T_CLK*3.2) n_rst = 1'b1;
end

always #(`T_CLK/2) clk = ~clk;
always #(`T_CLK/10) fast_clk = ~fast_clk;

always @(negedge n_rst or posedge fast_clk)
 if(!n_rst) begin
  din_en <= 1'b0;
 end
 else begin
  #(`T_CLK/5) din_en <= 1'b1;
  #(`T_CLK/5) din_en <= 1'b0;
  #(`T_CLK/5) din_en <= 1'b0;
  #(`T_CLK/5) din_en <= 1'b0;
  #(`T_CLK/5) din_en <= 1'b0;
 end

reg [7:0] cnt;
wire [DSIZE-1:0] din;
wire [DSIZE*2-1+3:0] dout, dout_02, dout_03;

always @(negedge n_rst or posedge clk)
 if(!n_rst) begin
  cnt <= 8'h00;
 end
 else begin
  cnt <= cnt + 8'h01;
 end

assign din = (cnt < 8'h10)?  {(DSIZE){1'b0}} :
    (cnt <= 8'h10)? {{(DSIZE-1){1'b0}},1'b1} :
    (cnt <= 8'h1F)? {(DSIZE){1'b0}} :
    {1'b0,cnt[6:0]};

initial begin
 wait(cnt == 8'hFF);
 $stop;
end  

rcosine #(.DSIZE(DSIZE)) u_rcosine (
 .clk (clk),
 .n_rst (n_rst),
 .din (din),
 .dout(dout)
);

rcosine_02 #(.DSIZE(DSIZE)) u_rcosine_02 (
 .clk (clk),
 .n_rst (n_rst),
 .din (din),
 .dout(dout_02)
);

rcosine_03 #(.DSIZE(DSIZE)) u_rcosine_03 (
 .clk (fast_clk),
 .n_rst (n_rst),
 .din_en (din_en),
 .din (din),
 .dout (dout_03)
);

endmodule 

