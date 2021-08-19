module read_regfiles (
  clk,
  n_rst,

  done,
  r_data,
  r_addr,

  done_sync2,

  r_en,
  ren_ack,

  t_r_wait,
  t_g_wait
  
);

input clk;
input n_rst;

input done;
input ren_ack;
input [2:0] r_data;

output reg r_en;
output reg [1:0] r_addr;

reg done_sync1;
output reg done_sync2;
reg ack_sync1;
reg ack_sync2;

output reg [2:0] t_r_wait;
output reg [2:0] t_g_wait;

reg cnt;

always @(posedge clk or negedge n_rst) 
 if (!n_rst) begin
   cnt <= 1'h0;
 end
 else begin
   if (!cnt) cnt <= (ack_sync2)? cnt + 1'h1 : cnt;
 end
 
 
always @(posedge clk or negedge n_rst) 
 if (!n_rst) begin
   done_sync1 <= 1'h0;
 end
 else begin
   done_sync1 <= (done)? done : 1'h0;
end
                            
always @(posedge clk or negedge n_rst) 
 if (!n_rst) begin
   done_sync2 <= 1'h0;
 end
 else begin
   done_sync2 <= (done_sync1)? done_sync1 : 1'h0;
 end 


always @(posedge clk or negedge n_rst) 
 if (!n_rst) begin
   r_addr <= 2'h3;
 end
 else begin
   if (done_sync2) r_addr <= (!cnt)? 2'h0 :
                              (cnt)? 2'h1 : r_addr;
  // r_addr <= (done_sync2)? cnt : r_addr;
 end

always @(posedge clk or negedge n_rst) 
 if (!n_rst) begin
   r_en <= 1'h0;
 end
 else begin
   r_en <= (ack_sync2)? 1'h0 :
       (done_sync2)? 1'h1 : r_en;
   
   /*
   (ack_sync2)? 1'h0 :
           (r_addr != 2'h3)? 1'h1 : r_en;
           */
 end
 
always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   ack_sync1 <= 1'h0;
 end
 else begin
   ack_sync1 <= (ren_ack)? ren_ack : 1'h0;
 end

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   ack_sync2 <= 1'h0;
 end
 else begin
   ack_sync2 <= (ack_sync1)? ack_sync1 : 1'h0;
 end

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   t_r_wait <= 3'h0;
 end
 else begin
   t_r_wait <= (r_addr==2'h0)&&(ack_sync2)? r_data : t_r_wait;
 end 

always @(posedge clk or negedge n_rst)
 if (!n_rst) begin
   t_g_wait <= 3'h0;
 end
 else begin
   t_g_wait <= (r_addr==2'h1)&&(ack_sync2)? r_data : t_g_wait;
 end 


endmodule 

