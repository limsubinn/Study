module slave_regfiles (
   spi_sclk,
   n_rst,

   addr,
   wen,
   data,
   
/////////////////////////////////////////////

   r_en,
   r_addr,

   done_sync2,

   r_data,
   done,

   ren_ack

);

input spi_sclk;
input n_rst;

input [1:0] addr;
input [2:0] data;
input       wen;

reg [2:0] t_r_wait;
reg [2:0] t_g_wait;

parameter A_T_R_WAIT = 2'h0;
parameter A_T_G_WAIT = 2'h1;

reg [1:0] addr_d;
reg wen_d;

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
      addr_d <= 2'h0;
    end
    else begin
      addr_d <= addr;
    end

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
      wen_d <= 1'h0;
    end
    else begin
      wen_d <= wen;
    end


always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
     t_r_wait <= 1'h0;
    end
    else begin
     t_r_wait <= ((addr_d==A_T_R_WAIT)&&(wen_d))? data : t_r_wait;
    end

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
     t_g_wait <= 1'h0;
    end
    else begin
     t_g_wait <= ((addr_d==A_T_G_WAIT)&&(wen_d))? data : t_g_wait;
    end
    
////////////////////////////////////////////////////////////////////////
input r_en;
input [1:0] r_addr;

//input done_sync1;
input done_sync2;

output reg [2:0] r_data;
output reg done;

reg ren_sync1;
reg ren_sync2;

output reg ren_ack;

    
always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
     done <= 1'h0;
    end
    else begin
     done <=  (wen_d)? 1'h1 : 
         (done_sync2)? 1'h0 : done;
    end

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
     ren_sync1 <= 1'h0;
    end
    else begin
     ren_sync1 <= (r_en)? 1'h1 : 1'h0;
    end

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
     ren_sync2 <= 1'h0;
    end
    else begin
     ren_sync2 <= ren_sync1;
    end

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
     r_data <= 3'h0;
    end
    else begin
     if (ren_sync2) begin
      r_data <= (r_addr==A_T_R_WAIT)? t_r_wait : 
                (r_addr==A_T_G_WAIT)? t_g_wait :
                r_data;
     end
    end

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
     ren_ack <= 1'h0;
    end
    else begin
     ren_ack <= (ren_sync2)? 1'h1 : 1'h0;
    end

endmodule 

