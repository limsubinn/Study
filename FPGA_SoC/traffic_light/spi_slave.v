module spi_slave (
    spi_sclk,
    n_rst,

    addr,
    data,
    wen,

    
    spi_mosi,
    spi_miso,
    spi_ss_n
  
);
//input   clk;
input   n_rst;
input   spi_sclk;
input   spi_mosi;
output    spi_miso;
output [1:0] addr;
output [2:0] data;
output wen;

input   spi_ss_n;
parameter S_IDLE   = 4'h0;
parameter S_ACTIVE = 4'h1;
parameter S_END    = 4'h9;
reg [6:0]  mosi;
//reg   ss_n;
reg [3:0] cnt;
reg spi_mosi_d;
reg [2:0] data_d;

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
      spi_mosi_d <= 1'b0;
    end
    else begin
      spi_mosi_d <= spi_mosi;
    end

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
      data_d <= 3'h0;
    end
    else begin
      data_d <= mosi[2:0];
    end
    

always @(negedge n_rst or posedge spi_sclk)
    if(!n_rst) begin
        cnt <= S_IDLE;
    end
    else begin
        if(cnt==S_IDLE) cnt <= (spi_mosi==1'b1&&spi_mosi_d==1'b0&&spi_ss_n==1'b0)? cnt + 4'h1 : cnt;
        else if(mosi[6]!=1'b1) cnt <= (spi_ss_n==1'b0)? cnt + 4'h1 : cnt;
        else cnt <= S_IDLE;
    end


always @(negedge n_rst or posedge spi_sclk)
 if(!n_rst) begin
 // ss_n <= 1'b1;
  mosi <= 7'h00;
 end
 else begin
  //ss_n <= (start==1'b1)? 1'b0 :
    //(cnt == S_END)? 1'b1 : ss_n;
  mosi <= (cnt == S_ACTIVE)? {mosi[5:0], spi_mosi} : 
          (spi_ss_n==1'b0)? {mosi[5:0], spi_mosi} : 7'h00;
 end
//assign spi_ss_n = ss_n;
assign addr = mosi[4:3];
assign data = data_d;
//assign spi_sclk = clk;
assign spi_miso = 1'h0;
assign wen = mosi[5];
endmodule


