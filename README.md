# Assembler

Note:
This is an **unfinished** project currently being developed.

This is an on-calc editor and ez80 compiler for the Ti-84+CE graphing calculator.
In order to compile build for yourself, you must download and install the CEDev toolchain,
this ensures you have the neccesarry binaries to compile C into assembly for the calculator.
Otherwise the "most up to date" Assembler.8xp is included for testing purposes. 

Currently redesigning the editor window to fix recursive calls to the main editor window
(currently nested input requires a lot of memory). Also working on dynamic memory versus a static 
partition on calculator.

Things currently to do:  
Main menu:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Open project    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Rename project/files  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Add files  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Delete files  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Open file  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Read & write appvars  
  
Editor:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-clear and restore previous page on exit    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-fix and add box_type values  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-fix and add no label option  
  
Text editor:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Spaces are 3 pixels, versus 1  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Remove scroll on insert  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Add option buttons (Graph row) graphics   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>cut & paste : Cut currently works  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>clear row : Done  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>clear up to cursor  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>save & exit to menu  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Add options menu  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Select box color  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>Cursor color  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>Syntax highlighting, add options   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>Line number : Looks bad right now  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Add labels box, jump to/paste : Jump works? Fix recursive returns  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Add symbol selector : Forgot what this means  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Add useful call selector  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Fix line numbers, fixed size, 3 digits?  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Tabs for multiple files : Forgot what this means  

Assembler:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Errors:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>draw gui : Done  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>show line number and error   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>No label defined : Working?   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>No ret  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>call address not on defined    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Display bar for progress  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Doesn't assembler if any errors : Done  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-.db, .dw, .BYTE, .WORD : Add directives  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>string parsing  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>value parsing  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-#defines  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Opcodes : Some are done  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-Program is a locked file
