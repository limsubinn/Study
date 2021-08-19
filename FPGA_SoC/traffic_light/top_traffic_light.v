module top_traffic_light (
    clk,
    spi_sclk,
    n_rst,
    
    sensor,
    main_light,
    country_light,
    
    spi_mosi,
    spi_ss_n,
    spi_miso
);

input sensor;
input spi_sclk;
input n_rst;
input spi_mosi;
input spi_ss_n;
output spi_miso;
output [1:0] country_light;
output [1:0] main_light;

input clk;
wire done;
wire [2:0] r_data;
wire done_sync2;
wire r_en;
wire ren_ack;
wire [1:0] r_addr;
wire [2:0] t_r_wait;
wire [2:0] t_g_wait;


slave u_slave (
   .spi_sclk(spi_sclk),
   .n_rst(n_rst),
   
   .spi_mosi(spi_mosi),
   .spi_ss_n(spi_ss_n),
   .spi_miso(spi_miso),

  // .t_r_wait(t_r_wait),
  // .t_g_wait(t_g_wait),

   .r_en(r_en),
   .r_addr(r_addr),

   .done_sync2(done_sync2),

   .r_data(r_data),
   .done(done),

   .ren_ack(ren_ack)

);

read_regfiles u_read_regfiles (
   .clk(clk),
   .n_rst(n_rst),

  .done(done),
  .r_data(r_data),

  .done_sync2(done_sync2),

  .r_en(r_en),
  .ren_ack(ren_ack),
  .r_addr(r_addr),

  .t_r_wait(t_r_wait),
  .t_g_wait(t_g_wait)

);

traffic_light u_traffic_light (
   .spi_sclk(spi_sclk),
   .n_rst(n_rst),
/*
   .addr(addr),
   .data(data), */
   
   .t_r_wait(t_r_wait),
   .t_g_wait(t_g_wait),
   
   .sensor(sensor),
   .main_light(main_light),
   .country_light(country_light)
);

endmodule

