// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Main loop that decides sub-loop to take (blacken or whiten screen) depending on 
// whether a key is being pressed
(LOOP)
	// Put base address of screen (18384) into R0 so that R0 can be incremented
	@SCREEN		
	D=A

	@pixelsWord
	M=D

	// Decide on black or white path depending on key pressed or not
	@KBD
	D=M

	@BLACK
	D;JNE

	@WHITE
	D;JEQ

	// Keep polling for a key press
	@LOOP
	0;JMP
(BLACK)
	// If R0 has reached end of screen (24575), go back to main loop to reset R0 to start of screen (18384)
	@pixelsWord	// Check the value that R0 is holding (the address of the current screen word)
	D=M

	@24576		// 24576 is the KBD and 24577 is an illegal address
	D=D-A
	
	@LOOP
	D;JEQ	

	// Else, R0 is still within the start and end of screen, so fill the word with all 1's
	@pixelsWord	// Set the address to the value that R0 is holding
	A=M

	M=-1		// Fill current word with 1111111111111111

	@pixelsWord	// Move on to the next word in the screen
	M=M+1

	// If the key is no longer pressed, return to main loop
	@KBD		
	D=M
	
	@LOOP
	D;JEQ

	// Else, continue filling the rest of the screen with 1's
	@BLACK
	D;JNE
(WHITE)
	// If R0 has reached end of screen (24575), go back to main loop to reset R0 to start of screen (18384)
	@pixelsWord	// Check the value that R0 is holding (the address of the current screen word)
	D=M

	@24576		// 24576 is the KBD and 24577 is an illegal address
	D=D-A
	
	@LOOP
	D;JEQ
	
	// Else, R0 is still within the start and end of screen, so fill the word with all 0's
	@pixelsWord
	A=M

	M=0		// Fill current word with 0000000000000000

	@pixelsWord	// Move on to the next word in the screen
	M=M+1

	// If a key is suddenly pressed, return to main loop
	@KBD
	D=M
	
	@LOOP
	D;JNE

	// Else, continue filling the rest of the screen with 0's
	@WHITE
	D;JEQ