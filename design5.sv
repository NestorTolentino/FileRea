// Code your design here
module FSM3(clk,reset,outp);
  input clk,reset;
  output[2:0] outp;
  reg[2:0] outp;
  //state coding
  reg[2:0] state, next_state; 
  
  parameter s0=3'b000; //iguala
  parameter s1=3'b001;
  parameter s2=3'b010;
  parameter s3=3'b011;
  parameter s4=3'b100;
  parameter s5=3'b101;
  parameter s6=3'b110;
  parameter s7=3'b111;

  
  initial begin 
    state =3'b000;
  end
  
  //state register
  
  always @(posedge clk, posedge reset) //reset asincrono 
    begin
      if(reset)
        state <= s0;
      else 
        state <= next_state;
    end
  
  //next state function 
  
  always @(state)
    begin 
      case(state)
        s0: next_state=s1;
        s1: next_state=s2;
        s2: next_state=s3;
        s3: next_state=s4;
        s4: next_state=s5;
        s5: next_state=s6;
        s6: next_state=s7;
        default: next_state=s0;

      endcase
    end
      
      //output logic
  
  always @(state)
    begin
      case(state)
        s0 : outp=3'b000;
        s1 : outp=3'b001;
        s2 : outp=3'b010;
        s3 : outp=3'b011;
        s4 : outp=3'b100;
        s5 : outp=3'b101;
        s6 : outp=3'b110;      
        default : outp=3'b111;
      endcase
    end
endmodule
