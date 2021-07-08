
void assembler() {
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    gfx_SetTextTransparentColor(255);
    //draw_rect(true, 0, 0, LCD_WIDTH, LCD_HEIGHT, 255);
    //gfx_SetTextXY(2, 2);
    //gfx_PrintString("Pass 1");

    char opcodes[] = {"LD ld PUSH push POP pop ADD add MLT mlt INC inc CALL call RET ret"};
    char pair_Regs[] = {"BCbcDEdeHLhlSPspIXixIYiy"};
    char regs[] = {"AaBbCcDdEeHhLlIiRr"};
    //load memory
    char tokens[5][10] = {'0'};
    char ins[3][10] = {'0'};
    int offset = 0;
    int labels = 0;
    int p_line = 0;
    int addressing = 3;

    ti_var_t var;
    ti_CloseAll();

    char line_hex[20];
    var = ti_OpenVar(prog_name, "w", TI_PRGM_TYPE);
    //char newline[] = "\x3F";
    ti_Write("\xEF\x7a\x3F", 3, 1, var); //tAsmCePrgm//newline
    
    char delim[] = " ,";
    char *ptr;
    int pos;
    int loc_counter;
    char copy[prog_size][35];

    for (int pass = 0; pass < 2; ++pass) {    
        line_counter = 0;
        loc_counter = 0;
        draw_rect(true, 0, 0, LCD_WIDTH, LCD_HEIGHT, 255);
        gfx_SetTextXY(2, 2);
        gfx_PrintString("Pass ");
        gfx_PrintUInt(pass + 1, 1);
        memcpy(copy, strs, sizeof(copy));

        while(line_counter < prog_size) {
            memset(tokens, 0, sizeof tokens);
            //memset(ins, 0, sizeof ins);
            line_counter++;
            //char token[10];
            //split into tokens
            //ptr = strtok(strs + line_counter - 1, delim);
            ptr = strtok(copy + line_counter - 1, delim);
            pos = 0;
            while(ptr != NULL)
            {
                //push token into array
                //tokens[pos] = ptr;
                strcpy(tokens[pos], ptr);
                pos += 1; 
                if (ptr[0] == '#') break;
                if (ptr[0] != ' ')
                    ptr = strtok(NULL, delim);
                if (pos > prog_size) ptr = NULL;
            }
            draw_rect(false, 0, 20, LCD_WIDTH, LCD_HEIGHT, 255);
            gfx_SetTextXY(2, 30);

            if (!pass) { //first pass load mem table
                char *s = strstr(opcodes, tokens[0]);
                if (s != NULL) {
                    offset += 1; //1 byte added
                    gfx_PrintString("Instruction>");
                    gfx_SetTextXY(2, 50);
                    gfx_PrintString(tokens[0]);
                    gfx_SetTextXY(2, 70);
                    gfx_PrintString(tokens[1]);
                    gfx_SetTextXY(2, 90);
                    gfx_PrintString(tokens[2]);
                    //check arg1 for size
                    char *reg2 = strstr(pair_Regs, tokens[1]);
                    char *reg1 = strstr(regs, tokens[1]);
                    int strT1 = strlen(tokens[1]);
                    if (reg2 != NULL && strT1) {
                        //2 pair reg found
                        offset += 3;
                        gfx_SetTextXY(2, 110);
                        gfx_PrintString("3 byte arg");
                        //3 bytes added for tokens[2] value
                    } else if (reg1 != NULL && strT1) {
                        //regular register found
                        offset += 1; //1 byte added
                        gfx_SetTextXY(2, 110);
                        gfx_PrintString("1 byte arg");
                    } else if (strT1) {
                        gfx_SetTextXY(2, 110);
                        gfx_PrintString("3 byte label arg");
                        offset += 3; 
                    }
                } else if (!strcmp(tokens[0], ".db") || !strcmp(tokens[0], ".DB")) {
                    gfx_SetTextXY(2, 30);
                    gfx_PrintString("Directive>");
                    gfx_SetTextXY(2, 50);
                    int p = 0;
                    int len = 0;
                    while(strcmp(tokens[p], "")) {
                        if (p) len += strlen(tokens[p]) + 1;
                        gfx_PrintString(strcat(tokens[p++], " "));
                    }
                    len -= 3;
                    offset += len; 
                    gfx_SetTextXY(2, 70);
                    gfx_PrintUInt(len, 1);
                    gfx_PrintString(" bytes");
                } else {
                    gfx_SetTextXY(2, 30);
                    gfx_PrintString("Label>");
                    gfx_SetTextXY(2, 50);
                    gfx_PrintString(tokens[0]);
                    gfx_SetTextXY(2, 70);
                    gfx_PrintUInt(offset, 1);
                    //add label to sym_table
                    //sym_label[labels] = tokens[0];
                    //memcpy(tokens[0], tokens[0], strlen(tokens[0])-1); 
                    tokens[0][strlen(tokens[0]) - 1] = '\0'; 
                    strcpy(sym_label[labels], tokens[0]);
                    sym_address[labels++] = offset;
                } //else if directives
                //while(getkey() != 21) {}
                //while(getkey() != 105) {}
            } 
            else { //load memory
                if (!strcmp(tokens[0], "LD") || !strcmp(tokens[0], "ld")) {
                    gfx_PrintString("Load instruction>");
                    //check all types of LD
                    line_hex[0] = '2';
                    line_hex[1] = '1';
                    int l = get_Table_lookup(tokens[2]);
                    gfx_SetTextXY(2, 50);
                    gfx_PrintString("LD HL, ");
                    //gfx_PrintUInt(l, 1);
                    //D1 A8 81 + label offset
                    //then little endian
                    char str[(int)((ceil(log10(base + l))+1)*sizeof(char))];
                    sprintf(str, "%X", base + l);
                    gfx_PrintString(str);
                    line_hex[2] = str[4]; 
                    line_hex[3] = str[5];
                    line_hex[4] = str[2];
                    line_hex[5] = str[3];
                    line_hex[6] = str[0];
                    line_hex[7] = str[1];
                    if (l > -1) ti_Write(line_hex, 8, 1, var);
                    ti_Write("\x3F", 1, 1, var);
                } else if (!strcmp(tokens[0], "CALL") || !strcmp(tokens[0], "call")) {
                    line_hex[0] = 'C';
                    line_hex[1] = 'D';
                    //get value from define
                    line_hex[2] = 'C';
                    line_hex[3] = '0';
                    line_hex[4] = '0';
                    line_hex[5] = '7';
                    line_hex[6] = '0';
                    line_hex[7] = '2';
                    ti_Write(line_hex, 8, 1, var);
                    ti_Write("\x3F", 1, 1, var);
                } else if (!strcmp(tokens[0], "ret") || !strcmp(tokens[0], "RET")) {
                    ti_Write("C9\x3F", 3, 1, var); //ret
                } else if (!strcmp(tokens[0], ".db") || !strcmp(tokens[0], ".DB")) {
                    ti_Write("48656C6C6F2C20776F726C642100", 28, 1, var); //ret
                }
                //while(getkey() != 21) {}
                //while(getkey() != 105) {}
            }
            //while(getkey() != 21) {}
            //while(getkey() != 105) {}
        } //end line < prog_size
    }
    ti_CloseAll();
}
