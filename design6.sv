module TOP(
  input[5:0] OP,Func,
  output Memmux,Memwe,Alumux,Regmux,Regwe,
  output [2:0] ALUctrl
);
  
  assign Memux = !&OP;
  assign Alumux = !&OP;
  assign Regmux = &OP;
  assign Regwe =1'b1;
  assign Memwe=1'b1;
always @(A,B,s) begin
  case(Func)
      6'b100000: ALUctrl=001;
      6'b100010: ALUctrl=010;
      6'b100100: ALUctrl=011;
      6'b100101: ALUctrl=100;
      6'b100110: ALUctrl=101;
      6'b100111: ALUctrl=110;
      6'b101010: ALUctrl=111;
      default: ALUctrl=000; 
  endcase
end
endmodule