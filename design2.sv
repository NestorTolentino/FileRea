module reg_memory(
  input [4:0] A1,A2,A3,
  input [47:0] WD3,
  input clk,rst,rw,
  output reg [31:0] RD1,RD2
 
);
  //Change the sisze of the memory  Mem[0:31] -> Mem[0:4]
  reg [31:0] Mem[0:4];
  
  initial begin
    $readmemh("mem3.txt", Mem);
    end
  always@(posedge clk,posedge rst) begin
      if(rst) begin
        RD1 = 'b0;
      	RD2 = 'b0;
      end
      else
        if (rw) Mem[A3] = WD3;
      	RD1 = Mem[A1];
      	RD2 = Mem[A2];
  end
endmodule