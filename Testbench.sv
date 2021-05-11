`timescale 1ns/1ns 
module Basic_Gates_TB;
	wire q0,q1,q2,q3,q4,q5,q6;
	wire [3:0] c,d;
	wire [4:0] f;
	reg a,b;
Basic_Gates UUT(.a(a),.b(b),.q0(q0),.q1(q1),.q2(q2),.q3(q3),.q4(q4),.q5(q5),.q6(q6),.c(c),.d(d),. f( f));

initial
	begin
		$dumpfile("Basic_Gates.vcd");
		$dumpvars(1,Basic_Gates_TB);
			{a,b}=2'b0;#1
			{a,b}=2'b1;#1
			{a,b}=2'b10;#1
			{a,b}=2'b11;#1

		$finish;
	end
endmodule