# Assembler

Note:
This is an **unfinished** project currently being developed.

This is an on-calc editor and ez80 compiler for the Ti-84+CE graphing calculator.
In order to compile build for yourself, you must download and install the CEDev toolchain,
this ensures you have the neccesarry binaries to compile C into assembly for the calculator.
Otherwise the "most up to date" Assembler.8xp is included for testing purposes. 

Currently redesigning the editor window to fix recursive calls to the main editor window
(nested input requires a lot of memory). Also working on dynamic memory versus a static 
partition on calculator.

Things currently to do:&nbsp;
//Main menu&nbsp;
    //Open project&nbsp;
    //Rename project/files&nbsp;
    //Add files&nbsp;
    //Delete files&nbsp;
    //Open file&nbsp;
    //Read & write appvars&nbsp;
//Editor&nbsp;
    //clear and restore previous page on exit&nbsp;
        //more than 1 val box_type is broken&nbsp;
    //fix and add box_type values&nbsp;
    //fix and add no label option&nbsp;
&nbsp;
//Text editor&nbsp;
//-------------------&nbsp;
//Spaces are 3? pixels, versus 1&nbsp;
//Remove scroll on insert&nbsp;
//Add option buttons (Graph row) graphics&nbsp;
    //cut & paste&nbsp;
    //clear row&nbsp;
    //clear up to cursor&nbsp;
    //save & exit to menu&nbsp;
//Add options menu&nbsp;
    //Select box color&nbsp;
    //Cursor color&nbsp;
    //Syntax highlighting, add options&nbsp;
    //Line number&nbsp;
//Add labels box, jump to/paste&nbsp;
//Add symbol selector&nbsp;
//Add useful call selector&nbsp;
//Fix line numbers, fixed size, 3 digits?&nbsp;
//tabs for multiple files&nbsp;

//Assembler&nbsp;
//-------------------&nbsp;
//Errors&nbsp;
    //draw gui&nbsp;
        //show line number and error&nbsp;
    //No label defined&nbsp;
    //No ret&nbsp;
    //call address not on defined&nbsp;
    //labels need to have :&nbsp;
//Display bar for progress&nbsp;
//Doesn't assembler if any errors&nbsp;
//.db, .dw, .BYTE, .WORD&nbsp;
    //string parsing&nbsp;
    //value parsing&nbsp;
    //each seperated by ,&nbsp;
//#define, .equ&nbsp;
//Add rest of the opcodes&nbsp;
//Program is a locked file
