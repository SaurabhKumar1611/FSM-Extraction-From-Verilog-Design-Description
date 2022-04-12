
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
				if (equal_or_not == 1) begin
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
				
				if (data_clk1 == 1) begin
				datacount = datacount + 1;
				nstate = remember_state;
				end
			end
			count_reset: begin
				output1 = 3'd3;
				datacount = 8'b00000000;
				if (data_clk1 == 1) begin 
				nstate = remember_state;
				end 
			end



			endcase
		end
		
		
		 
			
end


endmodule
	
