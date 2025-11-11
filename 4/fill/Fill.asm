// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//Main Program Loop
(LOOP)
    //Get screen address
    @SCREEN
    D=A
    @0
    M=D
    //Get Keyboard Status, puts it into the M Register
    @KBD
    D=M
    @1
    M=-1
    //Jump to fill with color black if key is pressed
    @FILL
    D;JNE
    //Else - set color to white and Fill
    @1
    M=0

//Fills the Screen with color value within the M Register
(FILL)
    //Select color
    @1
    D=M
    //Get pixel
    @0
    A=M
    M=D
    //Move to next Pixel
    @0
    D=M+1
    @KBD
    D=A-D
    @0
    M=M+1
    //Loop back
    @FILL
    D;JGT
    //Go back to start if screen is full
    @LOOP
    0;JMP