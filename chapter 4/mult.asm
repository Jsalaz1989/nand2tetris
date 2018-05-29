// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
	
	// Initialize R2=0
	@R2
	M=0	
	
	// If R0=0 or R1=0, R2=0 already so exit 
	@R0
	D=M
	@END		// R0=0?
	D;JEQ		
	@R1
	D=M
	@END		// R1=0?
	D;JEQ		
(LOOP)
	// Add R0 to R2 and store in R2, decrementing R1
	@R0	 
	D=M
	@R2		// Add R0 to current sum (R2)
	M=D+M		
	@R1		// Decrement R1
	MD=M-1		
	
	@END		// If R1 has dropped to 0, exit
	D;JEQ
	@LOOP		// Otherwise, keep adding	
	0;JMP	
(END)
	@END
	0;JMP