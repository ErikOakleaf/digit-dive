#include "buffers.h"

void initBuffers(StringBuffers *buffers) {

    memset(buffers->decimalBuffer, 0, sizeof(buffers->decimalBuffer));
    memset(buffers->binaryBuffer, 0, sizeof(buffers->binaryBuffer));
    memset(buffers->hexBuffer, 0, sizeof(buffers->hexBuffer));
}

void reverseString(char *str) {
    if (!str) {
        return;
    }

    char *start = str;
    char *end = str;

    while (*end != '\0') {
        end++;
    }
    end--;

    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }
}

void decimalToBinary(char *decimalBuffer, char *binaryBuffer) {
    long long decimal = atoll(decimalBuffer);

    if (decimal == 0) {
        binaryBuffer[0] = '0';
        binaryBuffer[1] = '\0';
        return;
    }

    int i = 0;
    while (decimal > 0) {
        int bit = decimal & 1;
        binaryBuffer[i++] = '0' + bit;

        decimal = decimal >> 1;
    }

    binaryBuffer[i] = '\0';

    reverseString(binaryBuffer);
}

void decimalToHex(char *decimalBuffer, char *hexBuffer) {
    long long num = atoll(decimalBuffer);
    sprintf(hexBuffer, "%llX", num);
}

void binaryToDecimal(char *binaryBuffer, char *decimalBuffer) {
    char *endPointer;  
    long long num = strtoll(binaryBuffer, &endPointer, 2);

    if(*endPointer != '\0') {
        return;
    }

    sprintf(decimalBuffer, "%lld", num);
}

void addToBuffer(StringBuffers *buffers, int *bufferIndex, char c, BufferType type) {
    switch (type) {
        case Decimal: {
            if (!(c >= '0' && c <= '9')) {
                return;
            }
            addToBufferDecimal(buffers, bufferIndex, c);
            break;
        }
        case Binary: {
            if (!(c == '0' | c == '1')) {
                return;
            }
            addToBufferBinary(buffers, bufferIndex, c);
            break;
        }
        case Hex: {

            break;
        }
        default:
            return;
    }
}

void addToBufferDecimal(StringBuffers *buffers, int *bufferIndex, char c) {
    if (*bufferIndex < 10) {
        buffers->decimalBuffer[(*bufferIndex)++] = c;
        buffers->decimalBuffer[*bufferIndex] = '\0';
    }

    decimalToBinary(buffers->decimalBuffer, buffers->binaryBuffer);
    decimalToHex(buffers->decimalBuffer, buffers->hexBuffer);
}

void addToBufferBinary(StringBuffers *buffers, int *bufferIndex, char c) {
    if (*bufferIndex < 33) {
        buffers->binaryBuffer[(*bufferIndex)++] = c;
        buffers->binaryBuffer[*bufferIndex] = '\0';
    }

    binaryToDecimal(buffers->binaryBuffer, buffers->decimalBuffer);
    decimalToHex(buffers->decimalBuffer, buffers->hexBuffer);
}

void removeFromBuffer(StringBuffers *buffers, int *bufferIndex, BufferType type) {
    if (*bufferIndex <= 0) {
        return;
    }

    switch (type) {
        case Decimal: {
            removeFromBufferDecimal(buffers, bufferIndex);
            break;
        }
        case Binary: {
            removeFromBufferBinary(buffers, bufferIndex);
            break;
        }
        case Hex: {

            break;
        }
        default:
            return;
    }
}

void removeFromBufferDecimal(StringBuffers *buffers, int *bufferIndex) {
    (*bufferIndex)--;
    buffers->decimalBuffer[*bufferIndex] = '\0';

    decimalToBinary(buffers->decimalBuffer, buffers->binaryBuffer);
    decimalToHex(buffers->decimalBuffer, buffers->hexBuffer);
}

void removeFromBufferBinary(StringBuffers *buffers, int *bufferIndex) {
    (*bufferIndex)--;
    buffers->binaryBuffer[*bufferIndex] = '\0';

    binaryToDecimal(buffers->binaryBuffer, buffers->decimalBuffer);
    decimalToHex(buffers->decimalBuffer, buffers->hexBuffer);
}

void resetBuffers(StringBuffers *buffers, int *cursor) {
    buffers->decimalBuffer[0] = '\0';
    buffers->binaryBuffer[0] = '\0';
    buffers->hexBuffer[0] = '\0';
    *cursor = 0;
}
