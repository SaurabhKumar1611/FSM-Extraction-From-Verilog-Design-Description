`include "fifo.v"
`timescale 1us/1us

module router(

		routeridx,
		routeridy,
		local_in,
		north_in,
		south_in,
		west_in,
		east_in,
		local_out,
		north_out,
		south_out,
		west_out,
		east_out,
		count_out_north,
		count_out_south,
		count_out_east,
		count_out_west,
		count_out_local,
		count_in_north,
		count_in_south,
		count_in_east,
		count_in_west,
		count_in_local,
		clk,
		reset,
		enable,
		push_north,
		push_south,
		push_east,
		push_west,
		push_local,
		pop_north,
		pop_south,
		pop_east,
		pop_west,
		pop_local
		);
input [1:0] routeridx,routeridy;
input [31:0] local_in,north_in,south_in,west_in,east_in;
input [2:0] count_in_north;
input [2:0] count_in_south;
input [2:0] count_in_east;
input [2:0] count_in_west;
input [2:0] count_in_local;
input push_north,push_south,push_east,push_west,push_local;
output pop_north,pop_south,pop_east,pop_west,pop_local;

input clk,reset,enable;

output [31:0] local_out,north_out,south_out,west_out,east_out;
output [2:0] count_out_north;
output [2:0] count_out_south;
output [2:0] count_out_east;
output [2:0] count_out_west;
output [2:0] count_out_local;

wire [31:0] local_out,north_out,south_out,west_out,east_out;
wire [2:0] count_out_north;
wire [2:0] count_out_south;
wire [2:0] count_out_east;
wire [2:0] count_out_west;
wire [2:0] count_out_local;

wire [31:0] north_out_intermediate;
wire [31:0] south_out_intermediate;
wire [31:0] east_out_intermediate;
wire [31:0] west_out_intermediate;
wire [31:0] local_out_intermediate;

reg pop_north1;
reg pop_south1;
reg pop_east1;
reg pop_west1;
reg pop_local1;
reg pop_north;
reg pop_south;
reg pop_east;
reg pop_west;
reg pop_local;



assign north_out = muxoutput1;
assign south_out = muxoutput2;
assign east_out = muxoutput3;
assign west_out = muxoutput4;
assign local_out = muxoutput5;


wire [31:0] north_frontdata,north_reardata;
wire [31:0] south_frontdata,south_reardata;
wire [31:0] east_frontdata,east_reardata;
wire [31:0] west_frontdata,west_reardata;
wire [31:0] local_frontdata,local_reardata;

fifo u1(
.frontdata(north_frontdata),
.reardata(north_reardata),
.data_in(north_in),
.data_out(north_out_intermediate),
.count(count_out_north),
.pop(pop_north1),
.push(push_north),
.clk(clk),
.reset(reset),
.enable(enable)
);

fifo u2(
.frontdata(south_frontdata),
.reardata(south_reardata),
.data_in(south_in),
.data_out(south_out_intermediate),
.count(count_out_south),
.pop(pop_south1),
.push(push_south),
.clk(clk),
.reset(reset),
.enable(enable)
);

fifo u3(
.frontdata(east_frontdata),
.reardata(east_reardata),
.data_in(east_in),
.data_out(east_out_intermediate),
.count(count_out_east),
.pop(pop_east1),
.push(push_east),
.clk(clk),
.reset(reset),
.enable(enable)
);

fifo u4(
.frontdata(west_frontdata),
.reardata(west_reardata),
.data_in(west_in),
.data_out(west_out_intermediate),
.count(count_out_west),
.pop(pop_west1),
.push(push_west),
.clk(clk),
.reset(reset),
.enable(enable)
);

fifo u5(
.frontdata(local_frontdata),
.reardata(local_reardata),
.data_in(local_in),
.data_out(local_out_intermediate),
.count(count_out_local),
.pop(pop_local1),
.push(push_local),
.clk(clk),
.reset(reset),
.enable(enable)
);



reg [2:0] x1;
reg [2:0] x2;
reg [2:0] x3;
reg [2:0] x4;
reg [2:0] x5;

reg [2:0] nstate1;
reg [2:0] nstate2;
reg [2:0] nstate3;
reg [2:0] nstate4;
reg [2:0] nstate5;

initial begin
x1 <= 3'b000;
x2 <= 3'b000;
x3 <= 3'b000;
x4 <= 3'b000;
x5 <= 3'b000;
end
parameter s0_south = 0, s1_south = 1, s2_south = 2, s3_south = 3, s4_south = 4, s5_south = 5, s6_south = 6;
parameter s0_north = 0, s1_north = 1, s2_north = 2, s3_north = 3, s4_north = 4, s5_north = 5, s6_north = 6;
parameter s0_east = 0, s1_east = 1, s2_east = 2, s3_east = 3, s4_east = 4, s5_east = 5, s6_east = 6;
parameter s0_west = 0, s1_west = 1, s2_west = 2, s3_west = 3, s4_west = 4, s5_west = 5, s6_west = 6;
parameter s0_local = 0, s1_local = 1, s2_local = 2, s3_local = 3, s4_local = 4, s5_local = 5, s6_local = 6;
//0--reset,1--north,2--south,3--east,4--west,5--local

