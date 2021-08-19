module lock (
  input clk,n_reset,
  input [11:0] user_press,
  output reg open,
  output reg led1, led2, led3, led4, led5, led6, led7
  );
  
  wire [11:0] secret_num_1=12'hFF7; //4
  wire [11:0] secret_num_2=12'hF7F; //8
  wire [11:0] secret_num_3=12'hFFE; //1
  
  reg [3:0] cur_state;
  reg [3:0] next_state;
  
  parameter MSB=24;
  reg [MSB-1:0] cnt;
  

  parameter [4:0] IDLE=4'b0000, STAR_R=4'b0001, STAR=4'b0010, BUT_1_R=4'b0011, BUT_1=4'b0100, BUT_2_R=4'b0101, BUT_2=4'b0110, BUT_3_R=4'b0111, BUT_3=4'b1000;
  
  always @(posedge clk or negedge n_reset)
	if (!n_reset) begin
		cnt<={(MSB){1'b0}};
	end
	else begin
		if (user_press==12'hFFF) begin
			if (cnt=={(MSB){1'b1}}) begin 
				cnt<={(MSB){1'b0}};
			end
			else begin
				cnt<=cnt+{{(MSB-1){1'b0}},1'b1};
			end
		end
	end
  
  
  
  
  always @(posedge clk or negedge n_reset)
    if (!n_reset) begin
      cur_state<=IDLE;
    end
    else begin
      cur_state<=next_state;
    end
    
    
  always @(*)
    case (cur_state)
      
      IDLE : next_state = (user_press==12'h7FF)? STAR_R : cur_state;
		
		STAR_R : next_state = ((user_press==12'hFFF)&&(cnt=={(MSB){1'b1}}))? STAR : cur_state;
      
      STAR : if (user_press==secret_num_1) next_state = BUT_1_R;
             else if ((user_press==12'hFFF)||(user_press==12'h7FF)) next_state = cur_state;
             else next_state = IDLE;             
               
		BUT_1_R : next_state = ((user_press==12'hFFF)&&(cnt=={(MSB){1'b1}}))? BUT_1 : cur_state;
		
      BUT_1 : if (user_press==secret_num_2) next_state = BUT_2_R;
              else if (user_press==12'hFFF) next_state = cur_state;
              else if (user_press==12'h7FF) next_state = STAR_R;
              else next_state = IDLE;
                    
		BUT_2_R : next_state = ((user_press==12'hFFF)&&(cnt=={(MSB){1'b1}}))? BUT_2 : cur_state;
		
      BUT_2 : if (user_press==secret_num_3) next_state = BUT_3_R;
              else if (user_press==12'hFFF) next_state = cur_state;
              else if (user_press==12'h7FF) next_state = STAR_R;
              else next_state = IDLE;
				  
		BUT_3_R : next_state = ((user_press==12'hFFF)&&(cnt=={(MSB){1'b1}}))? BUT_3 : cur_state;

      BUT_3 : if (user_press==12'h7FF) next_state = STAR_R;
				  else if (user_press==12'hFFF) next_state = cur_state;
				  else next_state = IDLE;
		
      
      default : next_state = IDLE;
      
    endcase

  always @(cur_state)
    case (cur_state)
      IDLE : begin 
				 open=1'b0;
				 led1=1'b0;
				 led2=1'b0;
				 led3=1'b0;
				 led4=1'b0;
				 led5=1'b0;
				 led6=1'b0;
				 led7=1'b0;
				 end
				 
		STAR_R : begin
					open=1'b0;
					led1=1'b1;
					led2=1'b0;
					led3=1'b0;
					led4=1'b0;
				   led5=1'b0;
					led6=1'b0;
					led7=1'b0;
					end
					
      STAR : begin
			    open=1'b0;
				 led1=1'b0;
				 led2=1'b1;
				 led3=1'b0;
				 led4=1'b0;
				 led5=1'b0;
				 led6=1'b0;
				 led7=1'b0;
				 end
				 
		BUT_1_R : begin
				    open=1'b0;
					 led1=1'b0;
				    led2=1'b0;
				    led3=1'b1;
				    led4=1'b0; 
					 led5=1'b0;
					 led6=1'b0;
					 led7=1'b0;
					 end
					 
      BUT_1 : begin 
		        open=1'b0;
				  led1=1'b0;
				  led2=1'b0;
				  led3=1'b0;
				  led4=1'b1;
				  led5=1'b0;
				  led6=1'b0;
				  led7=1'b0;
				  end
				  
		BUT_2_R : begin 
					 open=1'b0;
					 led1=1'b0;
					 led2=1'b0;
				    led3=1'b0;
					 led4=1'b0;
					 led5=1'b1;
					 led6=1'b0;
					 led7=1'b0;
					 end
					 
      BUT_2 : begin 
		        open=1'b0;
				  led1=1'b0;
				  led2=1'b0;
				  led3=1'b0;
				  led4=1'b0;
				  led5=1'b0;
				  led6=1'b1;
				  led7=1'b0;
				  end
				  
		BUT_3_R : begin
	             open=1'b0;
					 led1=1'b0;
					 led2=1'b0;
					 led3=1'b0;
					 led4=1'b0;
					 led5=1'b0;
					 led6=1'b0;
					 led7=1'b1;
					 end
					 
      BUT_3 : begin 
		        open=1'b1;
				  led1=1'b0;
				  led2=1'b0;
				  led3=1'b0;
				  led4=1'b0; 
				  led5=1'b0;
				  led6=1'b0;
				  led7=1'b0;
				  end
				  
      default : begin
		          open=1'b0;
					 led1=1'b0;
					 led2=1'b0;
					 led3=1'b0;
					 led4=1'b0;
					 led5=1'b0;
					 led6=1'b0;
					 led7=1'b0;
					 end
					 
    endcase

endmodule