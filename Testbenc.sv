`timescale 1ns/1ns 
module RAM_memory_TB;
	wire [3:0]DataOut;
	reg Enable, ReadWrite,clk;
	reg [3:0]DataIn;
	reg [5:0]Address;
RAM_memory UUT(.Enable(Enable),.ReadWrite(ReadWrite),.clk(clk),.DataIn(DataIn),.Address(Address),.DataOut(DataOut));

initial
	begin
		$dumpfile("RAM_memory.vcd");
		$dumpvars(1,RAM_memory_TB);
			clk=1'b0; #1
			{Enable,ReadWrite,DataIn,Address}=12'b0;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1010100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1101100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11010101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101110110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110101011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111011001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1000000010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1000110110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1001011001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1010110111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1011001001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1011011100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1011101111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1100010100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1100011011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1101001001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1110010101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1110100011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1111001001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1111001111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1111100011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b1111101100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10000111011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10001111000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10001111011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10010000001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10010011110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10011010111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10100010011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10101001111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10110100100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b10111010000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11000001110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11000011100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11010110110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11011010001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11011010110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11100100000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11100110000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11101000010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11101101000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11110100100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b11110101000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100000000101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100000101000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100000110011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100000110111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100001100100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100001101100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100010100010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100010110101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100010111001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100100011011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100100111101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b100110110010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101000111101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101001000110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101001110110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101100010101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101100010110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101100101101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101101100011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101101111100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b101110111000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110000011111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110001000100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110001111111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110010000010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110010110000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110010110101;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110011000110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110011011011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110100010001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110100011010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110101101111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110101110111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110110001011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110110101011;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110110101110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110110110111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110111000000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b110111110000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111000010001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111000111000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111000111010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111001011000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111001100010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111010010001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111010010010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111010011110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111011000111;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111011001100;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111011011110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111100001000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111101010010;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111110101110;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111110110001;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111111010000;#1
			{Enable,ReadWrite,DataIn,Address}=12'b111111111111;#1

		$finish;
	end
	always #1 clk=~clk;
endmodule