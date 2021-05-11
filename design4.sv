`define Xdig1 X[7:4]
`define Xdig0 X[3:0]
`define Ydig1 Y[7:4]
`define Ydig0 Y[3:0]
`define Zdig2 Z[11:8]
`define Zdig1 Z[7:4]
`define Zdig0 Z[3:0]
module BCD_Adder (X, Y, Z);
input[7:0] X;
input[7:0] Y;
output[11:0] Z;