//void options_bar(char l1[], char l2[], char l3[], char l4[], char l5[]) {
void options_bar(char label[5][8]) { 
    gfx_SetColor(255);
    gfx_FillRectangle_NoClip(0, LCD_HEIGHT - 17, LCD_WIDTH, 20);
    gfx_SetColor(0);
    gfx_HorizLine(0, LCD_HEIGHT - 18, LCD_WIDTH);
    gfx_HorizLine(1, LCD_HEIGHT - 19, LCD_WIDTH-2);
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    gfx_SetTextTransparentColor(255);
    gfx_SetTextScale(1,2);
    int len = LCD_WIDTH / 5;
    int offset = 0;
    for (int x = 0; x < 5; ++x) {
        offset = (64 - gfx_GetStringWidth(label[x])) / 2;
        gfx_SetTextXY((64 * x) + offset, LCD_HEIGHT - 16);
        gfx_PrintString(label[x]);
        //draw each vert line
        gfx_VertLine_NoClip(64 + (64 * x) + 1, LCD_HEIGHT - 18, 18);
        gfx_VertLine_NoClip(64 + (64 * x), LCD_HEIGHT - 18, 18);
    }
    gfx_VertLine_NoClip(LCD_WIDTH - 1, LCD_HEIGHT - 18, 18);
    gfx_VertLine_NoClip(LCD_WIDTH - 2, LCD_HEIGHT - 18, 18);
}

int charLoc(char * str, char c) {
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c) return i;
    return -1;        
}

void print_line_xy(int xpos, int ypos, int ar_val, char *arr_mem[]) {
    gfx_SetTextXY(xpos, ypos);
    gfx_PrintString(arr_mem[ar_val]);
}

void selected_boxXYZ(int xpos, int select, int width, int top) {
    gfx_SetColor(100);
    gfx_Rectangle_NoClip(xpos+1, top + 17*select-18, width-2, 18);
    gfx_Rectangle_NoClip(xpos+1, top + 17*select-17, width-2, 18);
}

void clear_selected_boxXYZ(int xpos, int select, int width, int top) {
    gfx_SetColor(255);
    gfx_Rectangle_NoClip(xpos+1, top + 17*select-18, width-2, 18);
    gfx_Rectangle_NoClip(xpos+1, top + 17*select-17, width-2, 18);   
}

void draw_topXY(char* msg[], int xpos, int ypos, int width) {
    gfx_SetTextScale(1, 2);
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(255);
    draw_rect(true, xpos, ypos + 1, width, 16, 0);
    //Top text
    gfx_SetTextTransparentColor(0); 
    gfx_PrintStringXY(msg, xpos + (width / 2) - (gfx_GetStringWidth(msg) / 2), ypos + 1);
}

void shift_downXY(int xpos, int ypos, int width, int height, int tot, int pos, int sel, int topbar, char* arr_mem[]) {
    int mpos = sel;
    if (!topbar) mpos += 1;
    clear_selected_boxXYZ(xpos, pos+topbar-1, width, ypos);
    gfx_SetClipRegion(xpos+1, ypos+(18*topbar), xpos+width-2, ypos+(18*topbar)+(tot*17)+(17*topbar)-1);
    gfx_ShiftDown(17);
    draw_rect(true, xpos+1, ypos+(18*topbar), width-2, 17, 255);
    print_line_xy(xpos+5, ypos+(18*topbar), mpos, arr_mem);
}

void shift_upXY(int xpos, int ypos, int width, int height, int tot, int pos, int sel, int topbar, char* arr_mem[]) {
    int mpos = sel;
    if (!topbar) mpos += 1;
    clear_selected_boxXYZ(xpos, pos+topbar-1, width, ypos); //height + 37
    gfx_SetClipRegion(xpos+1, ypos+(18*topbar), xpos+width-2, ypos+(18*topbar)+(tot*17)+(17*topbar)-1);
    draw_rect(true, xpos+1, ypos+(18*topbar)+(17*tot)+15, width-2, 1, 255);
    gfx_ShiftUp(17);
    draw_rect(true, xpos+1, ypos+height-18, width-2, 17, 255);
    gfx_SetColor(0);
    gfx_HorizLine_NoClip(xpos+2, ypos+height+1, width-4);
    print_line_xy(xpos+5, ypos+(18*topbar)+(17*tot), mpos, arr_mem);
} 

