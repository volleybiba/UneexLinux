#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DX 7
#define DY 3

#define MAX_LINES 10
#define BUF_SIZE 200

int main(int argc, char *argv[]) {
        WINDOW *frame, *win;
        int c = 0;
        FILE *file = fopen(argv[1], "r");
        char **lines = NULL;
        char buffer[BUF_SIZE];
        int buf_size = BUF_SIZE, line_count = 0, cur_line = 0, start_line = 0, start_col = 0, cur_col = 0;
        

        setlocale(LC_ALL, "");
        initscr();
        noecho();
        cbreak();
        printw("%s", argv[1]);
        refresh();

        frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
        box(frame, 0, 0);
        mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), "");
        wrefresh(frame);
        
        win = newwin(LINES - 2*DY - 2, COLS - 2*DX-2, DY+1, DX+1);
        keypad(win, TRUE);
        scrollok (win, TRUE);
        
        while (fgets(buffer, buf_size, file)) {
                lines = realloc(lines, sizeof(char*) * (line_count + 1));
                lines[line_count] = strdup(buffer);
                line_count++;
        }
        fclose(file);
        
        for (cur_line = start_line; cur_line < start_line + LINES - 2*DY - 3 && cur_line < line_count; cur_line++) {
                wprintw(win, "%4d: ", cur_line + 1);
                for (cur_col = start_col; cur_col < start_col + COLS - 2*DX - 8 && cur_col < strlen(lines[cur_line]); cur_col++) {
                        wprintw(win, "%c", lines[cur_line][cur_col]);
                }
                //if (lines[cur_line][cur_col - 1] != '\n')
                  //      wprintw(win, "\n");
        }
        
        while((c = wgetch(win)) != 27) {
                werase(win);
                if ((c == 258 || c == 32) && start_line < line_count - LINES + 2*DY + 3)
                        start_line++;
                else if (c == 338) {
                        if (cur_line < line_count - LINES + 2*DY + 3)
                                start_line = cur_line;
                        else
                                start_line = line_count - LINES + 2*DY + 3;
                }
                else if (c == 259 && start_line > 0)
                        start_line--;
                else if (c == 339) {
                        if (start_line >= LINES - 2*DY - 3) 
                                start_line = start_line - LINES + 2*DY + 3;
                        else
                                start_line = 0;
                }
                else if (c == 261)
                        start_col++;
                else if (c == 260 && start_col > 0)
                        start_col--;
                for (cur_line = start_line; cur_line < start_line + LINES - 2*DY - 3 && cur_line < line_count; cur_line++) {
                        wprintw(win, "%4d: ", cur_line + 1);
                        for (cur_col = start_col; cur_col < start_col + COLS - 2*DX - 8 && cur_col < strlen(lines[cur_line]); cur_col++) {
                                wprintw(win, "%c", lines[cur_line][cur_col]);
                        }
                        if (strlen(lines[cur_line]) <= start_col)
                                wprintw(win, "\n");
                }
        }
                
        delwin(win);
        delwin(frame);
        endwin();
        return 0;
}
