`timescale 1ns/1ns
module mux_4_1_TB;
reg I0,I1,I2,I3;
reg [1:0] s;
wire out;
mux_4_1 UUT(.I0(I0),.I1(I1),.I2(I2),.I3(I3),.s(s),.out(out));
initial
	begin
		$dumpfile("mux_4_1.vcd");
		$dumpvars(1,mux_4_1_TB);
		{I0,I1,I2,I3,s}=6'b0;#1
		{I0,I1,I2,I3,s}=6'b10;#1
		{I0,I1,I2,I3,s}=6'b110;#1
		{I0,I1,I2,I3,s}=6'b1001;#1
		{I0,I1,I2,I3,s}=6'b1010;#1
		{I0,I1,I2,I3,s}=6'b1101;#1
		{I0,I1,I2,I3,s}=6'b10001;#1
		{I0,I1,I2,I3,s}=6'b10100;#1
		{I0,I1,I2,I3,s}=6'b11010;#1
		{I0,I1,I2,I3,s}=6'b11011;#1
		{I0,I1,I2,I3,s}=6'b11111;#1
		{I0,I1,I2,I3,s}=6'b100011;#1
		{I0,I1,I2,I3,s}=6'b100111;#1
		{I0,I1,I2,I3,s}=6'b101000;#1
		{I0,I1,I2,I3,s}=6'b101001;#1
		{I0,I1,I2,I3,s}=6'b101011;#1
		{I0,I1,I2,I3,s}=6'b101100;#1
		{I0,I1,I2,I3,s}=6'b101110;#1
		{I0,I1,I2,I3,s}=6'b110010;#1
		{I0,I1,I2,I3,s}=6'b110011;#1
		{I0,I1,I2,I3,s}=6'b110110;#1
		{I0,I1,I2,I3,s}=6'b111000;#1
		{I0,I1,I2,I3,s}=6'b111010;#1
		{I0,I1,I2,I3,s}=6'b111011;#1
		{I0,I1,I2,I3,s}=6'b111100;#1
		{I0,I1,I2,I3,s}=6'b111111;#1
		$finish;
	end
endmodule
