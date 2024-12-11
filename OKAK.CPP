#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define X1 20
#define Y1 8
#define X2 60
#define Y2 18
#define SCROLL_LINES 1  // Number of lines to scroll up
#define DELAY_MS 900    // Delay in milliseconds

// Array of color names
const char* colorNames[] = {
    "Black", "Blue", "Green", "Cyan",
    "Red", "Magenta", "Brown", "Light Gray",
    "Dark Gray", "Light Blue", "Light Green", "Light Cyan",
    "Light Red", "Light Magenta", "Yellow", "White"
};

// Function to scroll the window up or down
void scrollWindow(int direction, int top, int bottom, int left, int right, int lines, int attr) {
    union REGS r;
    r.h.ah = (direction == 1) ? 0x06 : 0x07;  // 0x06 = scroll up, 0x07 = scroll down
    r.h.al = lines;  // Number of lines to scroll
    r.h.ch = top;    // Top row of the window
    r.h.cl = left;   // Left column of the window //MB WRONG
    r.h.dh = bottom-1; // Bottom row of the window //MB WRONG
    r.h.dl = right-1;  // Right column of the window
    r.h.bh = attr;   // Attribute for new lines
    int86(0x10, &r, &r);  // Call BIOS interrupt
}

// Function to print text with specific background and foreground colors
void printColorText(int bgColor, int textColor, int x, int y) {
    char buffer[50];
    sprintf(buffer, "%s %s", colorNames[bgColor], colorNames[textColor]);

    textcolor(textColor);         // Set text color
    textbackground(bgColor);      // Set background color

    gotoxy(x, y);                 // Move cursor to the desired position
    cprintf("%s", buffer);        // Print the text
}

// Function to clear the line at the given y-coordinate
void clearLine(int y, int x1, int x2) {
    gotoxy(x1, y);  // Move to the start of the line
    for (int x = x1; x <= x2; x++) {
        putch(' ');  // Clear character by character
    }
}

// Function to clear the entire window area
void clearWindow(int top, int bottom, int left, int right) {
    for (int y = top; y <= bottom; y++) {
        clearLine(y, left, right);
    }
}

void drawBorder(int top, int bottom, int left, int right) {
    // Draw top border
    gotoxy(left, top);
    cprintf("+");
    for (int x = left + 1; x < right; x++) {
        cprintf("-");
    }
    cprintf("+");

    // Draw sides border
    for (int y = top + 1; y < bottom; y++) {
        gotoxy(left, y);
        cprintf("|");
        gotoxy(right, y);
        cprintf("|");
    }

    // Draw bottom border
    gotoxy(left, bottom);
    cprintf("+");
    for (int z = left + 1; z < right; z++) {
        cprintf("-");
    }
    cprintf("+");
}

// Main program
int main() {
    int bgColor, textColor;
    int currentY = Y2;  // Start from the bottom of the window

    clrscr();  // Clear the screen initially
	
    drawBorder(Y1-1, Y2+1, X1-1, X2+1);
    // Loop through all background and text color combinations
    for (bgColor = 0; bgColor <= 15; bgColor++) {  // Loop through all background colors
        for (textColor = 0; textColor <= 15; textColor++) {  // Loop through all text colors
            if (bgColor != textColor) {  // Skip if background color is the same as text color
                // Clear the line where the new text will be printed
                clearLine(currentY, X1, X2);

                // Print color text at the current position
                printColorText(bgColor, textColor, X1, currentY);
                delay(DELAY_MS);  // Delay before updating the screen

                currentY--;  // Move to the previous line

                // Scroll if we reach the top of the window
                if (currentY < Y1) {
                    scrollWindow(1, Y1, Y2, X1-1, X2, SCROLL_LINES, 0x00);  // Scroll the window up
                    currentY = Y2;  // Reset currentY to the bottom of the window
                }
            }
        }
    }

    getch();  // Wait for a key press before exiting
    return 0;
}