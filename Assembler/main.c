/*
Sets up graphic settings,
Runs main editor window
Assembles and quits
*/

#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <string.h>
#include <keypadc.h>
#include <fileioc.h>
#include "Editor.h"
#include "Assembler.h"
#include "Functions.h"
#include "Data.h"

//TODO:
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

int main(void)
{
    /* Initialize graphics drawing */
    gfx_Begin();
    //open up main menu
    //textEditor();    
    void (*main_fun_ptrs[])(void *data) = {label_func, test, null, null, quit_edit};
    editor(main_fun_ptrs, 1, 0, "Program: Hello", 0, 0, LCD_WIDTH, LCD_HEIGHT - 20, 14, 12, strs, main_label, 1, 1);
    assembler();

    gfx_End();
    return 0;
}



