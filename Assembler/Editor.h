int editor(int (*fptrs[])(void *data), int topbar, int box_type, char* name[], int xpos, int ypos, int width, int height, int size, int num_lines, char* arr_mem, char labels[5][8], int type, int in_type) {
    //arr_mem should be declared as
    //char *name[size] = {}
    //255 white
    //0 black
    //height = (num_lines-topbar) * 18;
    height = (18*topbar+17*num_lines)-2;

    int r = strlen(arr_mem);
    //copy arr_mem into temp
    memset(t_buf, '\0', 32);
    strncpy(t_buf, arr_mem, r);

    gfx_SetColor(255); //erase everything
    gfx_FillRectangle_NoClip(xpos, ypos, width, height);
    
    gfx_SetColor(0);
    /*for (int b = 1; b <= box_type; ++b) 
        gfx_Rectangle_NoClip(xpos-b+1, ypos-b+3, width+(2*b)-2, height+(2*b)-2);
    */
    for (int b = 0; b < box_type; ++b) 
        gfx_Rectangle_NoClip(xpos-b, ypos-b+2, width+(2*b), height+(2*b));
    
    gfx_HorizLine_NoClip(xpos, ypos, width);
    bool run = true;
    int Key_val = 1000;
    int last_key = 105;
    int input_val = 0;
    int sel = 1;
    int top = 1;
    num_lines -= 1;
    int reset_key = 1;

    int offset = 0;

    if (topbar) {
        offset = 17;
        draw_topXY(name, xpos, ypos, width);
    }

    int ystart = ypos + box_type + offset + 1;
    if (box_type == 0) {
        xpos--;
        width+=2;
    } else {
        ystart -= box_type;
    }

    gfx_SetTextScale(1, 2 + scale);
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    gfx_SetTextTransparentColor(255);
    
    //draw text
    /*
    int line = 0;
    int total = 0;
    for(uint8_t y = ystart; y < LCD_HEIGHT - 10 - ypos && line < size; y += 17)
        print_line_xy(xpos + 5, y, line++, arr_mem);*/
    print_lines(arr_mem, xpos, ystart, ypos, size, 0);
    //draw top line for single line boxes
    if (size == 1) print_top_line(arr_mem, xpos, ypos);    

    selected_boxXYZ(xpos, sel + topbar, width, ypos);
    int key_timer = 0;
    options_bar(labels);

    int a = 0;

    while (run) {
        if (reset_key)
            if (getkey() == -1) reset_key = 0;
        if (!input_val && !reset_key) {
            Key_val = getkey();
        } else {
            Key_val = input_val;
            last_key = 0;
        }
        //Auto select
        /*FIX: Doesn't allow extra button input
        if (size == 1 && !a) {
            input_val = 1;
            Key_val = 105;
            a = 1;
        }*/
        if (Key_val == 11 && last_key != 11) {
            //Y-Equals
            //draw table
            int ret = fptrs[0](sel+top-2);
            if (!ret) run = false;
            //if (ret || !ret) {
            if (ret != 3) {
                gfx_SetColor(255);
                gfx_FillRectangle_NoClip(xpos+1, ypos+(18*topbar)+1, width-2, height-(18*topbar)-2);
                print_lines(arr_mem, xpos, ystart, ypos, size, top-1);
                selected_boxXYZ(xpos, sel + topbar, width, ypos);
                options_bar(labels);
            }
            last_key = 105;
            reset_key = 1;
        } else if (Key_val == 12 && last_key != 12) {
            //send current string over
            //char* send[12] = {'\0'};
            //strncpy(send, arr_mem[0], 12);
            int ret = fptrs[1](sel+top-2);
            if (!ret) run = false;
            if (ret != 3) {
                gfx_SetColor(255);
                gfx_FillRectangle_NoClip(xpos+1, ypos+(18*topbar)+1, width-2, height-(18*topbar)-2);
                print_lines(arr_mem, xpos, ystart, ypos, size, top-1);
                selected_boxXYZ(xpos, sel + topbar, width, ypos);
                options_bar(labels);
            }
            last_key = 105;
            reset_key = 1;
        } else if (Key_val == 13 && last_key != 13) {
            int ret = fptrs[2](sel+top-2);
            if (!ret) run = false;
            if (ret != 3) {
                gfx_SetColor(255);
                gfx_FillRectangle_NoClip(xpos+1, ypos+(18*topbar)+1, width-2, height-(18*topbar)-2);
                print_lines(arr_mem, xpos, ystart, ypos, size, top-1);
                selected_boxXYZ(xpos, sel + topbar, width, ypos);
                options_bar(labels);
            }
            last_key = 105;
            reset_key = 1;
        }
        if (Key_val >= 0 && last_key != Key_val) { // && last_key != Key_val
            if (Key_val == 25) { //Moving up
                if (sel > 1) {
                    //if bottomed && > 1/2 down
                    if (top + num_lines <= size && sel >= size/2) {
                        clear_selected_boxXYZ(xpos, sel+topbar, width, ypos);
                        sel -= 1;
                        selected_boxXYZ(xpos, sel+topbar, width, ypos);
                        if (sel == 11) {//if at max screen size
                            gfx_SetColor(0);
                            gfx_HorizLine_NoClip(1, LCD_HEIGHT - 19, LCD_WIDTH-2);
                        }
                    } else if (top > 1) {
                        shift_downXY(xpos, ypos, width, height, num_lines, sel+topbar, top-2, topbar, arr_mem);
                        top--;
                        selected_boxXYZ(xpos, sel+topbar, width, ypos);
                    } else {
                        //top is 1
                        clear_selected_boxXYZ(xpos, sel+topbar, width, ypos);
                        sel -= 1;
                        selected_boxXYZ(xpos, sel+topbar, width, ypos);
                    }
                }
            }
            else if (Key_val == 34) { //Moving down
                if (top + num_lines < size) {
                    if (top == 1 && sel <= num_lines/2) { //stay in spot
                        clear_selected_boxXYZ(xpos, sel+topbar, width, ypos);
                        sel += 1;
                        selected_boxXYZ(xpos, sel+topbar, width, ypos);
                    } else {
                        shift_upXY(xpos, ypos, width, height, num_lines, sel+topbar, top+num_lines, topbar, arr_mem);
                        top++;
                        selected_boxXYZ(xpos, sel+topbar, width, ypos);
                    }
                } else if (sel < num_lines + topbar && sel < size) {
                    clear_selected_boxXYZ(xpos, sel+topbar, width, ypos);
                    sel += 1;
                    selected_boxXYZ(xpos, sel+topbar, width, ypos);
                }
            } 
            if (input_val > 0) {
                Key_val = 105;
            }
            if ((Key_val == 21 || Key_val == 105) && type==1) { //2nd
                //Custom input routine here
                //input_val = 
                //arr_mem[sel+1]
                a = txt_inputXY(xpos, ypos+sel*17, arr_mem, sel+top-2, in_type, num_lines);
                Key_val = 105;
            } else if (Key_val == QUIT) {
                int rt = fptrs[4](sel+top-2);
                if (rt < 1) run = false; 
                //run = false; //quit function
            }
        }  
        last_key = Key_val;
    }
    //return line num for usage
    print_line_xy(100, 100, 0, arr_mem);
    print_line_xy(100, 120, 0, t_buf);
    if (!strncmp(arr_mem, t_buf, r) && a!=-5) return -2;

    return sel;
}
