module rcosine_03 (
  clk,
  n_rst,
  din_en,
  din,
  dout
);
parameter DSIZE=8;

input clk;
input n_rst;

input din_en;
input [DSIZE-1:0] din;
output reg [(DSIZE*2+3)-1:0] dout;

reg [2:0] sel, sel2;

reg [DSIZE-1:0] din1,d0,d1,d2,d3,d4,d5,d6,d7;
reg [(DSIZE+1)-1:0] a0,a1,a2,a3,a4;
reg [(DSIZE*2+1)-1:0] b0,b1,b2,b3;
reg [(DSIZE*2)-1:0] b4;
wire [(DSIZE*2+1+1)-1:0] c0,c1;
wire [(DSIZE*2+3)-1:0] d;

reg [DSIZE-1:0] mux1,mux2;
reg [(DSIZE+1)-1:0] mux3;
reg [7:0] mux4;

wire [(DSIZE+1)-1:0] adder;
wire [(DSIZE*2+1)-1:0] multiplier;

reg dout_en;

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   sel <= 3'h0;
 end
 else begin
   if (din_en) begin
     sel <= 3'h0;
   end
   else begin
     sel <= sel + 3'h1;
   end
 end

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   sel2 <= 3'h0;
 end
 else begin
   sel2 <= sel;
 end

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   din1 <= {(DSIZE){1'b0}};
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
  if (din_en) begin
   din1 <= din;
   d0 <= din1;
   d1 <= d0;
   d2 <= d1;
   d3 <= d2;
   d4 <= d3;
   d5 <= d4;
   d6 <= d5;
   d7 <= d6;
  end
 end
 
always @(sel,din1,d0,d1,d2,d3) //mux1 for adder
 case (sel)
  3'h0 : mux1 = din1;
  3'h1 : mux1 = d0;
  3'h2 : mux1 = d1;
  3'h3 : mux1 = d2;
  3'h4 : mux1 = d3;
  default : mux1 = {(DSIZE){1'b0}};
 endcase

always @(sel,d7,d6,d5,d4) //mux2 for adder
 case (sel)
  3'h0 : mux2 = d7;
  3'h1 : mux2 = d6;
  3'h2 : mux2 = d5;
  3'h3 : mux2 = d4;
  3'h4 : mux2 = {(DSIZE){1'b0}};
  default : mux2 = {(DSIZE){1'b0}};
 endcase

assign adder = mux1 + mux2;

always @(posedge clk or negedge n_rst) //demux1
 if (!n_rst) begin
  a0 <= {(DSIZE+1){1'b0}};
  a1 <= {(DSIZE+1){1'b0}};
  a2 <= {(DSIZE+1){1'b0}};
  a3 <= {(DSIZE+1){1'b0}};
  a4 <= {(DSIZE+1){1'b0}};
 end
 else begin
  case (sel)
   3'h0 : begin a0 <= adder; a1 <= a1; a2 <= a2; a3 <= a3; a4 <= a4; end
   3'h1 : begin a0 <= a0; a1 <= adder; a2 <= a2; a3 <= a3; a4 <= a4; end
   3'h2 : begin a0 <= a0; a1 <= a1; a2 <= adder; a3 <= a3; a4 <= a4; end
   3'h3 : begin a0 <= a0; a1 <= a1; a2 <= a2; a3 <= adder; a4 <= a4; end
   3'h4 : begin a0 <= a0; a1 <= a1; a2 <= a2; a3 <= a3; a4 <= adder; end
   default : begin a0 = {(DSIZE+1){1'b0}}; a1 = {(DSIZE+1){1'b0}}; a2 = {(DSIZE+1){1'b0}}; a3 = {(DSIZE+1){1'b0}}; a4 = {(DSIZE+1){1'b0}}; end
  endcase
 end

always @(sel2,a0,a1,a2,a3,a4) //mux3 for multiplier
 case (sel2)
  3'h0 : mux3 = a0;
  3'h1 : mux3 = a1;
  3'h2 : mux3 = a2;
  3'h3 : mux3 = a3;
  3'h4 : mux3 = a4;
  default : mux3 = {(DSIZE+1){1'b0}};
 endcase

always @(sel2) //mux4 for multiplier
 case (sel2)
  3'h0 : mux4 = 8'h26;
  3'h1 : mux4 = 8'h36;
  3'h2 : mux4 = 8'h44;
  3'h3 : mux4 = 8'h50;
  3'h4 : mux4 = 8'h51;
  default : mux4 = 8'h0;
 endcase

assign multiplier = mux3 * mux4;

always @(posedge clk or negedge n_rst) //demux2
 if (!n_rst) begin
  b0 <= {(DSIZE*2+1){1'b0}};
  b1 <= {(DSIZE*2+1){1'b0}};
  b2 <= {(DSIZE*2+1){1'b0}};
  b3 <= {(DSIZE*2+1){1'b0}};
  b4 <= {(DSIZE*2){1'b0}};
 end
 else begin
  case (sel2)
   3'h0 : begin b0 <= multiplier; b1 <= b1; b2 <= b2; b3 <= b3; b4 <= b4; end
   3'h1 : begin b0 <= b0; b1 <= multiplier; b2 <= b2; b3 <= b3; b4 <= b4; end
   3'h2 : begin b0 <= b0; b1 <= b1; b2 <= multiplier; b3 <= b3; b4 <= b4; end
   3'h3 : begin b0 <= b0; b1 <= b1; b2 <= b2; b3 <= multiplier; b4 <= b4; end
   3'h4 : begin b0 <= b0; b1 <= b1; b2 <= b2; b3 <= b3; b4 <= multiplier; end
   default : begin b0 <= {(DSIZE*2+1){1'b0}}; b1 <= {(DSIZE*2+1){1'b0}}; b2 <= {(DSIZE*2+1){1'b0}}; b3 <= {(DSIZE*2+1){1'b0}}; b4 <= {(DSIZE*2){1'b0}}; end
  endcase
 end

assign c0 = b0 + b1;
assign c1 = b2 + b3;
assign d = c0 + c1;

always@(posedge clk or negedge n_rst)
 if(!n_rst) begin
  dout_en <= 1'h0;
 end
 else begin
  if (sel2==3'h4) begin
   dout_en <= 1'h1;
  end
  else begin
   dout_en <= 1'h0;
  end
 end

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   dout <= {(DSIZE*2+3){1'b0}};
 end
 else begin
   if (dout_en) dout <= d + b4;
 end
endmodule