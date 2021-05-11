  
  module mux_4_1(
  input I0,I1,I2,I3,
  input I4,
  input [5:0] lasdasdeedads,hinput,
  input [7:0] xinput,
  input [1:0] s,
  output out
  
  );
  reg out;
  always@(I0,I1,I2,I3,s)
    begin
      if (s== 2'b00)
        out = I0;
      else if (s ==2'b01)
        out = I1;
      else if (s == 2'b10)
        out =I2;
      else
        out = I3;
    end //la ultima sentencia de un if debe ser un else
endmodule

      
  
  