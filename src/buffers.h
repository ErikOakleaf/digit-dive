#ifndef BUFFERS_H
#define BUFFERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char decimalBuffer[11];
    char binaryBuffer[37];
    char hexBuffer[9];
} StringBuffers;

typedef enum {
    Decimal,
    Binary,
    Hex,
} BufferType;

void initBuffers(StringBuffers *buffers);
void reverseString(char *str);
void decimalToBinary(char *decimalBuffer, char *binaryBuffer);
void decimalToHex(char *decimalBuffer, char *hexBuffer);
void binaryToDecimal(char *binaryBuffer, char *decimalBuffer);
void hexToDecimal(char *hexBuffer, char *decimalBuffer);
void addToBuffer(StringBuffers *buffers, int *bufferIndex, char c, BufferType type);
void addToBufferDecimal(StringBuffers *buffers, int *bufferIndex, char c);
void addToBufferBinary(StringBuffers *buffers, int *bufferIndex, char c);
void addToBufferHex(StringBuffers *buffers, int *bufferIndex, char c);
void removeFromBuffer(StringBuffers *buffers, int *bufferIndex, BufferType type);
void removeFromBufferDecimal(StringBuffers *buffers, int *bufferIndex);
void removeFromBufferBinary(StringBuffers *buffers, int *bufferIndex);
void removeFromBufferHex(StringBuffers *buffers, int *bufferIndex);
void resetBuffers(StringBuffers *buffers, int *cursor);

#endif
