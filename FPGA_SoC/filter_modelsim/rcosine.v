module rcosine (
  clk,
  n_rst,
  din,
  dout
);

parameter DSIZE=8;

input clk;
input n_rst;
input [DSIZE-1:0] din;

reg [DSIZE-1:0] d0,d1,d2,d3,d4,d5,d6,d7;
wire [(DSIZE+1)-1:0] a0,a1,a2,a3;
wire [(DSIZE*2+1)-1:0] b0,b1,b2,b3;
wire [(DSIZE*2)-1:0] b4;
wire [(DSIZE*2+1+1)-1:0] c0,c1;
wire [(DSIZE*2+3)-1:0] d;

output reg [(DSIZE*2+3)-1:0] dout;

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   d0 <= {(DSIZE){1'b0}};
   d1 <= {(DSIZE){1'b0}};
   d2 <= {(DSIZE){1'b0}};
   d3 <= {(DSIZE){1'b0}};
   d4 <= {(DSIZE){1'b0}};
   d5 <= {(DSIZE){1'b0}};
   d6 <= {(DSIZE){1'b0}};
   d7 <= {(DSIZE){1'b0}};
 end
 else begin
   d0 <= din;
   d1 <= d0;
   d2 <= d1;
   d3 <= d2;
   d4 <= d3;
   d5 <= d4;
   d6 <= d5;
   d7 <= d6;
 end

assign a0 = din + d7;
assign a1 = d0 + d6;
assign a2 = d1 + d5;
assign a3 = d2 + d4;

assign b0 = a0 * 8'h26;
assign b1 = a1 * 8'h36;
assign b2 = a2 * 8'h44;
assign b3 = a3 * 8'h50;
assign b4 = d3 * 8'h51;

assign c0 = b0 + b1;
assign c1 = b2 + b3;

assign d = c0 + c1;

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   dout <= {(DSIZE*2+3){1'b0}};
 end
 else begin
   dout <= d + b4;
 end

endmodule  