int null(void *data) {return 3;} //returns blank button

int jump(void *data) {
    char *cstr;
    cstr = data;
    gfx_SetTextXY(100, 100);
    gfx_PrintString(cstr);
    while(getkey()!=105) {}
    return 1;
}

int quit() {return 0;} //function to handle exit keys
int quit_edit() {
    char *tstrs[] = {
            "Yes",
            "No"
        };
    char tl[5][8] = {
        "Confirm",
        "",
        "",
        "",
        "Back",
    };
    int (*labelFptrs[])(void *data) = {null, null, null, null, null};
    int l = editor(labelFptrs, 1, 1, "Exit to main menu?", LCD_WIDTH/2 - mini_width/4, mini_y*2, mini_width/2, 85, 2, 2, tstrs, tl, 0, 1);
    debugINT(l);
    while(getkey()!=14) {}
    return -1; //EXIT !
}

int rename(int data) {
    char *rstr[1] = {"\0"}; 
    rstr[0] = labels[data];
    char rl[5][8] = {
        "Rename","","","","Exit",
    };
    int (*rFptrs[])(void *data) = {quit, null, null, null, null};
    int l = editor(rFptrs, 1, 1, "Rename: " , LCD_WIDTH/2 - mini_width/4, mini_y*2, mini_width/2, 35, 1, 1, rstr, rl, 1, 0);
    //TODO: Test if string is same as before
    if (getkey() == QUIT) l = 0;
    debugINT(l);
    if (l == -2) {
        //no change
        char eMsg[2][32] = {
            "No change detected\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "Label name not changed\0\0\0\0\0\0\0\0\0\0"
        };
        char rl[5][8] = {
            "","","","","Back",
        };
        txt_box(1, 1, "Notice!", 2, eMsg, rl);
        return 1;
    }
    while(getkey()!=QUIT) {}
    return 1;
}

int test(void *data) {
    char *tstrs[] = {
            "This is", //0
            "me just testing", //1 + 3
            "the editor", //1 + 3
            "routine. Making", //1
            "sure it works",
            "on all shapes",
            "and sizes.",
            "I suppose it",
            "is working if",
            "you see all",
            "these lines way",
            "down here.",
            "Tada",
            "*bows*"
        };
    char tl[5][8] = {
        "Testing",
        "Random",
        "Box",
        "Things",
        "Exit",
    };
    int (*labelFptrs[])(void *data) = {null, null, null, null, null};
    editor(labelFptrs, 1, 3, "Test Box", LCD_WIDTH/2 - mini_width/4, mini_y*2, mini_width/2, 85, 14, 4, tstrs, tl, 0, 1);
    return 1;
}

int label_func(void *data) {
    int l = 0;
    int f = 0;
    char *s;
    //TODO: Paste, Jump, Rename
    //Paste
    char l1[5][8] = {
        "Test",
        "Jump",
        "Rename",
        " ",
        "Exit",
    };
    options_bar(l1);
    int localAdd[25];

    while(l < prog_size) {
        //if last char of string is :
        if (strs[l][strlen(strs[l]) - 1] == ':') {
            localAdd[f] = l;
            labels[f] = strcat(substr(strs[l], 0, charLoc(strs[l], ':')), "\0");
            ++f;
        }
        ++l;
    }
    int (*labelFptrs[])(void *data) = {test, null, rename, null, quit};
    editor(labelFptrs, 1, 1, "Labels", mini_x, mini_y, mini_width, mini_height, f, mini_num_lines, labels, l1, 0, 0);
    //redraw previous screen & exit
    //gfx_SetColor(255);
    //gfx_FillRectangle_NoClip(20, 40, LCD_WIDTH - 20, LCD_HEIGHT - 60);
    //last_key = 105;
    return 1;
}

void print_lines(char* arr_mem, int xpos, int ystart, int ypos, int size, int offset) {
    int line = 0;
    int total = 0;
    for(uint8_t y = ystart; y < LCD_HEIGHT - 10 - ypos && line + offset < size - 2; y += 17)
        print_line_xy(xpos + 5, y, line++, arr_mem + offset);
}

void print_top_line(char* arr_mem, int xpos, int ypos) {
    print_line_xy(xpos + 5, ypos + 18, 0, arr_mem);
}

