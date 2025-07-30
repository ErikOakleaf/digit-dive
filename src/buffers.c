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
    long long decimal = atoll(decimalBuffer);
    sprintf(hexBuffer, "%llX", decimal);
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

void resetBuffers(StringBuffers *buffers, int *cursor) {
    buffers->decimalBuffer[0] = '\0';
    buffers->binaryBuffer[0] = '\0';
    buffers->hexBuffer[0] = '\0';
    *cursor = 0;
}
