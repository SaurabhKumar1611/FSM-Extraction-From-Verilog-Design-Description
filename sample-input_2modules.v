module
    liftcontroller(start,clk,reset_inside_button,reset_up,reset_down,up_button,down_button,inside_button,present_floor);
    input start,clk;
    input [6:0] up_button,down_button,inside_button;
    output [6:0] reset_inside_button,reset_up,reset_down,present_floor;
    reg [6:0] reset_inside_button,reset_up,reset_down,present_floor;
    reg dir_up;
    reg [4:0] nstate;
    parameter 	s0_idle = 0,s0_up = 1,door_0 = 2,s1_idle = 3,s1_up = 4,s1_down = 5,
    door_1 = 6,s2_idle = 7,s2_up = 8,s2_down = 9,door_2 = 10,s3_idle = 11,s3_down = 12,
    door_3 = 13,s3_up = 14,door_4 = 15,door_5 = 16, door_6 = 17, s4_up = 18, s5_up = 19,
    s5_down = 20, s4_down = 21, s6_down = 22, s4_idle = 23, s5_idle = 24, s6_idle = 25;
    initial begin
        reset_inside_button <= 7'b0000000;
        reset_up            <= 7'b0000000;
        reset_down          <= 7'b0000000;
        present_floor       <= 7'b0000000;
    end
    
    always @(posedge clk,start,nstate)
    begin
        if (start == 1'b1)
            nstate = s0_idle;
        else begin
            case(nstate)
                //------------------------------------------ground floor-----------------------------------------------
                s0_idle:begin
                    
                    present_floor = 7'd0;
                    if (up_button ! = 7'd0 || down_button ! = 7'd0 || inside_button ! = 7'd0)
                        nstate = s0_up;
                    else
                        nstate = s0_idle;
                    
                end
                s0_up:begin
                    present_floor          = 7'd0;
                    reset_up[0]            = 1'b0;
                    reset_inside_button[0] = 1'b0;
                    if (up_button[0] == 1'b1 || inside_button[0] == 1'b1)
                        nstate = door_0;
                    
                    else if ((up_button ! = 7'd0 || down_button ! = 7'd0 || inside_button ! = 7'd0) && up_button[0] == 1'b0 && inside_button[0] == 1'b0)
                    nstate = s1_up;
                    else
                    nstate = s0_idle;
                    
                end
                door_0:begin
                    reset_up[0]            = 1'b1;
                    reset_inside_button[0] = 1'b1;
                    nstate                 = s0_up;
                end
                //---------------------------------------------1st floor------------------------------------------------
                s1_idle:begin
                    present_floor = 7'b0000010;
                    if (up_button ! = 7'd0 || down_button ! = 7'd0 || inside_button ! = 7'd0) begin
                        if (up_button[0] == 1'b1 || inside_button[0] == 1'b1 || down_button[1] == 1'b1)
                            nstate = s1_down;
                        else
                            nstate = s1_up;
                    end
                    else
                    nstate = s1_idle;
                    
                end
                s1_up:begin
                    present_floor          = 7'b0000010;
                    reset_up[1]            = 1'b0;
                    reset_inside_button[1] = 1'b0;
                    if (up_button[1] == 1'b1 || inside_button[1] == 1'b1) begin
                        dir_up = 1'b1;
                        nstate = door_1;
                    end
                    
                    else if (up_button[5:2] ! = 4'b0000 || down_button[6:2] ! = 5'b00000 || inside_button[6:2] ! = 5'b00000)
                    nstate = s2_up;
                    
                    else if (up_button[0] == 1'b1 || inside_button[0] == 1'b1)
                    nstate = s1_down;
                    
                    else
                    nstate = s1_idle;
                    
                    
                end
                door_1:begin
                    reset_inside_button[1] = 1'b1;
                    if (dir_up == 1'b1) begin
                        reset_up[1] = 1'b1;
                        nstate      = s1_up;
                    end
                    else begin
                        reset_down[1] = 1'b1;
                        nstate        = s1_down;
                    end
                end
                s1_down:begin
                    present_floor          = 7'b0000010;
                    reset_inside_button[1] = 1'b0;
                    reset_down[1]          = 1'b0;
                    if (down_button[1] == 1'b1 || inside_button[1] == 1'b1) begin
                        dir_up = 1'b0;
                        nstate = door_1;
                    end
                    else if (up_button[0] == 1'b1 || inside_button[0] == 1'b1)
                    nstate = s0_up;
                    else if (up_button[5:2] ! = 4'b0000 || down_button[6:2] ! = 5'b00000 || inside_button[6:2] ! = 5'b00000)
                    nstate = s1_up;
                    else
                    nstate = s1_idle;
                    
                end
                //--------------------------second floor--------------------------------------------------------------
                s2_idle:begin
                    present_floor = 7'b0000100;
                    if (up_button ! = 7'b0000000 || down_button ! = 7'b0000000 || inside_button ! = 7'b0000000) begin
                        if (up_button[1:0] ! = 2'b00 || down_button[2:1] ! = 2'b00 || inside_button[1:0] ! = 2'b00)
                            nstate = s2_down;
                        else
                            nstate = s2_up;
                    end
                    else
                    nstate = s2_idle;
                end
                
                s2_up:begin
                    present_floor          = 7'b0000100;
                    reset_inside_button[2] = 1'b0;
                    reset_up[2]            = 1'b0;
                    if (up_button[2] == 1'b1 || inside_button[2] == 1'b1) begin
                        dir_up = 1'b1;
                        nstate = door_2;
                    end
                    else if (up_button[5:3] ! = 3'b000 || inside_button[6:3] ! = 4'b0000 || down_button[6:3] ! = 4'b0000)
                    nstate = s3_up;
                    else if (up_button[1:0] ! = 2'b00 || down_button[1] == 1'b1 || inside_button[1:0] ! = 2'b00)
                    nstate = s2_down;
                    else
                    nstate = s2_idle;
                end
                
                door_2:begin
                    reset_inside_button[2] = 1'b1;
                    if (dir_up == 1'b1) begin
                        reset_up[2] = 1'b1;
                        nstate      = s2_up;
                    end
                    else begin
                        reset_down[2] = 1'b1;
                        nstate        = s2_down;
                    end
                end
                
                s2_down:begin
                    present_floor          = 7'b0000100;
                    reset_inside_button[2] = 1'b0;
                    reset_down[2]          = 1'b0;
                    if (down_button[2] == 1'b1 || inside_button[2] == 1'b1) begin
                        dir_up = 1'b0;
                        nstate = door_2;
                    end
                    else if (up_button[1:0] ! = 2'b00 || down_button[1] == 1'b1 || inside_button[1:0] ! = 2'b00)
                    nstate = s1_down;
                    
                    else if (up_button[5:3] ! = 3'b000 || down_button[6:3] ! = 4'b0000 || inside_button[6:3] ! = 4'b0000)
                    nstate = s2_up;
                    else
                    nstate = s2_idle;
                    
                end
                //--------------------------3rd floor--------------------------------------------------------------
                
                s3_idle:begin
                    present_floor = 7'b0001000;
                    if (up_button ! = 7'b0000000 || down_button ! = 7'b0000000 || inside_button ! = 7'b0000000) begin
                        if (up_button[2:0] ! = "000" || down_button[3:1] ! = 3'b000 || inside_button[2:0] ! = 3'b000)
                            nstate = s3_down;
                        else
                            nstate = s3_up;
                    end
                    else
                    nstate = s3_idle;
                end
                s3_up:begin
                    present_floor          = 7'b0001000;
                    reset_inside_button[3] = 1'b0;
                    reset_up[3]            = 1'b0;
                    if (up_button[3] == 1'b1 || inside_button[3] == 1'b1) begin
                        dir_up = 1'b1;
                        nstate = door_3;
                    end
                    else if (up_button[5:4] ! = 2'b00 || inside_button[6:4] ! = 3'b000 || down_button[6:4] ! = 3'b000)
                    nstate = s4_up;
                    else if (up_button [2:0] ! = 3'b000 || down_button[2:1] ! = 2'b00 || inside_button[2:0] ! = 3'b000)
                    nstate = s3_down;
                    else
                    nstate = s3_idle;
                end
                s3_down:begin
                    present_floor          = 7'b0001000;
                    reset_inside_button[3] = 1'b0;
                    reset_down[3]          = 1'b0;
                    if (down_button[3] == 1'b1 || inside_button[3] == 1'b1) begin
                        dir_up = 1'b0;
                        nstate = door_3;
                    end
                    else if (up_button[2:0] ! = 3'b000 || down_button[2:1] ! = 2'b00 || inside_button[2:0] ! = 3'b000)
                    nstate = s2_down;
                    else if (up_button[5:4] ! = 2'b00 || inside_button[6:4] ! = 3'b000 || down_button[6:4] ! = 3'b000)
                    nstate = s3_up;
                    else
                    nstate = s3_idle;
                end
                door_3:begin
                    reset_inside_button[3] = 1'b1;
                    if (dir_up == 1'b1) begin
                        reset_up[3] = 1'b1;
                        nstate      = s3_up;
                    end
                    else begin
                        reset_down[3] = 1'b1;
                        nstate        = s3_down;
                    end
                end
                //--------------------------4th floor--------------------------------------------------------------
                s4_idle:begin
                    present_floor = 7'b0010000;
                    if (up_button ! = 7'b0000000 || down_button ! = 7'b0000000 || inside_button ! = 7'b0000000) begin
                        if (up_button[5] == 1'b1 || down_button[6:5] ! = 2'b00 || inside_button[6:5] ! = 2'b00 || up_button[4] == 1'b1)
                            nstate = s4_up;
                        else
                            nstate = s4_down;
                    end
                    else
                    nstate = s4_idle;
                end
                s4_up:begin
                    present_floor          = 7'b0010000;
                    reset_inside_button[4] = 1'b0;
                    reset_up[4]            = 1'b0;
                    if (up_button[4] == 1'b1 || inside_button[4] == 1'b1) begin
                        dir_up = 1'b1;
                        nstate = door_4;
                    end
                    else if (up_button[5] ! = 1'b0 || inside_button[6:5] ! = 2'b00 || down_button[6:5] ! = 2'b00)
                    nstate = s5_up;
                    else if (up_button[3:0] ! = 4'b0000 || down_button[3:1] ! = 3'b000 || inside_button[3:0] ! = 4'b0000)
                    nstate = s4_down;
                    else
                    nstate = s4_idle;
                end
                s4_down:begin
                    present_floor          = 7'b0010000;
                    reset_inside_button[4] = 1'b0;
                    reset_down[4]          = 1'b0;
                    if (down_button[4] == 1'b1 || inside_button[4] == 1'b1) begin
                        dir_up = 1'b0;
                        nstate = door_4;
                    end
                    else if (up_button [3:0] ! = 4'b0000 || down_button[3:1] ! = 3'b000 || inside_button[3:0] ! = 4'b0000)
                    nstate = s3_down;
                    else if (up_button[5] == 1'b1 || inside_button[6:5] ! = 2'b00 || down_button[6:5] ! = 2'b00)
                    nstate = s4_up;
                    
                    else
                    nstate = s4_idle;
                end
                door_4:begin
                    reset_inside_button[4] = 1'b1;
                    if (dir_up == 1'b1) begin
                        reset_up[4] = 1'b1;
                        nstate      = s4_up;
                    end
                    else begin
                        reset_down[4] = 1'b1;
                        nstate        = s4_down;
                    end
                end
                //--------------------------5th floor--------------------------------------------------------------
                
                s5_idle:begin
                    present_floor = 7'b0100000;
                    if (up_button ! = 7'b0000000 || down_button ! = 7'b0000000 || inside_button ! = 7'b0000000) begin
                        if (down_button[6] == 1'b1 || inside_button[6] == 1'b1 || up_button[5] == 1'b1)
                            nstate = s5_up;
                        else
                            nstate = s5_down;
                    end
                    else
                    nstate = s5_idle;
                end
                
                s5_up:begin
                    present_floor          = 7'b0100000;
                    reset_inside_button[5] = 1'b0;
                    reset_up[5]            = 1'b0;
                    if (up_button[5] == 1'b1 || inside_button[5] == 1'b1) begin
                        dir_up = 1'b1;
                        nstate = door_5;
                    end
                    else if (down_button[6] == 1'b1 || inside_button[6] == 1'b1)
                    nstate = s6_down;
                    else if (up_button[4:0] ! = 5'b00000 || down_button[4:1] ! = 4'b0000 || inside_button[4:0] ! = 4'b0000)
                    nstate = s5_down;
                    else
                    nstate = s5_idle;
                end
                s5_down:begin
                    present_floor          = 7'b0100000;
                    reset_inside_button[5] = 1'b0;
                    reset_down[5]          = 1'b0;
                    if (down_button[5] == 1'b1 || inside_button[5] == 1'b1) begin
                        dir_up = 1'b0;
                        nstate = door_5;
                    end
                    else if (up_button[4:0] ! = 5'b00000 || down_button[4:1] ! = 4'b0000 || inside_button[4:0] ! = 4'b0000)
                    nstate = s4_down;
                    else if (down_button[6] == 1'b1 || inside_button[6] == 1'b1)
                    nstate = s5_up;
                    
                    else
                    nstate = s5_idle;
                end
                door_5:begin
                    reset_inside_button[5] = 1'b1;
                    if (dir_up == 1'b1) begin
                        reset_up[5] = 1'b1;
                        nstate      = s5_up;
                    end
                    else begin
                        reset_down[5] = 1'b1;
                        nstate        = s5_down;
                    end
                end
                
                //--------------------------6th floor--------------------------------------------------------------
                
                s6_idle:begin
                    present_floor = 7'b1000000;
                    if (up_button ! = 7'b0000000 || down_button ! = 7'b0000000 || inside_button ! = 7'b0000000)
                    nstate = s6_down;
                    
                    else
                    nstate = s6_idle;
                end
                s6_down:begin
                    present_floor          = 7'b1000000;
                    reset_inside_button[6] = 1'b0;
                    reset_down[6]          = 1'b0;
                    if (down_button[6] == 1'b1 || inside_button[6] == 1'b1) begin
                        dir_up = 1'b0;
                        nstate = door_5;
                    end
                    else if (up_button [5:0] ! = 6'b000000 || down_button[5:1] ! = 5'b00000 || inside_button[5:0] ! = 6'b000000)
                    nstate = s5_down;
                    else
                    nstate = s6_idle;
                end
                door_6:begin
                    reset_inside_button[6] = 1'b1;
                    reset_down[6]          = 1'b1;
                    nstate                 = s6_down;
                end
            endcase
            
        end
    end
    
    
    
    
    
    
    
endmodule
	
	
	
	
	
`timescale 1us/1us

module rlencoding(data_in,data_in_valid,fast_clk,data_clk,reset,data_out,data_out_valid,read_signal,write_signal,readptr,writeptr,output1,data_clk1);
		
	input [7:0] data_in;
	input read_signal,write_signal,fast_clk,data_clk,data_in_valid,reset,data_clk1;
	output reg [7:0] data_out;
	output data_out_valid;
	output [7:0] readptr,writeptr;
	output [2:0] output1;
	
	reg [7:0] buffer [0:255];
	reg [7:0] count;
	reg [7:0] bufferoutput;
	reg [7:0] readptr;
	reg [7:0] writeptr;
	reg [1:0] nstate;
	reg [7:0] datacount;
	reg [2:0] output1;
	reg equal_or_not;
	reg [7:0] buffer1;
	reg [7:0] buffer2;
	reg [7:0] buffer3;
	reg flag1;
	reg flag2;
	reg flag3;
      	parameter reset_state=0,remember_state=1,count_state=2,count_reset=3,remember_state1=5;
	
	assign data_out_valid = flag3;	
	initial begin
	count <= 8'd0;
	readptr <= 8'd0;
	writeptr <= 8'd0;
	flag1 <= 1'b0;
	flag2 <= 1'b0;
	flag3 <= 1'b0;
	buffer1 <= 8'b0000_0000;
	buffer2 <= 8'b0000_0000;
	buffer3 <= 8'b0000_0000;
	datacount <= 8'b0000_0000;
	end

	
always @(posedge data_clk) begin
	
	if(reset == 1'b1) begin
	count = 0;
	writeptr = 0;
	readptr = 0;
	end
	if((buffer[readptr] == buffer[readptr+1]) && read_signal == 1) begin
	equal_or_not = 1'b1;
	end
	else	begin
	equal_or_not = 1'b0;
	end
	data_out = buffer[readptr];
	
	if(data_in_valid == 1'b1 && write_signal == 1'b1) begin
	if(count == 0) begin
	buffer[writeptr] = data_in;
	writeptr = (writeptr + 1)%255;
	readptr = (readptr + 1)%255;
	count = count + 1;
	end
	else if(count == 255) begin
	writeptr = writeptr;
	readptr = readptr;
	count = count;
	end
	else begin
	buffer[writeptr] = data_in;
	writeptr = (writeptr + 1)%255;
	count = count + 1;
	end
	end
	if(read_signal == 1'b1) begin
	if(count == 0) begin
	readptr = 0;
	writeptr = 0;
	count = count;
	end
	else begin
	bufferoutput = buffer[readptr];
	count = count - 1;
	readptr = (readptr + 1)%255;
	end
	end
	
		
end


always @(posedge data_clk)
	
	if(equal_or_not == 0) begin
		if(datacount == 0) begin
		flag1 <= 0;
		buffer1 <= 8'b0000_0000;
		buffer2 <= buffer1;
		buffer3 <= buffer2;
		flag2 <= flag1;
		flag3 <= flag2;
		end 
		else if(datacount == 1) begin
		flag1 <= 1;
		buffer1 <= buffer[readptr];
		buffer2 <= buffer[readptr];
		buffer3 <= buffer2;
		flag2 <= 1;
		flag3 <= flag2;
		end 
		else begin
		flag1 <= 1;
		flag2 <= 1;
		flag3 <= 1;
		buffer1 <= 8'b00011011;
		buffer2 <= datacount + 1;
		buffer3 <= buffer[readptr];
		end
	end
	else begin
	flag1 <= 0;
	buffer1 <= 8'b0000_0000;
	buffer2 <= buffer1;
	buffer3 <= buffer2;
	flag2 <= flag1;
	flag3 <= flag2; 
	end
	


always @(posedge fast_clk,nstate) begin
		if(reset == 1'b1) begin
			nstate = reset_state;
		end
		else begin
			case(nstate)
			
			remember_state: begin
				output1 = 3'd5;
				if(equal_or_not == 1) begin
					nstate = count_state;
				end
				else begin
					nstate = count_reset;
				end 
			end
			reset_state: begin
				output1 = 3'd0;
				datacount = 8'b0000_0000;
				nstate = remember_state;
			end
		
			count_state: begin
				output1 = 3'd2;
				if(data_clk1 == 1) begin
				datacount = datacount + 1;
				nstate = remember_state;
				end
			end
			count_reset: begin
				output1 = 3'd3;
				datacount = 8'b00000000;
				if(data_clk1 == 1) begin 
				nstate = remember_state;
				end 
			end



			endcase
		end
		
		
		 
			
end


endmodule
	
