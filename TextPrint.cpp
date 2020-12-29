#pragma once
#include "IO.cpp"
#include "Typedefs.cpp"
#include "TextModeColorCodes.cpp"
#define VGA_MEMORY (uint_8*)0xb8000
#define VGA_WIDTH 80

uint_16 CursorPosition;

void ClearScreen(uint_64 ClearColor = BACKGROUND_BLACK | FOREGROUND_WHITE){
    uint_64 value = 0;
    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;
    for (uint_64* i = (uint_64*)VGA_MEMORY; i < (uint_64*)(VGA_MEMORY + 4000); i++){
        *i = value;
    }
}

void SetCursorPosition(uint_16 position){
    outb(0x3D4, 0x0f);
    outb(0x3D5, (uint_8)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint_8)((position >> 8) & 0xFF));

    CursorPosition = position;
}

uint_16 PositionFromCoords(uint_8 x, uint_8 y){
    return y * VGA_WIDTH + x;
}

void PrintString(const char* str, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE){
    uint_8* charPtr = (uint_8*)str;
    uint_16 index = CursorPosition;
    while(*charPtr != 0){
        switch (*charPtr){
            case 10:
                index += VGA_WIDTH;
                break;
            case 13:
                index -= index % VGA_WIDTH;
            default:
                *(VGA_MEMORY + index * 2) = *charPtr;
                *(VGA_MEMORY + index * 2 + 1) = color;
                index++;
        }

        charPtr++;
    }
    SetCursorPosition(index);
}

void PrintChar(char chr, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE){
    *(VGA_MEMORY + CursorPosition * 2) = chr;
    *(VGA_MEMORY + CursorPosition * 2 + 1) = color;
    SetCursorPosition(CursorPosition + 1);
}

char hexToStringOutput[128];
template<typename T>
const char* HexToString(T value){
    T* valPtr = &value;
    uint_8* ptr;
    uint_8 temp;
    uint_8 size = (sizeof(T)) * 2 - 1;
    uint_8 i;
    for (i = 0; 1 < size; i++){
        ptr = ((uint_8*)valPtr + 1);
        temp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput[size - (1 * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
        temp = ((*ptr & 0x0F));
        hexToStringOutput[size - (1 * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
    }
    hexToStringOutput[size + 1] = 0;

    return hexToStringOutput;
}