always @(posedge clk,count_in_north,count_in_south,count_in_east,count_in_west,count_in_local,x1,x2,x3,x4,x5) begin//south



	if(x1 == 3'b010 && count_in_north < 3'b100)
		pop_south1 = 1'b1;
	else if(x2 == 3'b010 && count_in_south < 3'b100)
		pop_south1 = 1'b1;
	else if(x3 == 3'b010 && count_in_east < 3'b100)
		pop_south1 = 1'b1;
	else if(x4 == 3'b010 && count_in_west < 3'b100)
		pop_south1 = 1'b1;
	else if(x5 == 3'b010 && count_in_local < 3'b100)
		pop_south1 = 1'b1;
	else
		pop_south1 = 1'b0;
				 

end
always @(posedge clk,count_in_north,count_in_south,count_in_east,count_in_west,count_in_local,x1,x2,x3,x4,x5) begin//north


	if(x1 == 3'b001 && count_in_north < 3'b100)
		pop_north1 = 1'b1;
	else if(x2 == 3'b001 && count_in_south < 3'b100)
		pop_north1 = 1'b1;
	else if(x3 == 3'b001 && count_in_east < 3'b100)
		pop_north1 = 1'b1;
	else if(x4 == 3'b001 && count_in_west < 3'b100)
		pop_north1 = 1'b1;
	else if(x5 == 3'b001 && count_in_local < 3'b100)
		pop_north1 = 1'b1;
	else
		pop_north1 = 1'b0;
				 

end

always @(posedge clk,count_in_north,count_in_south,count_in_east,count_in_west,count_in_local,x1,x2,x3,x4,x5) begin//east


	if(x1 == 3'b011 && count_in_north < 3'b100)
		pop_east1 = 1'b1;
	else if(x2 == 3'b011 && count_in_south < 3'b100)
		pop_east1 = 1'b1;
	else if(x3 == 3'b011 && count_in_east < 3'b100)
		pop_east1 = 1'b1;
	else if(x4 == 3'b011 && count_in_west < 3'b100)
		pop_east1 = 1'b1;
	else if(x5 == 3'b011 && count_in_local < 3'b100)
		pop_east1 = 1'b1;
	else
		pop_east1 = 1'b0;
				 

end
always @(posedge clk,count_in_north,count_in_south,count_in_east,count_in_west,count_in_local,x1,x2,x3,x4,x5) begin//west

	
	if(x1 == 3'b100 && count_in_north < 3'b100)
		pop_west1 = 1'b1;
	else if(x2 == 3'b100 && count_in_south < 3'b100)
		pop_west1 = 1'b1;
	else if(x3 == 3'b100 && count_in_east < 3'b100)
		pop_west1 = 1'b1;
	else if(x4 == 3'b100 && count_in_west < 3'b100)
		pop_west1 = 1'b1;
	else if(x5 == 3'b100 && count_in_local < 3'b100)
		pop_west1 = 1'b1;
	else
		pop_west1 = 1'b0;
				 

end
always @(posedge clk,count_in_north,count_in_south,count_in_east,count_in_west,count_in_local,x1,x2,x3,x4,x5) begin//local


	if(x1 == 3'b101 && count_in_north < 3'b100)
		pop_local1 = 1'b1;
	else if(x2 == 3'b101 && count_in_south < 3'b100)
		pop_local1 = 1'b1;
	else if(x3 == 3'b101 && count_in_east < 3'b100)
		pop_local1 = 1'b1;
	else if(x4 == 3'b101 && count_in_west < 3'b100)
		pop_local1 = 1'b1;
	else if(x5 == 3'b101 && count_in_local < 3'b100)
		pop_local1 = 1'b1;
	else
		pop_local1 = 1'b0;
				 

end

always @(count_in_north,x1)
begin

	if(x1 == 3'b010 && count_in_north < 3'b100)
		pop_north = 1;
	else if(x1 == 3'b011 && count_in_north < 3'b100)
		pop_north = 1;
	else if(x1 == 3'b100 && count_in_north < 3'b100)
		pop_north = 1;
	else if(x1 == 3'b101 && count_in_north < 3'b100)
		pop_north = 1;
	else 
		pop_north = 0;


end

always @(count_in_south,x2)
begin

	if(x2 == 3'b001 && count_in_south < 3'b100)
		pop_south = 1;
	else if(x2 == 3'b011 && count_in_south < 3'b100)
		pop_south = 1;
	else if(x2 == 3'b100 && count_in_south < 3'b100)
		pop_south = 1;
	else if(x2 == 3'b101 && count_in_south < 3'b100)
		pop_south = 1;
	else 
		pop_south = 0;


end
always @(count_in_east,x3)
begin

	if(x3 == 3'b001 && count_in_east < 3'b100)
		pop_east = 1;
	else if(x3 == 3'b010 && count_in_east < 3'b100)
		pop_east = 1;
	else if(x3 == 3'b100 && count_in_east < 3'b100)
		pop_east = 1;
	else if(x3 == 3'b101 && count_in_east < 3'b100)
		pop_east = 1;
	else 
		pop_east = 0;

end
always @(count_in_west,x4)
begin

	if(x4 == 3'b001 && count_in_west < 3'b100)
		pop_west = 1;
	else if(x4 == 3'b010 && count_in_west < 3'b100)
		pop_west = 1;
	else if(x4 == 3'b011 && count_in_west < 3'b100)
		pop_west = 1;
	else if(x4 == 3'b101 && count_in_west < 3'b100)
		pop_west = 1;
	else 
		pop_west = 0;

end

	
	




//----------------------------------------------------north select-----------------------------------------------

//0--reset,1--north,2--south,3--east,4--west,5--local

