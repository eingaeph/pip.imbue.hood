

// ## Find mode
/* =============================== Find mode ================================ */

#define KILO_QUERY_LEN 256

// This function handles the whole find-mode. The `fd` parameter is needed because this function will need to call editorReadKey and handle keypresses by itself (taking away control from the main "normal-mode" loop, and also calling editorRefreshScreen()`).
void editorFind(int fd) {
    char query[KILO_QUERY_LEN+1] = {0};
    int qlen = 0;
    int last_match = -1; /* Last line where a match was found. -1 for none. */
    int find_next = 0; /* if 1 search next, if -1 search prev. */
    int saved_hl_line = -1;  /* No saved HL */
    char *saved_hl = NULL;

// Macro to restore the hilighting of a whole row. The `do{}while(0)` is a common trick to wrap complex macros so that they don't interfeere with the surrounding code
//
// BUG: saved_hl is heap-allocated, but this function doesn't free it before setting its pointer to NULL, leading to a memory leak
#define FIND_RESTORE_HL do { \
    if (saved_hl) { \
        memcpy(E.row[saved_hl_line].hl,saved_hl, E.row[saved_hl_line].rsize); \
        saved_hl = NULL; \
    } \
} while (0)

    /* Save the cursor position in order to restore it later. */
    int saved_cx = E.cx, saved_cy = E.cy;
    int saved_coloff = E.coloff, saved_rowoff = E.rowoff;

    while(1) {
        editorSetStatusMessage(
            "Search: %s (Use ESC/Arrows/Enter)", query);
        editorRefreshScreen();

        // while in search mode, the keypresses are handled here. The keys allow to edit the query, go to the next/previous match, and exit find mode. 
        int c = editorReadKey(fd);
        if (c == DEL_KEY || c == CTRL_H || c == BACKSPACE) {
            if (qlen != 0) query[--qlen] = '\0';
            last_match = -1;
        } else if (c == ESC || c == ENTER) {
            if (c == ESC) {
                E.cx = saved_cx; E.cy = saved_cy;
                E.coloff = saved_coloff; E.rowoff = saved_rowoff;
            }
            FIND_RESTORE_HL;
            editorSetStatusMessage("");
            return;
        } else if (c == ARROW_RIGHT || c == ARROW_DOWN) {
            find_next = 1;
        } else if (c == ARROW_LEFT || c == ARROW_UP) {
            find_next = -1;
        } else if (isprint(c)) {
            if (qlen < KILO_QUERY_LEN) {
                query[qlen++] = c;
                query[qlen] = '\0';
                last_match = -1;
            }
        }

        /* Search occurrence. */
        if (last_match == -1) find_next = 1;
        if (find_next) {
            char *match = NULL;
            int match_offset = 0;
            int i, current = last_match;

            // `i` is only used as counter, to move `current`, the actual row-offset in the file, `E.numrows` times, covering all the rows
            for (i = 0; i < E.numrows; i++) {
                current += find_next;
                
                //handles wraparounds
                if (current == -1) current = E.numrows-1; 
                else if (current == E.numrows) current = 0;
                
                // checks if there's a match on this row. BUG: if the row contains a null char (they aren't handled in row.render by `editorUpdateRow`), only the first part of the row is searched
                match = strstr(E.row[current].render,query);
                if (match) {
                    // column where the match starts in the row
                    match_offset = match-E.row[current].render;
                    break;
                }
            }
            find_next = 0;

            /* Highlight */

            // restore hilighting for the previous matched row (if any)
            FIND_RESTORE_HL;

            if (match) {
                erow *row = &E.row[current];
                last_match = current;
                if (row->hl) {
                    saved_hl_line = current;
                    //BUG: saved_hl is allocated here, but never freed (should be done in the FIND_RESTORE_HL macro)
                    saved_hl = malloc(row->rsize);
                    memcpy(saved_hl,row->hl,row->rsize);
                    memset(row->hl+match_offset,HL_MATCH,qlen);
                }
                // move the cursor to the match, scroll vertically so that the first row is on the matched row, and then horizontally os that the cursor is on the screen
                E.cy = 0;
                E.cx = match_offset;
                E.rowoff = current;
                E.coloff = 0;
                /* Scroll horizontally as needed. */
                if (E.cx > E.screencols) {
                    int diff = E.cx - E.screencols;
                    E.cx -= diff;
                    E.coloff += diff;
                }
            }
        }
    }
}
