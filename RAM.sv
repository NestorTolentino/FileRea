
module RAM(
  
  input Enable, ReadWrite,
  input [3:0]DataIn,
  input [5:0] Address,
  output reg [3:0]DataOut
  
);
input Enable;
  reg [3:0] Mem[0:63];
  
  initial
    begin
      $readmemh("ram_init.mem",Mem,0,63);
    end
  
  always @(Enable, ReadWrite, Address)
    begin
      if (Enable)
        begin
        if(ReadWrite)DataOut = Mem[Address];
      	else Mem[Address] = DataIn;
        end
      else DataOut = 4'bzzzz;
    end
endmodule

module testing();