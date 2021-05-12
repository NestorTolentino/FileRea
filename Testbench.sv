`timescale 1ns/1ns 
module FSM3_TB;
	wire [2:0] outp;
	reg clk,reset;
FSM3 UUT(.outp(outp));

initial
	begin
		$dumpfile("FSM3.vcd");
		$dumpvars(1,FSM3_TB);
