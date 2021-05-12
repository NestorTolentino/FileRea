module RAM_memory(clk,Enable, ReadWrite, Address, DataIn, DataOut);
  input Enable, ReadWrite,clk;
  input [3:0]DataIn;
  input [5:0]Address;
  output[3:0]DataOut;
  reg[3:0]	 DataOut;
  reg[3:0]	 Mem[0:63];
 
  initial begin
    $readmemb("DatosMemoria.data",Mem,0,63);
  end
  
  always @(posedge clk, Enable or ReadWrite)
    begin
      if(Enable == 1'b1)
        if(ReadWrite == 1'b1) 
        	DataOut = Mem[Address];
  	  	else 
        	Mem[Address] = DataIn;
  	 else 
       DataOut = 4'bz;
    end
endmodule
