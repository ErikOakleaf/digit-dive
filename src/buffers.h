#ifndef BUFFERS_H
#define BUFFERS_H

#include <stdlib.h>
#include <stdio.h>

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

void reverseString(char *str);
void decimalToBinary(char *decimalBuffer, char *binaryBuffer); 
void decimalToHex(char *decimalBuffer, char *hexBuffer); 
void addToBuffer(StringBuffers *buffers, int *bufferIndex, char c, BufferType type); 
void addToBufferDecimal(StringBuffers *buffers, int *bufferIndex, char c); 
void removeFromBuffer(StringBuffers *buffers, int *bufferIndex, BufferType type); 
void removeFromBufferDecimal(StringBuffers *buffers, int *bufferIndex); 
void resetBuffers(StringBuffers *buffers, int *cursor); 

#endif
