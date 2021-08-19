module rcosine_02 (
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
reg [(DSIZE+1)-1:0] a0,a1,a2,a3;
reg [DSIZE-1:0] a4;
reg [(DSIZE*2+1)-1:0] b0,b1,b2,b3;
reg [(DSIZE*2)-1:0] b4;
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
 
always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   a0 <= {(DSIZE+1){1'b0}};
   a1 <= {(DSIZE+1){1'b0}};
   a2 <= {(DSIZE+1){1'b0}};
   a3 <= {(DSIZE+1){1'b0}};
   a4 <= {(DSIZE){1'b0}};
 end
 else begin
   a0 <= din + d7;
   a1 <= d0 + d6;
   a2 <= d1 + d5;
   a3 <= d2 + d4;
   a4 <= d3;
 end
 
always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   b0 <= {(DSIZE+1+8){1'b0}};
   b1 <= {(DSIZE+1+8){1'b0}};
   b2 <= {(DSIZE+1+8){1'b0}};
   b3 <= {(DSIZE+1+8){1'b0}};
   b4 <= {(DSIZE+8){1'b0}};
 end
 else begin
   b0 <= a0 * 8'h26;
   b1 <= a1 * 8'h36;
   b2 <= a2 * 8'h44;
   b3 <= a3 * 8'h50;
   b4 <= a4 * 8'h51;
 end
 
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
