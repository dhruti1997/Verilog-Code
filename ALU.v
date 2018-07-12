// ALU

module ALU_4bit(Out, Z, C, V, P, A, B, Opcode);

output [3:0] Out;
output Z, C, V, P;
input [3:0] A, B, Opcode;

wire [3:0] shift_out, arith_out, logical_out, compare_out;

Shifter s (shift_out, A, B, Opcode);
Arithmetic a (arith_out, C, V, A, B, Opcode);
Logical l (logical_out, A, B, Opcode);
Comparator c (compare_out, A, B, Opcode);
MUX m (Out, shift_out, arith_out, logical_out, compare_out, Opcode);

nor (Z,Out[0],Out[1],Out[2],Out[3]);
xor (P,Out[0],Out[1],Out[2],Out[3]);

endmodule




// Shifter

module Shifter(shift_out, A, B, Opcode);

output reg [3:0] shift_out;
input [3:0] A, B, Opcode;

always @(*)
begin
	if(Opcode[3:1] == 0)
		shift_out = B<<A[1:0];
	if(Opcode == 2)
		shift_out = B>>A[1:0];
	if(Opcode == 3)
	begin
		case(A[1:0])
			0: shift_out = B;
			1: shift_out = {B[3],B[3:1]};
			2: shift_out = {B[3],B[3],B[3:2]};
			3: shift_out = {B[3],B[3],B[3],B[3]};
		endcase
	end
end

endmodule




// Arithmetic

module Arithmetic(arith_out, C, V, A, B, Opcode);

output reg [3:0] arith_out;
output reg C, V;
input [3:0] A, B, Opcode;

reg [3:0] temp_B;
reg temp_carry;

always@(*)
begin
	C = 0;
	if(Opcode[1] == 1)
	begin
		if(Opcode[0] == 1)
			temp_B = 4'b1111;
		else
			temp_B = ~B+1;
	end
	else
	begin
		if(Opcode[0] == 1)
			temp_B = 4'b0001;
		else
			temp_B = B;
	end
		
	if(Opcode[3:2] == 1)
	begin
		{temp_carry,arith_out[2:0]}=A[2:0]+temp_B[2:0];
		{C,arith_out[3]}=A[3]+temp_B[3]+temp_carry;
		V = C^temp_carry;
	end
	else
	begin
		V = 0;
		C = 0;
	end
end

endmodule





// Logic

module Logical(logical_out, A, B, Opcode);

output [3:0] logical_out;
input [3:0] A, B, Opcode;

assign logical_out = Opcode[1]?(Opcode[0]?~(A|B):(A^B)):(Opcode[0]?(A|B):(A&B));

endmodule





// Comparator

module Comparator(compare_out, A, B, Opcode);

output reg [3:0] compare_out;
input [3:0] A, B, Opcode;

always@(*)
begin
	if (Opcode == 12)
		compare_out[0] = A==B;
	if (Opcode == 13)
		compare_out[0] = A!=B;
	if (Opcode == 14)
	begin
		if(B[3]>A[3])
			compare_out[0] = 1;
		else if (A[3]!=B[3] && A[2:0]>B[2:0])
			compare_out[0] = 1;
		else
			compare_out[0] = 0;
	end
	if (Opcode == 15)
	begin
		if(A[3]>B[3])
			compare_out[0] = 1;
		else if (A[3]!=B[3] && B[2:0]>A[2:0])
			compare_out[0] = 1;
		else
			compare_out[0] = 0;
	end
	compare_out[3:1] = 0;
end
endmodule






// MUX

module MUX(Out, shift_out, arith_out, logical_out, compare_out, Opcode);

output reg [3:0] Out;
input [3:0] shift_out, arith_out, logical_out, compare_out, Opcode;

always@(*)
begin
	case(Opcode[3:2])
		0: Out = shift_out;
		1: Out = arith_out;
		2: Out = logical_out;
		3: Out = compare_out;
	endcase
end

endmodule




// Testbench

module ALU_4bit_tb;

	// Inputs
	reg [3:0] A;
	reg [3:0] B;
	reg [3:0] Opcode;

	// Outputs
	wire [3:0] Out;
	wire Z;
	wire C;
	wire V;
	wire P;

	// Instantiate the Unit Under Test (UUT)
	ALU_4bit uut (
		.Out(Out), 
		.Z(Z), 
		.C(C), 
		.V(V), 
		.P(P), 
		.A(A), 
		.B(B), 
		.Opcode(Opcode)
	);
	
	integer i;
	
	initial begin
		// Initialize Inputs
		A = 5;
		B = 12;
		// Wait 100 ns for global reset to finish
		for(i=0; i<16; i=i+1)
		begin
			Opcode = i;  
			#10;
		end

	end
      
endmodule
