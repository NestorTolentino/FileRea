module Basic_Gates(a,b,q0,q1,q2,q3,q4,q5,q6);
  input a,b;
  output q0,q1,q2,q3,q4,q5,q6;
  output [3:0] c,d;
  output [4:0] f;
  
  assign q0= ~a;
  assign q1= a | b;
  assign q2= a & b;
  assign q3 = ~(a | b);
  assign q4 = ~(a & b);
  assign q5 = a ^ b;
  assign q6 = ~(a ^ b);
  
endmodule