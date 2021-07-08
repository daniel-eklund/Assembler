//buffer for global arrays
char *labels[25] = {"\0"};

//in_type: 0: can't be null, 1: normal
uint8_t top_line = 1;
uint8_t selected = 1;
bool line_nums = false;
int prog_size = 14; //23
int scale = 0;

const int QUIT = 15;

char copy_buff[32];
char t_buf[32];
char program[1000];
char prog_name[] = "HELLO";

//ASSEMBLER GLOBALS
int start_val = -1;
int line_counter = 0; //for errors
char line[20]; //global for errors
bool no_errors = true;
bool debug = false;
char sym_label[20][15] = {"0"};
int sym_address[20];
int base = 0xD1A881;
int search_line = 0;

int mini_x = 20;
int mini_y = 40;
int mini_width = LCD_WIDTH - 40;
int mini_height = LCD_HEIGHT - 87;
int mini_num_lines = 8;

char main_label[5][8] = {
        "Labels",
        "Test",
        "Chars",
        "Ins",
        "Done"
};

void load_Imem(int val, int loc);
void load_Cmem(char val, int loc); 

//char strs[NUMBER_OF_STRINGS][STRING_LENGTH+1];
char *strs[] = { //static mem, allocate enough mem on calc
            "start:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", //0
            "   ld  hl, helloTxt\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", //1 + 3
            "   call _PutS\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", //1 + 3
            "   ret\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", //1
            "helloTxt:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "test1:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "test:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "a:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "b:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "c:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "d:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "helloworld:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "f:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
            "g:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
};
    /*"gfx_AllocSprite:", 
                    "   ld        bc, 3", 
                    "   push   bc", 
                    "   pop     hl", 
                    "   add     hl, sp", 
                    "   ld         e, (hl)",
                    "   add     hl, bc", 
                    "   ld         d, (hl)", 
                    "   add     hl, bc",
                    "   ld          hl, (hl)", 
                    "   push   de",
                    "   mlt      de",
                    "   inc      de", 
                    "   inc      de", 
                    "   push   de", 
                    "   call     _indcallHL", 
                    "   pop     de",
                    "   add     hl, de",
                    "   sbc     hl, de",
                    "   pop     de",
                    "   ret     z",
                    "   ld          (hl), de",
                    "   ret" }; //change to dynamic allocation*/