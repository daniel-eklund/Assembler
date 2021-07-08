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

Things currently to do:
//Main menu
    //Open project
    //Rename project/files
    //Add files
    //Delete files
    //Open file
    //Read & write appvars
//Editor
    //clear and restore previous page on exit
        //more than 1 val box_type is broken
    //fix and add box_type values
    //fix and add no label option

//Text editor
//-------------------
//Spaces are 3? pixels, versus 1
//Remove scroll on insert
//Add option buttons (Graph row) graphics
    //cut & paste
    //clear row
    //clear up to cursor
    //save & exit to menu
//Add options menu 
    //Select box color
    //Cursor color
    //Syntax highlighting, add options
    //Line number
//Add labels box, jump to/paste
//Add symbol selector
//Add useful call selector
//Fix line numbers, fixed size, 3 digits?
//tabs for multiple files

//Assembler
//-------------------
//Errors
    //draw gui
        //show line number and error
    //No label defined
    //No ret
    //call address not on defined
    //labels need to have :
//Display bar for progress
//Doesn't assembler if any errors
//.db, .dw, .BYTE, .WORD
    //string parsing
    //value parsing
    //each seperated by ,
//#define, .equ
//Add all the opcodes :D  
//; comments
//Program is a locked file