int txt_box(int topbar, int box_type, char* name[], int size, char arr_mem[size][32], char labels[5][8]) {
    int mw = 0;
    int w = 0;
    //get largest string for box size
    for (int i=0; i < size; ++i) {
        int w = gfx_GetStringWidth(arr_mem[i]);
        if (w > mw) mw = w;  
    }

    int width = mw + 9;
    int height = 18*(size+topbar) - 2;
    
    int xpos = LCD_WIDTH/2 - width/2;
    int ypos = LCD_HEIGHT/3 - height/3;

    gfx_SetColor(255); //erase everything
    gfx_FillRectangle_NoClip(xpos-(box_type+1), ypos-(box_type+1), width+2*(box_type+1), height+1+2*(box_type+1));
    gfx_SetColor(0);

    for (int b = 0; b < box_type; ++b) 
        gfx_Rectangle_NoClip(xpos-b, ypos-b+2, width+(2*b), height+(2*b));
    
    //top of name bar
    gfx_HorizLine_NoClip(xpos, ypos, width);

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

    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    gfx_SetTextTransparentColor(255);

    for (int i = 0; i < size; ++i) {
        gfx_SetTextXY(xpos+5, ystart+(18*i));
        gfx_PrintString(arr_mem[i]);
    }

    options_bar(labels);
    //Ensure quit release
    while(getkey()==QUIT){}
    while(getkey()!=QUIT){}
}





int get_Table_lookup(char *search) {
    //loop through
    int loc = 0;
    int pos = -1;
    int LABEL_SIZE = 20;
    while(loc < LABEL_SIZE && pos < 0)
        if (!strcmp(sym_label[loc++], search)) pos = loc;
    if (pos < 0) return pos;
    return sym_address[pos-1];
}

char* substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    strncpy(dest, (src + m), len);
    return dest;
}

void load_Imem(int val, int loc) {
    if (no_errors) {
        for (int n = 0; n < 4; ++n) //get nth bit from i
            program[loc + n] = (val >> (8 * n)) & 0xff;
        // program[loc - 3 + n] = (val >> (8 * n)) & 0xff; //for flipped endianess
    }
}

void load_Cmem(char val, int loc) {
    if (no_errors)
        program[loc] = val;
}

void error_msg(char msg) {
    gfx_PrintStringXY(&msg, 0, LCD_HEIGHT - 17);
    no_errors = false;
}


//END OF ASSEMBLER FUNCTIONS


/*
void debugSTR(char &msg) {
    draw_top();
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(255);
    //Top text
    gfx_SetTextTransparentColor(0);
    gfx_PrintStringXY(msg, LCD_WIDTH - gfx_GetStringWidth(msg) - 2, 0);
}*/ 

void debugINT(uint8_t msg) {
    //draw_top();
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(255);
    //Top text
    gfx_SetTextTransparentColor(0);
    draw_rect(false, 285, 0, 30, 16, 0);
    gfx_SetTextXY(285, 0);
    gfx_PrintUInt(msg, 1);
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    //Top text
    gfx_SetTextTransparentColor(255);
} 

void debugCHAR(char msg) {
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(255);
    //Top text
    gfx_SetTextTransparentColor(0);
    draw_rect(false, 311, 0, 10, 16, 0);
    gfx_SetTextXY(311, 0);
    gfx_PrintChar(msg);
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    //Top text
    gfx_SetTextTransparentColor(255);
}

