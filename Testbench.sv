module reg_memory_TB;
reg [4:0] A1,A2,A3
reg [31:0] WD3
reg clk,rst,rw
wire reg [31:0] RD1,RD2
module reg_memory UUT(.input[4:0](input[4:0]),.A1(A1),.A2(A2),.A3(A3),.input[31:0](input[31:0]),.WD3(WD3),.clk(clk),.rst(rst),.rw(rw),.reg(reg),.RD1(RD1),.RD2(RD2));
initial
	begin
		$dumpfile("reg_memory.vcd");
		$dumpvars(1,reg_memory_TB);