`timescale 1ns/1ns 
module FSM3_TB;
	wire [2:0] outp;
	wire logic;
	reg clk,reset;
FSM3 UUT(.outp(outp),.logic(logic));

initial
	begin
		$dumpfile("FSM3.vcd");
		$dumpvars(1,FSM3_TB);