int txt_inputXY(int xpos, int ypos, char *arr_mem[], int sel, int type, int size) {
    int ret_val = 0;
    bool run = true;
    int key;
    int mode = 1; //normal
    debugCHAR(' ');

    char linetxt[32] = {'\0'};
    strcpy(linetxt, arr_mem[sel]);

    int cursor_pos = gfx_GetStringWidth(linetxt) + 5;

    //debugINT(gfx_GetStringWidth(arr_mem[sel]));
    int c_pos = strlen(linetxt);
    //draw cursor
    draw_cursorXY(xpos, ypos, cursor_pos);
    int blink_timer = 0;
    bool cur = true;
    int last_key = 105;
    char replace_char = ' ';
    int key_timer = 0;

    while (run) {
        key = getkey();
        if (key == 105 && last_key != 105) run = false;
        if (key == 11 || key == 12 || key == 13 || key == 14 || key == QUIT) run = false;
        if (key == 34 || key == 25 && last_key != 105) { 
            ret_val = key;
            run = false;
        }
        if (key == 24 && c_pos > 0 && key != last_key) {
            key_timer = 0;
            blink_timer = 199;
            cur = false; 
            uint8_t min = gfx_GetCharWidth(linetxt[c_pos - 1]);
            erase_cursorXY(xpos, ypos, cursor_pos, linetxt[c_pos], true);
            //update pos
            cursor_pos -= min;
            c_pos -= 1;
            //debugINT(min);
        } else if (key == 26 && c_pos < 34 && key != last_key) {
            key_timer = 0;
            blink_timer = 199;
            cur = false; 
            uint8_t min = gfx_GetCharWidth(linetxt[c_pos]);
            erase_cursorXY(xpos, ypos, cursor_pos, linetxt[c_pos], true);
            //update pos
            cursor_pos += min;
            c_pos += 1;
            //debugINT(min);
        } else if (key == 31 && key != last_key) {
            key_timer = 0;
            //cycle through alpha modes
            mode++;
            if (mode > 3) { 
                mode = 1;
                debugCHAR(' ');
            }
            if (mode == 2) debugCHAR('A');
            else if (mode == 3) debugCHAR('a');
        }else if (key != -1 && key != last_key) {
            key_timer = 0;
            char in_char = getChar(key, mode);
            bool update_txt = false;
            //debugCHAR(in_char);
            if (in_char == '~') { //pressed clear (erase/copy)
                //copy buffer over
                strcpy(copy_buff, linetxt);
                int sl = strlen(linetxt);
                for (int i = 0; i < sl; ++i) 
                    linetxt[i] = '\0';
                //TODO fix the strlen when using '/0' as end of
                erase_cursorXY(xpos, ypos, cursor_pos, linetxt[c_pos], true);    
                cursor_pos = 5;
                c_pos = 0;
                gfx_SetColor(255);
                //gfx_FillRectangle(cursor_pos, ypos+1, gfx_GetStringWidth(copy_buff), 15);
                gfx_FillRectangle(xpos+5, ypos+1, gfx_GetStringWidth(copy_buff), 15);
                draw_cursorXY(xpos, ypos, cursor_pos);
                //update_txt = true;
                //clear box
            } else if (in_char == '%') { //pressed sto (tab)
                //[S][t][a][r]>[t][:]
                //fix with just two chars
                //fix on end of string
                int sl = strlen(linetxt);
                for (int i = sl; i >= c_pos; --i) {
                    linetxt[i + 4] = linetxt[i];
                    linetxt[i] = ' ';
                }
                linetxt[sl + 4] = '\0';
                update_txt = true;
            } else if (in_char == '@') { //pressed del (erase 1 tok)
                //FIX!!!
                //last two chars don't wanna delete
                int sl = strlen(linetxt);
                //debugINT(sl);
                for(int i = c_pos; i < sl; ++i) 
                    linetxt[i] = linetxt[i+1]; 
                //linetxt[sl - 1] = '\0';
                update_txt = true;
            } else if (in_char != '&') {//insert char
                //erase character in c_pos
                int sl = strlen(linetxt);
                for(int i = sl; i > c_pos; --i)
                    linetxt[i] = linetxt[i - 1];
                linetxt[c_pos] = in_char;
                linetxt[sl + 1] = '\0';
                //reload line
                erase_cursorXY(xpos, ypos, cursor_pos, linetxt[c_pos], true);
                cursor_pos += gfx_GetCharWidth(in_char);
                c_pos += 1;
                update_txt = true;
                key = getkey();
            }
            if (update_txt) {
                //check if end of line
                //if (c_pos < strlen(linetxt) - 1) {
                    gfx_SetColor(255);
                    erase_cursorXY(xpos, ypos, cursor_pos, linetxt[c_pos], true);
                    int a = gfx_GetStringWidth(substr(linetxt, c_pos-1, strlen(linetxt)-1)) + 15;
                    //debugINT(a);
                    gfx_FillRectangle(xpos+5, ypos+1, a, 15);
                    gfx_SetTextXY(xpos+5, ypos+1);
                    gfx_PrintString(linetxt);
                    draw_cursorXY(xpos, ypos, cursor_pos);
                    gfx_SetColor(100);
                    //gfx_HorizLine(xpos, ypos+16, a);
                //}
            }
        }
        
        last_key = key;
        //blip cursor
        blink_timer++;
        if (blink_timer == 350 && cur) {
            blink_timer = 0; 
            erase_cursorXY(xpos, ypos, cursor_pos, linetxt[c_pos], true);
            cur = false;
        } else if (blink_timer == 200 && cur == false) {
            draw_cursorXY(xpos, ypos, cursor_pos);
            blink_timer = 0;
            cur = true; 
        }
        key_timer++;
        if (key_timer == 150) {
            last_key = -1;
            key_timer = 0;
        }

    }
    //end while 
    erase_cursorXY(xpos, ypos, cursor_pos, linetxt[c_pos], true);
    linetxt[strlen(linetxt)] = '\0';
    
    debugCHAR(' ');

    //erase all spaces on end
    for (int a = strlen(linetxt)-1; a > 0; --a) {
        if (linetxt[a] == ' ') {
            linetxt[a] = '\0';
        } else { 
            a = 0;
        }
    }

    //copy buffer back into data
    if (!type && !strlen(linetxt)) { //if type==0 && strlen() = 0
        //ERROR BOX:
        char eMsg[2][32] = {
            "Label name can't be empty\0\0\0\0\0\0\0",
            "Returning to previous name\0\0\0\0\0\0"
        };
        char rl[5][8] = {
            "","","","","Back",
        };
        txt_box(1, 1, "Error", 2, eMsg, rl);
        return -5;
    } else if (getkey()!=QUIT) {
        bool same = false;
        if (!type) {
            //check if same as another entry
            for(int i=0; i < size; ++i) {
                if (!strcmp(arr_mem[i], linetxt)) {
                    same = true;
                    i = size;
                }
            }
            if (same) {
                char eMsg[2][32] = {
                    "Duplicate name entered\0\0\0\0\0\0\0\0\0\0",
                    "Returning to previous name\0\0\0\0\0\0"
                };
                char rl[5][8] = {
                    "","","","","Back",
                };
                txt_box(1, 1, "Error", 2, eMsg, rl);
                return 1;   
            }
        }
        strcpy(arr_mem[sel], linetxt);   
    } 
    //gfx_SetTextXY(LCD_WIDTH/2 + 15, ypos+1);
    //gfx_PrintString(arr_mem[sel]);
    return ret_val;
}