always @(posedge clk,nstate1,reset) begin //for north port

	if(reset == 1'b1) begin
		x1 = 3'b000; //no channel
		nstate1 = s0_north;
	end
	else begin
		case(nstate1)
			s0_north:begin
				x1 = 3'b000;
				if(north_frontdata[31:30] == 2'b01)begin
					nstate1 = s1_north;
				end
				else if(south_frontdata[31:30] == 2'b01)begin
						nstate1 = s2_north;
				end
				else if(east_frontdata[31:30] == 2'b01)begin
						nstate1 = s3_north;
				end
				else if(west_frontdata[31:30] == 2'b01)begin
						nstate1 = s4_north;
				end
				else if(local_frontdata[31:30] == 2'b01)begin
						nstate1 = s5_north;
				end								
				else begin
					nstate1 = s0_north;
				end
			end
			s1_north: begin //north
                if(north_frontdata[31:30] == 2'b01 && (north_frontdata[21:20] > routeridy) && (north_frontdata[23:22]==routeridx)) begin
					x1 = 3'b001;
					nstate1 = s1_north;
				end
				else if(north_frontdata[31:30] == 2'b01 && (north_frontdata[21:20] <= routeridy) && (north_frontdata[23:22]==routeridx)) begin
					x1 = 3'b000;
					nstate1 = s2_north;
				end
						
				else if(north_frontdata[31:30] == 2'b11 && count_in_north < 3'b100) begin
					nstate1 = s6_north;
				end
				else begin
					if(x1 == 3'b000) begin
						nstate1 = s2_north;
					end
					else begin
					  	nstate1 = s1_north;
					end
				end
			end
			s2_north: begin//south
				if(south_frontdata[31:30] == 2'b01 && (south_frontdata[21:20] > routeridy) && (south_frontdata[23:22]==routeridx)) begin
					x1 = 3'b010;
					nstate1 = s2_north;
				end
				else if(south_frontdata[31:30] == 2'b01 && (south_frontdata[21:20] <= routeridy) && (south_frontdata[23:22]==routeridx)) begin
					x1 = 3'b000;
					nstate1 = s3_north;
				end	
				else if(south_frontdata[31:30] == 2'b11 && count_in_south < 3'b100) begin
					nstate1 = s6_north;
				end	
				else begin
					if(x1 == 3'b000) begin
						nstate1 = s3_north;
					end
					else begin
					  	nstate1 = s2_north;
					end
				end	
			end
			
			s3_north: begin//east
				if(east_frontdata[31:30] == 2'b01 && (east_frontdata[21:20] > routeridy) && (east_frontdata[23:22]==routeridx)) begin
					x1 = 3'b011;
					nstate1 = s3_north;
				end
				else if(east_frontdata[31:30] == 2'b01 && (east_frontdata[21:20] <= routeridy) && (east_frontdata[23:22]==routeridx)) begin
					x1 = 3'b000;
					nstate1 = s4_north;
				end	
				else if(east_frontdata[31:30] == 2'b11 && count_in_east < 3'b100) begin
					nstate1 = s6_north;
				end	
				else begin
					if(x1 == 3'b000) begin
						nstate1 = s4_north;
					end
					else begin
					  	nstate1 = s3_north;
					end
				end	
			end
			s4_north: begin//west
				if(west_frontdata[31:30] == 2'b01 && (west_frontdata[21:20] > routeridy) && (west_frontdata[23:22]==routeridx)) begin	
					x1 = 3'b100;
					nstate1 = s4_north;
				end
				else if(west_frontdata[31:30] == 2'b01 && (west_frontdata[21:20] <= routeridy) && (west_frontdata[23:22]==routeridx)) begin
					x1 = 3'b000;	
					nstate1 = s5_north;
				end
						
				else if(west_frontdata[31:30] == 2'b11 && count_in_west < 3'b100) begin
					nstate1 = s6_north;
				end	
				else begin
					if(x1 == 3'b000) begin
						nstate1 = s5_north;
					end
					else begin
					  	nstate1 = s4_north;
					end
				end	
			end	
			s5_north: begin//local
				if(local_frontdata[31:30] == 2'b01 && (local_frontdata[21:20] > routeridy) && (local_frontdata[23:22]==routeridx)) begin
					x1 = 3'b101;
					nstate1 = s5_north;
				end
				else if(local_frontdata[31:30] == 2'b01 && (local_frontdata[21:20] <= routeridy) && (local_frontdata[23:22]==routeridx)) begin
					x1 = 3'b000;
					nstate1 = s1_north;
				end
						
				else if(local_frontdata[31:30] == 2'b11 && count_in_local < 3'b100) begin
					nstate1 = s6_north;
				end	
				else begin
					if(x1 == 3'b000) begin
						nstate1 = s1_north;
					end
					else begin
					  	nstate1 = s5_north;
					end
				end
			end
			s6_north: begin
				if(x1 == 3'b001) begin
					x1 = 3'b000;
					nstate1 = s2_north;
				end
				else if(x1 == 3'b010) begin
					x1 = 3'b000;
					nstate1 = s3_north;
				end
				else if(x1 == 3'b011) begin
					x1 = 3'b000;
					nstate1 = s4_north;
				end
				else if(x1 == 3'b100) begin
					x1 = 3'b000;
					nstate1 = s5_north;
				end
				else if(x1 == 3'b101) begin
					x1 = 3'b000;
					nstate1 = s1_north;
				end
				else begin
					x1 = 3'b000;
					nstate1 = s0_north;
				end
			end //s6_north
		endcase
	end//else
	 
	 

end //always
//----------------------------------------------------north select end------------------------------------------------

//------------------------------------------------------north mux----------------------------------------------------

reg [31:0] muxoutput1;//north output
reg [31:0] nochannel;
initial begin
nochannel <= 32'b1;
end



always @( 
		north_out_intermediate,
		south_out_intermediate,
		east_out_intermediate,
		west_out_intermediate,
		local_out_intermediate,
		x1,
		nochannel
	) begin //north

	
	if(x1 == 3'b001)
		muxoutput1 =  north_out_intermediate;
	else if(x1 == 3'b000)
		muxoutput1 = nochannel;
	else if(x1 == 3'b010)
		muxoutput1 = south_out_intermediate;
	else if(x1 == 3'b011)
		muxoutput1 = east_out_intermediate;
	else if(x1 == 3'b100)
		muxoutput1 = west_out_intermediate;
	else if(x1 == 3'b101)
		muxoutput1 = local_out_intermediate;
	else 
		muxoutput1 = nochannel;

end//always

//----------------------------------------------------------north mux end---------------------------------------


//-------------------------------------------------south select----------------------------------------------------

always @(posedge clk,nstate2,reset) begin //for south port

	if(reset == 1'b1) begin
		x2 = 3'b000; //no channel
		nstate2 = s0_south;
	end
	else begin
		case(nstate2)
			s0_south:begin
				x2 = 3'b000;
				if(north_frontdata[31:30] == 2'b01)begin
						nstate2 = s1_south;
				end
				else if(south_frontdata[31:30] == 2'b01) begin
						nstate2 = s2_south;
				end
				else if(east_frontdata[31:30] == 2'b01) begin
						nstate2 = s3_south;
				end
				else if(west_frontdata[31:30] == 2'b01) begin
						nstate2 = s4_south;
				end
				else if(local_frontdata[31:30] == 2'b01) begin
						nstate2 = s5_south;
				end								
				else begin
					nstate2 = s0_south;
				end
			end
			s1_south: begin //north
				if(north_frontdata[31:30] == 2'b01 && (north_frontdata[21:20] < routeridy) && (north_frontdata[23:22]==routeridx)) begin
					x2 = 3'b001;
					nstate2 = s1_south;
				end
				else if(north_frontdata[31:30] == 2'b01 && (north_frontdata[21:20] >= routeridy) && (north_frontdata[23:22]==routeridx)) begin
					x2 = 3'b000;
					nstate2 = s2_south;
				end	
				else if(north_frontdata[31:30] == 2'b11 && count_in_north < 3'b100) begin
					nstate2 = s6_south;
				end
				else begin
					if(x2 == 3'b000) begin
						nstate2 = s2_south;
					end
					else begin
					  	nstate2 = s1_south;
					end
				end	
			end
			s2_south: begin//south
				if(south_frontdata[31:30] == 2'b01 && (south_frontdata[21:20] < routeridy) && (south_frontdata[23:22]==routeridx)) begin	
					x2 = 3'b010;
					nstate2 = s2_south;
				end
				else if(south_frontdata[31:30] == 2'b01 && (south_frontdata[21:20] >= routeridy) && (south_frontdata[23:22]==routeridx)) begin
					x2 = 3'b000;
					nstate2 = s3_south;
				end
						
				else if(south_frontdata[31:30] == 2'b11 && count_in_south < 3'b100) begin
					nstate2 = s6_south;
				end	
				else begin
					if(x2 == 3'b000) begin
						nstate2 = s3_south;
					end
					else begin
					  	nstate2 = s2_south;
					end
				end
			end
			
			s3_south: begin//east
				if(east_frontdata[31:30] == 2'b01 && (east_frontdata[21:20] < routeridy) && (east_frontdata[23:22]==routeridx)) begin
					x2 = 3'b011;
					nstate2 = s3_south;
				end
				else if(east_frontdata[31:30] == 2'b01 && (east_frontdata[21:20] >= routeridy) && (east_frontdata[23:22]==routeridx)) begin
					x2 = 3'b000;
					nstate2 = s4_south;
				end
				else if(east_frontdata[31:30] == 2'b11 && count_in_east < 3'b100) begin
					nstate2 = s6_south;
				end	
				else begin
					if(x2 == 3'b000) begin
						nstate2 = s4_south;
					end
					else begin
					  	nstate2 = s3_south;
					end
				end
			end
			s4_south: begin//west
				if(west_frontdata[31:30] == 2'b01 && (west_frontdata[21:20] < routeridy) && (west_frontdata[23:22]==routeridx)) begin
					x2 = 3'b100;
					nstate2 = s4_south;
				end
				else if(west_frontdata[31:30] == 2'b01 && (west_frontdata[21:20] >= routeridy) && (west_frontdata[23:22]==routeridx)) begin
					x2 = 3'b000;
					nstate2 = s5_south;
				end		
				else if(west_frontdata[31:30] == 2'b11 && count_in_west < 3'b100) begin
					nstate2 = s6_south;
				end	
				else begin
					if(x2 == 3'b000) begin
						nstate2 = s5_south;
					end
					else begin
					  	nstate2 = s4_south;
					end
				end	
			end	
			
			
			s5_south: begin//local
				if(local_frontdata[31:30] == 2'b01 && (local_frontdata[21:20] < routeridy) && (local_frontdata[23:22]==routeridx)) begin	
					x2 = 3'b101;
					nstate2 = s5_south;
				end
				else if(local_frontdata[31:30] == 2'b01 && (local_frontdata[21:20] >= routeridy) && (local_frontdata[23:22]==routeridx)) begin
					x2 = 3'b000;
					nstate2 = s1_south;
				end		
				else if(local_frontdata[31:30] == 2'b11 && count_in_local < 3'b100) begin
					nstate2 = s6_south;
				end	
				else begin
					if(x2 == 3'b000) begin
						nstate2 = s1_south;
					end
					else begin
					  	nstate2 = s5_south;
					end
				end	
			end

			s6_south: begin
				if(x2 == 3'b001) begin
					x2 = 3'b000;
					nstate2 = s2_south;
				end
				else if(x2 == 3'b010) begin
					x2 = 3'b000;
					nstate2 = s3_south;
				end
				else if(x2 == 3'b011) begin
					x2 = 3'b000;
					nstate2 = s4_south;
				end
				else if(x2 == 3'b100) begin
					x2 = 3'b000;
					nstate2 = s5_south;
				end
				else if(x2 == 3'b101) begin
					x2 = 3'b000;
					nstate2 = s1_south;
				end
				else begin
					x2 = 3'b000;
					nstate2 = s0_south;
				end

			end //s6_south
		endcase

	end//else
	 
	 

end //always
//----------------------------------------------------south select end------------------------------------------------

//------------------------------------------------------south mux----------------------------------------------------

reg [31:0] muxoutput2;//south output




always @( 
		north_out_intermediate,
		south_out_intermediate,
		east_out_intermediate,
		west_out_intermediate,
		local_out_intermediate,
		x2,
		nochannel
	) begin //south

	
	if(x2 == 3'b001)
		muxoutput2 =  north_out_intermediate;
	else if(x2 == 3'b000)
		muxoutput2 = nochannel;
	else if(x2 == 3'b010)
		muxoutput2 = south_out_intermediate;
	else if(x2 == 3'b011)
		muxoutput2 = east_out_intermediate;
	else if(x2 == 3'b100)
		muxoutput2 = west_out_intermediate;
	else if(x2 == 3'b101)
		muxoutput2 = local_out_intermediate;
	else 
		muxoutput2 = nochannel;

end//always

//---------------------------------------------------------south mux end---------------------------------------


//-------------------------------------------------east select----------------------------------------------------

always @(posedge clk,nstate3,reset) begin //for east port

	if(reset == 1'b1) begin
		x3 = 3'b000; //no channel
		nstate3 = s0_east;
	end
	else begin
		case(nstate3)
			s0_east:begin
				x3 = 3'b000;
				
				if(north_frontdata[31:30] == 2'b01)begin
						nstate3 = s1_east;
				end
				else if(south_frontdata[31:30] == 2'b01) begin
						nstate3 = s2_east;
				end
				else if(east_frontdata[31:30] == 2'b01) begin
						nstate3 = s3_east;
				end
				else if(west_frontdata[31:30] == 2'b01) begin
						nstate3 = s4_east;
				end
				else if(local_frontdata[31:30] == 2'b01) begin
						nstate3 = s5_east;
				end								
				else begin
					nstate3 = s0_east;
				end
			end
			s1_east: begin //north
				if(north_frontdata[31:30] == 2'b01 && (north_frontdata[23:22] > routeridx)) begin	
					x3 = 3'b001;
					nstate3 = s1_east;
				end
				else if(north_frontdata[31:30] == 2'b01 && (north_frontdata[23:22] <= routeridx)) begin
					x3 = 3'b000;
					nstate3 = s2_east;
				end		
				else if(north_frontdata[31:30] == 2'b11 && count_in_north < 3'b100) begin
					nstate3 = s6_east;
				end
				else begin
					if(x3 == 3'b000) begin
						nstate3 = s2_east;
					end
					else begin
					  	nstate3 = s1_east;
					end
				end	
			end
			s2_east: begin//south
				if(south_frontdata[31:30] == 2'b01 && (south_frontdata[23:22] > routeridx)) begin	
					x3 = 3'b010;
					nstate3 = s2_east;
				end
				else if(south_frontdata[31:30] == 2'b01 && (south_frontdata[23:22] <= routeridx)) begin
					x3 = 3'b000;
					nstate3 = s3_east;
				end		
				else if(south_frontdata[31:30] == 2'b11 && count_in_south < 3'b100) begin
					nstate3 = s6_east;
				end	
				else begin
					if(x3 == 3'b000) begin
						nstate3 = s3_east;
					end
					else begin
					  	nstate3 = s2_east;
					end
				end	
			end
			
			s3_east: begin//east
				if(east_frontdata[31:30] == 2'b01 && (east_frontdata[23:22] > routeridx)) begin
					x3 = 3'b011;
					nstate3 = s3_east;
				end
				else if(east_frontdata[31:30] == 2'b01 && (east_frontdata[23:22]<=routeridx)) begin
					x3 = 3'b000;
					nstate3 = s4_east;
				end
				else if(east_frontdata[31:30] == 2'b11 && count_in_east < 3'b100) begin
					nstate3 = s6_east;
				end	
				else begin
					if(x3 == 3'b000) begin
						nstate3 = s4_east;
					end
					else begin
					  	nstate3 = s3_east;
					end
				end
			end
			s4_east: begin//west
				if(west_frontdata[31:30] == 2'b01 && (west_frontdata[23:22] > routeridx)) begin
					x3 = 3'b100;
					nstate3 = s4_east;
				end
				else if(west_frontdata[31:30] == 2'b01 && (west_frontdata[23:22]<=routeridx)) begin
					x3 = 3'b000;
					nstate3 = s5_east;
				end
				else if(west_frontdata[31:30] == 2'b11 && count_in_west < 3'b100) begin
					nstate3 = s6_east;
				end	
				else begin
					if(x3 == 3'b000) begin
						nstate3 = s5_east;
					end
					else begin
					  	nstate3 = s4_east;
					end
				end
			end	
			
			
			s5_east: begin//local
				if(local_frontdata[31:30] == 2'b01 && (local_frontdata[23:22]>routeridx)) begin
					x3 = 3'b101;
					nstate3 = s5_east;
				end
				else if(local_frontdata[31:30] == 2'b01 && (local_frontdata[23:22]<=routeridx)) begin
					x3 = 3'b000;
					nstate3 = s1_east;
				end
				else if(local_frontdata[31:30] == 2'b11 && count_in_local < 3'b100) begin
					nstate3 = s6_east;
				end	
				else begin
					if(x3 == 3'b000) begin
						nstate3 = s1_east;
					end
					else begin
					  	nstate3 = s5_east;
					end
				end
			end

			s6_east: begin
				if(x3 == 3'b001) begin
					x3 = 3'b000;
					nstate3 = s2_east;
				end

				else if(x3 == 3'b010) begin
					x3 = 3'b000;
					nstate3 = s3_east;
				end
				else if(x3 == 3'b011) begin
					x3 = 3'b000;
					nstate3 = s4_east;
				end
				else if(x3 == 3'b100) begin
					x3 = 3'b000;
					nstate3 = s5_east;
				end
				else if(x3 == 3'b101) begin
					x3 = 3'b000;
					nstate3 = s1_east;
				end
				else begin
					x3 = 3'b000;
					nstate3 = s0_east;
				end
			end //s6_east
		endcase

	end//else
	 
	 

end //always
//----------------------------------------------------east select end------------------------------------------------

//------------------------------------------------------east mux----------------------------------------------------

reg [31:0] muxoutput3;//east output



always @( 
		north_out_intermediate,
		south_out_intermediate,
		east_out_intermediate,
		west_out_intermediate,
		local_out_intermediate,
		x3,
		nochannel
	) begin //east

	
	if(x3 == 3'b001)
		muxoutput3 =  north_out_intermediate;
	else if(x3 == 3'b000)
		muxoutput3 = nochannel;
	else if(x3 == 3'b010)
		muxoutput3 = south_out_intermediate;
	else if(x3 == 3'b011)
		muxoutput3 = east_out_intermediate;
	else if(x3 == 3'b100)
		muxoutput3 = west_out_intermediate;
	else if(x3 == 3'b101)
		muxoutput3 = local_out_intermediate;
	else 
		muxoutput3 = nochannel;

end//always

//----------------------------------------------------------east mux end---------------------------------------





//-------------------------------------------------west select----------------------------------------------------
 

always @(posedge clk,nstate4,reset) begin //for west port

	if(reset == 1'b1) begin
		x4 = 3'b000; //no channel
		nstate4 = s0_west;
	end
	else begin
		case(nstate4)
			s0_west:begin
				x4 = 3'b000;
				if((north_frontdata[31:30] == 2'b01)) begin
						nstate4 = s1_west;
				end
				else if((south_frontdata[31:30] == 2'b01)) begin
						nstate4 = s1_west;
				end
				else if((east_frontdata[31:30] == 2'b01)) begin
						nstate4 = s1_west;
				end
				else if((west_frontdata[31:30] == 2'b01)) begin
						nstate4 = s1_west;
				end
				else if((local_frontdata[31:30] == 2'b01)) begin
						nstate4 = s1_west;
				end
				else begin
					nstate4 = s0_west;
				end
			end
			s1_west: begin //north
				if(north_frontdata[31:30] == 2'b01 && (north_frontdata[23:22] < routeridx)) begin
					x4 = 3'b001;
					nstate4 = s1_west;
				end
				else if(north_frontdata[31:30] == 2'b01 && (north_frontdata[23:22] >= routeridx)) begin
					x4 = 3'b000;
					nstate4 = s2_west;
				end
						
				else if(north_frontdata[31:30] == 2'b11 && count_in_north < 3'b100) begin
					nstate4 = s6_west;
				end
				else begin
					if(x4 == 3'b000) begin
						nstate4 = s2_west;
					end
					else begin
					  	nstate4 = s1_west;
					end
				end
			end
			s2_west: begin//south
				if(south_frontdata[31:30] == 2'b01 && (south_frontdata[23:22] <routeridx)) begin
					x4 = 3'b010;
					nstate4 = s2_west;
				end
				else if(south_frontdata[31:30] == 2'b01 && (south_frontdata[23:22] >= routeridx)) begin
					x4 = 3'b000;
					nstate4 = s3_west;
				end
						
				else if(south_frontdata[31:30] == 2'b11 && count_in_south < 3'b100) begin
					nstate4 = s6_west;
				end	
				else begin
					if(x4 == 3'b000) begin
						nstate4 = s3_west;
					end
					else begin
					  	nstate4 = s2_west;
					end
				end
			end
			
			s3_west: begin//east
				if(east_frontdata[31:30] == 2'b01 && (east_frontdata[23:22] < routeridx)) begin
					x4 = 3'b011;
					nstate4 = s3_west;
				end
				else if(east_frontdata[31:30] == 2'b01 && (east_frontdata[23:22] >= routeridx)) begin
					x4 = 3'b000;
					nstate4 = s4_west;
				end
				else if(east_frontdata[31:30] == 2'b11 && count_in_east < 3'b100) begin
					nstate4 = s6_west;
				end	
				else begin
					if(x4 == 3'b000) begin
						nstate4 = s4_west;
					end
					else begin
					  	nstate4 = s3_west;
					end
				end
			end
			s4_west: begin//west
				if(west_frontdata[31:30] == 2'b01 && (west_frontdata[23:22] < routeridx)) begin
					x4 = 3'b100;
					nstate4 = s4_west;
								
				end
				else if(west_frontdata[31:30] == 2'b01 && (west_frontdata[23:22] >= routeridx)) begin
					x4 = 3'b000;
					nstate4 = s5_west;
				end
				else if(west_frontdata[31:30] == 2'b11 && count_in_west < 3'b100) begin
					nstate4 = s6_west;
				end	
				else begin
					if(x4 == 3'b000) begin
						nstate4 = s5_west;
					end
					else begin
					  	nstate4 = s4_west;
					end
				end
			end	
			
			
			s5_west: begin//local
				if(local_frontdata[31:30] == 2'b01 && (local_frontdata[23:22]<routeridx)) begin
					x4 = 3'b101;
					nstate4 = s5_west;
				end
				else if(local_frontdata[31:30] == 2'b01 && (local_frontdata[23:22]>=routeridx)) begin
					x4 = 3'b000;
					nstate4 = s1_west;
				end
				else if(local_frontdata[31:30] == 2'b11 && count_in_local < 3'b100) begin
					nstate4 = s6_west;
				end	
				else begin
					if(x4 == 3'b000) begin
						nstate4 = s1_west;
					end
					else begin
					  	nstate4 = s5_west;
					end
				end
			end
			s6_west: begin
				if(x4 == 3'b001) begin
					x4 = 3'b000;
					nstate4 = s2_west;
				end
				else if(x4 == 3'b010) begin
					x4 = 3'b000;
					nstate4 = s3_west;
				end
				else if(x4 == 3'b011) begin
					x4 = 3'b000;
					nstate4 = s4_west;
				end
				else if(x4 == 3'b100) begin
					x4 = 3'b000;
					nstate4 = s5_west;
				end
				else if(x4 == 3'b101) begin
					x4 = 3'b000;
					nstate4 = s1_west;
				end
				else begin
					x4 = 3'b000;
					nstate4 = s0_west;
				end
			end //s6_west
		endcase //endcase
	end//else
end //always

//-------------------------------------------------west select end----------------------------------------------------


//-------------------------------------------------west mux----------------------------------------------------
reg [31:0] muxoutput4;//west output

always @( 
		north_out_intermediate,
		south_out_intermediate,
		east_out_intermediate,
		west_out_intermediate,
		local_out_intermediate,
		x4,
		nochannel
	) begin //west

	
	if(x4 == 3'b001)
		muxoutput4 =  north_out_intermediate;
	else if(x4 == 3'b000)
		muxoutput4 = nochannel;
	else if(x4 == 3'b010)
		muxoutput4 = south_out_intermediate;
	else if(x4 == 3'b011)
		muxoutput4 = east_out_intermediate;
	else if(x4 == 3'b100)
		muxoutput4 = west_out_intermediate;
	else if(x4 == 3'b101)
		muxoutput4 = local_out_intermediate;
	else 
		muxoutput4 = nochannel;

end//always

//-------------------------------------------------west mux end----------------------------------------------------








//-------------------------------------------------local select----------------------------------------------------
 

always @(posedge clk,nstate5,reset) begin //for local port

	if(reset == 1'b1) begin
		x5 = 3'b000; //no channel
		nstate5 = s0_local;
	end
	else begin
		case(nstate5)
			s0_local:begin
				x5 = 3'b000;
				if((north_frontdata[31:30] == 2'b01) && (north_frontdata[21:20]==routeridy) && (north_frontdata[23:22]==routeridx)) begin
						nstate5 = s1_local;
				end
				else if((south_frontdata[31:30] == 2'b01) && (south_frontdata[21:20]==routeridy) &&(south_frontdata[23:22]==routeridx)) begin
						nstate5 = s1_local;
				end
				else if((east_frontdata[31:30] == 2'b01) && (east_frontdata[21:20]==routeridy) && (east_frontdata[23:22]==routeridx)) begin
						nstate5 = s1_local;
				end
				else if((west_frontdata[31:30] == 2'b01) && (west_frontdata[21:20] == routeridy) && (west_frontdata[23:22]==routeridx)) begin
						nstate5 = s1_local;
				end
				else if((local_frontdata[31:30] == 2'b01) && (local_frontdata[21:20]==routeridy) && (local_frontdata[23:22]==routeridx)) begin
						nstate5 = s1_local;
				end
				else begin
					nstate5 = s0_local;
				end
			end
			s1_local: begin //north
				if(north_frontdata[31:30] == 2'b01 && (north_frontdata[21:20] == routeridy) && (north_frontdata[23:22]==routeridx)) begin
					x5 = 3'b001;
					nstate5 = s1_local;
				end
				else if(north_frontdata[31:30] == 2'b01 && (north_frontdata[21:20] == routeridy) && (north_frontdata[23:22]==routeridx)) begin
					x5 = 3'b000;
					nstate5 = s2_local;
				end
				else if(north_frontdata[31:30] == 2'b11 && count_in_north < 3'b100) begin
					nstate5 = s6_local;
				end
				else begin
					if(x5 == 3'b000) begin
						nstate5 = s2_local;
					end
					else begin
					  	nstate5 = s1_local;
					end
				end
			end
			s2_local: begin//south
				if(south_frontdata[31:30] == 2'b01 && (south_frontdata[21:20] == routeridy) && (south_frontdata[23:22]==routeridx)) begin
					x5 = 3'b010;
					nstate5 = s2_local;
				end
				else if(south_frontdata[31:30] == 2'b01 && (south_frontdata[21:20] == routeridy) && (south_frontdata[23:22]==routeridx)) begin
					x5 = 3'b000;
					nstate5 = s3_local;
				end
				else if(south_frontdata[31:30] == 2'b11 && count_in_south < 3'b100) begin
					nstate5 = s6_local;
				end	
				else begin
					if(x5 == 3'b000) begin
						nstate5 = s3_local;
					end
					else begin
					  	nstate5 = s2_local;
					end
				end
			end
			
			s3_local: begin//east
				if(east_frontdata[31:30] == 2'b01 && (east_frontdata[21:20] == routeridy) &&	(east_frontdata[23:22]==routeridx)) begin
					x5 = 3'b011;
					nstate5 = s3_local;
								
				end
				else if(east_frontdata[31:30] == 2'b01 && (east_frontdata[21:20] == routeridy) && (east_frontdata[23:22]==routeridx)) begin
					x5 = 3'b000;
					nstate5 = s4_local;
				end
						
				else if(east_frontdata[31:30] == 2'b11 && count_in_east < 3'b100) begin
					nstate5 = s6_local;
				end	
				else begin
					if(x5 == 3'b000) begin
						nstate5 = s4_local;
					end
					else begin
					  	nstate5 = s3_local;
					end
				end
			end
			s4_local: begin//west
				if(west_frontdata[31:30] == 2'b01 && (west_frontdata[21:20] == routeridy) && (west_frontdata[23:22]==routeridx)) begin
					x5 = 3'b100;
					nstate5 = s4_local;
				end
				else if(west_frontdata[31:30] == 2'b01 && (west_frontdata[21:20] == routeridy) && (west_frontdata[23:22]==routeridx)) begin
					x5 = 3'b000;
					nstate5 = s5_local;
				end
				else if(west_frontdata[31:30] == 2'b11 && count_in_west < 3'b100) begin
					nstate5 = s6_local;
				end	
				else begin
					if(x5 == 3'b000) begin
						nstate5 = s5_local;
					end
					else begin
					  	nstate5 = s4_local;
					end
				end
			end	
			s5_local: begin//local
				if(local_frontdata[31:30] == 2'b01 && (local_frontdata[21:20] == routeridy) && (local_frontdata[23:22]==routeridx)) begin
					x5 = 3'b101;
					nstate5 = s5_local;
								
				end
				else if(local_frontdata[31:30] == 2'b01 && (local_frontdata[21:20] == routeridy) && (local_frontdata[23:22]==routeridx)) begin
					x5 = 3'b000;
					nstate5 = s1_local;
				end
				else if(local_frontdata[31:30] == 2'b11 && count_in_local < 3'b100) begin
					nstate5 = s6_local;
				end	
				else begin
					if(x5 == 3'b000) begin
						nstate5 = s1_local;
					end
					else begin
					  	nstate5 = s5_local;
					end
				end
			end
			s6_local: begin
				if(x5 == 3'b001) begin
					x5 = 3'b000;
					nstate5 = s2_local;
				end

				else if(x5 == 3'b010) begin
					x5 = 3'b000;
					nstate5 = s3_local;
				end
				else if(x5 == 3'b011) begin
					x5 = 3'b000;
					nstate5 = s4_local;
				end
				else if(x5 == 3'b100) begin
					x5 = 3'b000;
					nstate5 = s5_local;
				end
				else if(x5 == 3'b101) begin
					x5 = 3'b000;
					nstate5 = s1_local;
				end
				else begin
					x5 = 3'b000;
					nstate5 = s0_local;
				end
			end //s6_local
		endcase//endcase
	end//else
end //always

//-------------------------------------------------local select end----------------------------------------------------


//-------------------------------------------------local mux----------------------------------------------------
reg [31:0] muxoutput5;//local output

always @( 
		north_out_intermediate,
		south_out_intermediate,
		east_out_intermediate,
		west_out_intermediate,
		local_out_intermediate,
		x5,
		nochannel
	) begin //local

	
	if(x5 == 3'b001)
		muxoutput5 =  north_out_intermediate;
	else if(x5 == 3'b000)
		muxoutput5 = nochannel;
	else if(x5 == 3'b010)
		muxoutput5 = south_out_intermediate;
	else if(x5 == 3'b011)
		muxoutput5 = east_out_intermediate;
	else if(x5 == 3'b100)
		muxoutput5 = west_out_intermediate;
	else if(x5 == 3'b101)
		muxoutput5 = local_out_intermediate;
	else 
		muxoutput5 = nochannel;

end//always

//-------------------------------------------------local mux end----------------------------------------------------





endmodule