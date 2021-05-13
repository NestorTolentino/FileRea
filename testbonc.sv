module reg_memory_TB;
reg [4:0] A1,A2,A3;
reg [31:0] WD3;
reg clk,rst,rw;
wire [31:0] RD1,RD2;
reg_memory UUT(.A1(A1),.A2(A2),.A3(A3),.WD3(WD3),.clk(clk),.rst(rst),.rw(rw),.RD1(RD1),.RD2(RD2));
initial
	begin
		$dumpfile(".vcd");
		$dumpvars(1,_TB);