void draw_cursor(int pos) {
    draw_rect(false, pos, 17 * selected + 1, 2, 15, 100);
}

void draw_cursorXY(int xpos, int ypos, int pos) {
    //debugINT(pos);
    draw_rect(false, xpos + pos, ypos+1, 2, 15, 100);
}

void erase_cursorXY(int xpos, int ypos, int pos, char replace, bool draw) {
    draw_rect(false, xpos + pos, ypos+1, 2, 15, 255);
    //replace char
    if (draw) {
        gfx_SetTextFGColor(0);
        gfx_SetTextBGColor(255);
        gfx_SetTextTransparentColor(255);
        gfx_SetTextXY(xpos + pos, ypos+1);
        gfx_PrintChar(replace);
    }
}

void erase_cursor(int pos, char replace, bool draw) {
    draw_rect(false, pos, 17 * selected + 1, 2, 15, 255);
    //replace char
    if (draw) {
        //selected_box();
        gfx_SetTextFGColor(0);
        gfx_SetTextBGColor(255);
        gfx_SetTextTransparentColor(255);
        gfx_SetTextXY(pos, 17 * selected + 2 - 1);
        gfx_PrintChar(replace);
    }
}

void draw_rect(bool clip, int x, int y, int w, int h, int color) {
    gfx_SetColor(color);
    gfx_SetDrawBuffer();
    if (clip) {
        gfx_FillRectangle(x, y, w, h);
    } else {
        gfx_FillRectangle_NoClip(x, y, w, h);
    }
    gfx_CopyRectangle(gfx_buffer, gfx_screen, x, y, x, y, w, h);
    gfx_SetDrawScreen();
}

