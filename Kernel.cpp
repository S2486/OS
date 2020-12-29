#include "TextPrint.cpp"
#include "IDT.cpp"

extern const char Banner[];

extern "C" void _start() {
    SetCursorPosition(PositionFromCoords(0, 0));
    InitializeIDT();
    ClearScreen();
    PrintString(Banner);
    PrintString("\nWelcome to AnOS\n \n\rHello World\n\n\r");
    return;
}