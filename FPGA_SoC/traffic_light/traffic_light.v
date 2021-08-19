module traffic_light(
 spi_sclk,
 n_rst,

 t_g_wait,
 t_r_wait,

 sensor,

 main_light,
 country_light
);

input spi_sclk;
input n_rst;
input [2:0] t_g_wait;
input [2:0] t_r_wait;
input sensor;

output reg [1:0] main_light;
output reg [1:0] country_light;

reg [1:0] state_main;
reg [2:0] state_main_cnt;
reg [1:0] state_country;
reg [2:0] state_country_cnt;

parameter RED = 2'b00;
parameter GREEN = 2'b01;
parameter YELLOW = 2'b10;

parameter STATE_RED = 2'b00;
parameter STATE_GREEN = 2'b01;
parameter STATE_YELLOW = 2'b10;


always@(posedge spi_sclk, negedge n_rst)
 if(!n_rst) begin
  state_main <= STATE_GREEN;
 end
 else begin
  case (state_main)
   STATE_GREEN :  state_main <= (sensor==1'b1) ? STATE_YELLOW : state_main;
   STATE_YELLOW : state_main <= (state_main_cnt==t_r_wait) ? STATE_RED : state_main;
   STATE_RED :    state_main <= ((sensor==1'b0)&&(state_main_cnt==t_g_wait)) ? STATE_GREEN : state_main;
   default :      state_main <= STATE_GREEN;
  endcase
 end

always@(posedge spi_sclk, negedge n_rst)
 if(!n_rst)
 begin
  state_country <= STATE_RED;
 end
 else
 begin
  case(state_country)
    STATE_RED :     state_country <= ((sensor==1'b1)&&(state_country_cnt==t_g_wait)) ? STATE_GREEN : state_country;
    STATE_GREEN :   state_country <= (sensor==1'b0) ? STATE_YELLOW : state_country;
    STATE_YELLOW :  state_country <= (state_country_cnt==t_r_wait) ? STATE_RED : state_country;
    default : state_country <= STATE_RED;
  endcase
 end




always @ (posedge spi_sclk, negedge n_rst)
begin
 if(!n_rst)
 begin  
  state_main_cnt<=3'b000;
 end
 else
 begin
    if(state_main==STATE_RED)
    begin
     if(sensor==1'b0)
     begin
      state_main_cnt<=state_main_cnt+3'b001;
     end
     else
     begin
      state_main_cnt<=3'b000;
     end
    end
    else if(state_main==STATE_YELLOW)
    begin
     state_main_cnt<=state_main_cnt+3'b001;
    end
    else
    begin
     state_main_cnt<=3'b000;
    end
  end
end 
 

 

always @ (posedge spi_sclk, negedge n_rst)
begin
 if(!n_rst)
 begin
  state_country_cnt <= 3'b000;
 end
  else
  begin
   if(state_country==STATE_RED)
   begin
    if(sensor==1'b1)
    begin
     state_country_cnt <= state_country_cnt + 3'b001;
    end
    else
    begin
     state_country_cnt<=3'b000;
    end
   end
  else if(state_country==STATE_YELLOW)
   begin
    state_country_cnt <= state_country_cnt + 3'b001;
   end
   else
   begin
    state_country_cnt <= 3'b000;
   end
  end
end

always @ (posedge spi_sclk, negedge n_rst)
begin
 if(!n_rst)
 begin
  country_light<=RED;
 end
 else
 begin
  case(state_country)
  STATE_RED : country_light <= RED;
  STATE_YELLOW : country_light <= YELLOW;
  STATE_GREEN : country_light <= GREEN;
  default : country_light <= RED;
  endcase
 end
end

always @ (posedge spi_sclk, negedge n_rst)
begin
 if(!n_rst)
 begin
  main_light<=GREEN;
 end
 else
 begin
  case(state_main)
  STATE_RED : main_light <= RED;
  STATE_YELLOW : main_light <= YELLOW;
  STATE_GREEN : main_light <= GREEN;
  default : main_light <= GREEN;
  endcase
 end
end

endmodule 