int getkey() {
    kb_Scan();
    int val = -1;
    kb_key_t key;
    key = kb_Data[1];
    switch (key)
    {
        case kb_2nd:          
            val = 21;
            break;
        case kb_Del:         
            val = 23;
            break;
        case kb_Mode:
            val = 22;
            break;
        case kb_Graph:
            val = 15;
            break;
        case kb_Trace:
            val = 14;
            break;
        case kb_Zoom:
            val = 13;
            break;
        case kb_Window:
            val = 12;
            break;
        case kb_Yequ:
            val = 11;
            break;
        default:
            break;
    }
    key = kb_Data[3];
    switch (key)
    {
        case kb_0:          
            val = 102;
            break;
        case kb_1:         
            val = 92;
            break;
        case kb_4:             
            val = 82;
            break;
        case kb_7:           
            val = 72;
            break;
        case kb_Comma:
            val = 62;
            break;
        default:
            break;
    }
    key = kb_Data[2];
    switch (key)
    {
        case kb_Sto:          
            val = 91;
            break;
        case kb_Ln:         
            val = 81;
            break;
        case kb_Log:             
            val = 71;
            break;
        case kb_Square:           
            val = 61;
            break;
        case kb_Recip:
            val = 51;
            break;
        case kb_Math:
            val = 41;
            break;
        case kb_Alpha:
            val = 31;
            break;
        default:
            break;
    }
    key = kb_Data[3];
    switch (key)
    {
        case kb_0:          
            val = 102;
            break;
        case kb_1:         
            val = 92;
            break;
        case kb_4:             
            val = 82;
            break;
        case kb_7:           
            val = 72;
            break;
        case kb_Comma:
            val = 62;
            break;
        case kb_Sin:
            val = 52;
            break;
        case kb_Apps:
            val = 42;
            break;   
        default:
            break;
    }
    key = kb_Data[4];
    switch (key)
    {
        case kb_DecPnt:          
            val = 103;
            break;
        case kb_2:         
            val = 93;
            break;
        case kb_5:             
            val = 83;
            break;
        case kb_8:           
            val = 73;
            break;
        case kb_LParen:
            val = 63;
            break;
        case kb_Cos:
            val = 53;
            break;
        case kb_Prgm:
            val = 43;
            break;
        default:
            break;
    }
    key = kb_Data[5];
    switch (key) 
    {
        case kb_3:         
            val = 94;
            break;
        case kb_6:             
            val = 84;
            break;
        case kb_9:           
            val = 74;
            break;
        case kb_RParen:
            val = 64;
            break;
        case kb_Chs:
            val = 104;
            break;
        case kb_Tan:
            val = 54;
            break;
        case kb_Vars:
            val = 44;
            break;
        default:
            break;
    }
    key = kb_Data[6];
    switch (key)
    {
        case kb_Enter:         
            val = 105;
            break;
        case kb_Add:             
            val = 95;
            break;
        case kb_Sub:           
            val = 85;
            break;
        case kb_Mul:
            val = 75;
            break;
        case kb_Div:
            val = 65;
            break; 
        case kb_Clear:
            val = 45;
            break;
        case kb_Power:
            val = 55;
            break;  
        default:
            break;
    }
    key = kb_Data[7];
    switch (key) //arrows
    {
        case kb_Down:          
            val = 34;
            break;
        case kb_Right:         
            val = 26;
            break;
        case kb_Up:             
            val = 25;
            break;
        case kb_Left:           
            val = 24;
            break;
        default:
            break;
    }
    return val;
}

