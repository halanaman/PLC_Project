#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "page.h"

RenderedBlocks *create_blocks(int numBlocks) {
    RenderedBlocks *renderedBlocks;
    if (numBlocks < 1) return NULL;

    renderedBlocks = malloc(sizeof(RenderedBlocks));
    if (!renderedBlocks) return NULL;

    renderedBlocks->rowToRenderEveryBlock = calloc(numBlocks, sizeof(int));
    if (!renderedBlocks->rowToRenderEveryBlock) {
        free_blocks(renderedBlocks);
        return NULL;
    }

    renderedBlocks->blocks = malloc(numBlocks * sizeof(RenderedBlock));
    if (!renderedBlocks->blocks) {
        free_blocks(renderedBlocks);
        return NULL;
    }
    renderedBlocks->numBlocks = numBlocks;

    return renderedBlocks;
}

void add_block_to_blocks(int index, RenderedBlocks *renderedBlocks, int rowToRenderBlock, int numRows, int numCols, DisplayStrings displayText) {
    int i;
    RenderedBlock *block;

    if (check_memory_allocation_blocks(renderedBlocks) != 0) return;
    if (index < 0 || index >= renderedBlocks->numBlocks) return; 

    if (rowToRenderBlock + numRows > MAX_BLOCK_HEIGHT) return;
    renderedBlocks->rowToRenderEveryBlock[index] = rowToRenderBlock;
    
    block = &renderedBlocks->blocks[index];
    block->numRows = numRows;
    block->numCols = numCols;
    for (i = 0; i < numRows; i++) {
        strcpy(block->displayedText[i], displayText[i]);
    }
}

int check_memory_allocation_blocks(RenderedBlocks *renderedBlocks) {
    if (!renderedBlocks || !renderedBlocks->blocks || !renderedBlocks->rowToRenderEveryBlock)
        return 1;
    return 0;
}

void free_blocks(RenderedBlocks *renderedBlocks) {
    if (!renderedBlocks) return;
    if (renderedBlocks->blocks) 
        free(renderedBlocks->blocks);
    if (renderedBlocks->rowToRenderEveryBlock) 
        free(renderedBlocks->rowToRenderEveryBlock);
    free(renderedBlocks);
}

Page *create_page(char *name, RenderedBlocks *renderedBlocks) {
    Page *page = malloc(sizeof(Page));
    if (!page || check_memory_allocation_blocks(renderedBlocks) != 0) return NULL;

    page->name = name;
    page->renderedBlocks = renderedBlocks;
    return page;
}

void free_page(Page *page) {
    if (page) {
        free_blocks(page->renderedBlocks);
        free(page);
    }
}

void render_block(RenderedBlock *block) {
    int i;
    for (i = 0; i < block->numRows; i++) {
        /*
        int displayWidth = get_display_width(block.displayedText[i]);
        if (displayWidth > maxWidth) {
            maxWidth = displayWidth; // Store the maximum width found
        }
        */
        printf("%s%s", LEFT_PADDING , block->displayedText[i]);
    }
}

void render_blocks(RenderedBlocks *renderedBlocks) {
    int i, currentLine, nextLine;
    RenderedBlock *blocks;
    if (check_memory_allocation_blocks(renderedBlocks) != 0) return;

    currentLine = 0;
    blocks = renderedBlocks->blocks;
    for (i = 0; i < renderedBlocks->numBlocks; i++) {
        nextLine = renderedBlocks->rowToRenderEveryBlock[i];
        while (nextLine > currentLine) {
            printf("\n");
            currentLine++;
        }
        render_block(&blocks[i]);
        currentLine += blocks[i].numRows;
    }
    /* Last 2 slots reserved for error and input text*/
    while (currentLine < MAX_BLOCK_HEIGHT) {
        printf("\n");
        currentLine++;
    }
}

void render_page(Page *page) {
    if (!page) return;
    clear_screen();
    render_blocks(page->renderedBlocks);
    free_page(page);
}

void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int get_display_width(const char *str) {
    int i, w, width;
    wchar_t wideStr[100];   /*Temporary buffer*/
    setlocale(LC_ALL, "");  /*Enable UTF-8 handling*/
    mbstowcs(wideStr, str, 100); /*Convert UTF-8 string to wide characters*/

    width = 0;
    for (i = 0; wideStr[i] != L'\0'; i++) {
        w = wcwidth(wideStr[i]);
        if (w > 0) width += w;  /*Count only valid display characters*/
    }
    return width;
}
