module slave (
    spi_sclk,
    n_rst,

    spi_mosi,
    spi_miso,
    spi_ss_n,
    
    r_en,
    r_addr,

    done_sync2,

    r_data,
    done,

    ren_ack
    
    
);

input spi_sclk;
input n_rst;

input spi_mosi;
input spi_ss_n;
output spi_miso;

wire [1:0] addr;
wire [2:0] data;
wire       wen;

output done;
output ren_ack;
output [2:0] r_data;


output r_en;
input [1:0] r_addr;


input done_sync2;


slave_regfiles u_slave_regfiles (
   .spi_sclk(spi_sclk),
   .n_rst(n_rst),

   .addr(addr),
   .wen(wen),
   .data(data),

   .r_en(r_en),
   .r_addr(r_addr),

   .done_sync2(done_sync2),

   .r_data(r_data),
   .done(done),

   .ren_ack(ren_ack)

);

spi_slave u_spi_slave (
   .spi_sclk(spi_sclk),
   .n_rst(n_rst),

   .addr(addr),
   .data(data),
   .wen(wen),
    
   .spi_mosi(spi_mosi),
   .spi_miso(spi_miso),
   .spi_ss_n(spi_ss_n)
);

endmodule