char getChar(int key, int mode) {
    char ret_char = '&';
    switch (mode) {
        case 1: //reg/num mode
            switch(key) {
                case 91:
                    ret_char = '%';
                    break;
                case 23:
                    ret_char = '@';
                    break;
                case 45:
                    ret_char = '~';
                    break;
                case 102: 
                    ret_char = '0';
                    break;
                case 103:
                    ret_char = '.';
                    break;
                case 104:
                    ret_char = '-';
                    break;
                case 92:
                    ret_char = '1';
                    break;
                case 93:
                    ret_char = '2';
                    break;
                case 94:
                    ret_char = '3';
                    break;
                case 95:
                    ret_char = '+';
                    break;
                case 82:
                    ret_char = '4';
                    break;
                case 83:
                    ret_char = '5';
                    break;
                case 84:
                    ret_char = '6';
                    break;
                case 85:
                    ret_char = '_';
                    break;
                case 72:
                    ret_char = '7';
                    break;
                case 73:
                    ret_char = '8';
                    break;
                case 74:
                    ret_char = '9';
                    break;
                case 75:
                    ret_char = '*';
                    break;
                case 62:
                    ret_char = ',';
                    break;
                case 63:
                    ret_char = '(';
                    break;
                case 64:
                    ret_char = ')';
                    break;
                case 65:
                    ret_char = '/';
                    break;
            }
            break;
        case 2: //Big alpha mode
            switch(key) {
            case 23:
                    ret_char = '@';
                    break;
            case 45:
                    ret_char = '~';
                    break;    
            case 41:
                    ret_char = 'A';
                    break;
            case 51:
                    ret_char = 'D';
                    break;
            case 61:
                    ret_char = 'I';
                    break;    
            case 71:
                    ret_char = 'N';
                    break;
            case 81:
                    ret_char = 'S';
                    break;
            case 91:
                    ret_char = 'X';
                    break;
            case 42:
                    ret_char = 'B';
                    break;
            case 52:
                    ret_char = 'E';
                    break;
            case 62:
                    ret_char = 'J';
                    break;    
            case 72:
                    ret_char = 'O';
                    break;
            case 82:
                    ret_char = 'T';
                    break;
            case 92:
                    ret_char = 'Y';
                    break;
            case 102:
                    ret_char = ' ';
                    break;
            case 43:
                    ret_char = 'C';
                    break;
            case 53:
                    ret_char = 'F';
                    break;
            case 63:
                    ret_char = 'K';
                    break;    
            case 73:
                    ret_char = 'P';
                    break;
            case 83:
                    ret_char = 'U';
                    break;
            case 93:
                    ret_char = 'Z';
                    break;
            case 103:
                    ret_char = ':';
                    break;
            case 54:
                    ret_char = 'G';
                    break;
            case 64:
                    ret_char = 'L';
                    break;    
            case 74:
                    ret_char = 'Q';
                    break;
            case 84:
                    ret_char = 'V';
                    break;
            case 104:
                    ret_char = '?';
                    break;
            case 55:
                    ret_char = 'H';
                    break;
            case 65:
                    ret_char = 'M';
                    break;    
            case 75:
                    ret_char = 'R';
                    break;
            case 85:
                    ret_char = 'W';
                    break;
            case 95:
                    ret_char = '"';
                    break;
            break;
            }
            break;
        case 3:
            switch(key) {
            case 23:
                    ret_char = '@';
                    break;    
            case 45:
                    ret_char = '~';
                    break;
            case 41:
                    ret_char = 'a';
                    break;
            case 51:
                    ret_char = 'd';
                    break;
            case 61:
                    ret_char = 'i';
                    break;    
            case 71:
                    ret_char = 'n';
                    break;
            case 81:
                    ret_char = 's';
                    break;
            case 91:
                    ret_char = 'x';
                    break;
            case 42:
                    ret_char = 'b';
                    break;
            case 52:
                    ret_char = 'e';
                    break;
            case 62:
                    ret_char = 'j';
                    break;    
            case 72:
                    ret_char = 'o';
                    break;
            case 82:
                    ret_char = 't';
                    break;
            case 92:
                    ret_char = 'y';
                    break;
            case 102:
                    ret_char = ' ';
                    break;
            case 43:
                    ret_char = 'c';
                    break;
            case 53:
                    ret_char = 'f';
                    break;
            case 63:
                    ret_char = 'k';
                    break;    
            case 73:
                    ret_char = 'p';
                    break;
            case 83:
                    ret_char = 'u';
                    break;
            case 93:
                    ret_char = 'z';
                    break;
            case 103:
                    ret_char = ':';
                    break;
            case 54:
                    ret_char = 'g';
                    break;
            case 64:
                    ret_char = 'l';
                    break;    
            case 74:
                    ret_char = 'q';
                    break;
            case 84:
                    ret_char = 'v';
                    break;
            case 104:
                    ret_char = '?';
                    break;
            case 55:
                    ret_char = 'h';
                    break;
            case 65:
                    ret_char = 'm';
                    break;    
            case 75:
                    ret_char = 'r';
                    break;
            case 85:
                    ret_char = 'w';
                    break;
            case 95:
                    ret_char = '"';
                    break;
            break;
            }
            break;
    }
    return ret_char;
}