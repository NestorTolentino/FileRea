// Code your design here
module mux4_1(
    i1,i2,i3,i4,s,ot
  );
  input [3:0]i1,i2,i3,i4;
  input [1:0]s;
  output reg [3:0]ot;
  
  always @(i1,i2,i3,i4,s)
    begin
      if (s==2'b00)
      	ot = i1;
      else if (s==2'b01)
      	ot = i2;
      else if (s==2'b10)
      	ot = i3;
      else
        ot = i4;
    end
  
endmodule