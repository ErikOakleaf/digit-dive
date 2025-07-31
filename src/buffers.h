#ifndef BUFFERS_H
#define BUFFERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char decimalBuffer[11];
    char binaryBuffer[37];
    char hexBuffer[9];
    int decimalCursor;
    int binaryCursor;
    int hexCursor;
} StringBuffers;

typedef enum {
    Decimal,
    Binary,
    Hex,
} BufferType;

void initBuffers(StringBuffers *buffers);
void reverseString(char *str);
void decimalToBinary(StringBuffers *buffers);
void decimalToHex(StringBuffers *buffers);
void binaryToDecimal(StringBuffers *buffers);
void hexToDecimal(StringBuffers *buffers);
void addToBuffer(StringBuffers *buffers, char c, BufferType type);
void addToBufferDecimal(StringBuffers *buffers, char c);
void addToBufferBinary(StringBuffers *buffers, char c);
void addToBufferHex(StringBuffers *buffers, char c);
void removeFromBuffer(StringBuffers *buffers, BufferType type);
void removeFromBufferDecimal(StringBuffers *buffers);
void removeFromBufferBinary(StringBuffers *buffers);
void removeFromBufferHex(StringBuffers *buffers);
void resetBuffers(StringBuffers *buffers);

#endif
