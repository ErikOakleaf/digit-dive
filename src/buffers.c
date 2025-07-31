#include "buffers.h"
#include "stdbool.h"

// prototypes

void removeFromBufferDecimal(StringBuffers *buffers);
void reverseString(char *str);
void decimalToBinary(StringBuffers *buffers);
void decimalToHex(StringBuffers *buffers);
void binaryToDecimal(StringBuffers *buffers);
void hexToDecimal(StringBuffers *buffers);
void addToBufferDecimal(StringBuffers *buffers, char c);
void addToBufferBinary(StringBuffers *buffers, char c);
void addToBufferHex(StringBuffers *buffers, char c);
void removeFromBufferDecimal(StringBuffers *buffers);
void removeFromBufferBinary(StringBuffers *buffers);
void removeFromBufferHex(StringBuffers *buffers);
void resetBuffers(StringBuffers *buffers);
bool checkIfEmpty(char *buffer);

// implementations

void initBuffers(StringBuffers *buffers) {

    memset(buffers->decimalBuffer, 0, sizeof(buffers->decimalBuffer));
    memset(buffers->binaryBuffer, 0, sizeof(buffers->binaryBuffer));
    memset(buffers->hexBuffer, 0, sizeof(buffers->hexBuffer));

    buffers->decimalCursor = 0;
    buffers->binaryCursor = 0;
    buffers->hexCursor = 0;
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

void decimalToBinary(StringBuffers *buffers) {
    long long decimal = atoll(buffers->decimalBuffer);

    if (decimal == 0) {
        buffers->binaryBuffer[0] = '0';
        buffers->binaryBuffer[1] = '\0';
        return;
    }

    int i = 0;
    while (decimal > 0) {
        int bit = decimal & 1;
        buffers->binaryBuffer[i++] = '0' + bit;

        decimal = decimal >> 1;
    }

    buffers->binaryBuffer[i] = '\0';
    buffers->binaryCursor = i;

    reverseString(buffers->binaryBuffer);
}

void decimalToHex(StringBuffers *buffers) {
    long long num = atoll(buffers->decimalBuffer);
    sprintf(buffers->hexBuffer, "%llX", num);

    buffers->hexCursor = strlen(buffers->hexBuffer);
}

void binaryToDecimal(StringBuffers *buffers) {
    char *endPointer;
    long long num = strtoll(buffers->binaryBuffer, &endPointer, 2);

    if (*endPointer != '\0') {
        return;
    }

    sprintf(buffers->decimalBuffer, "%lld", num);
    buffers->decimalCursor = strlen(buffers->decimalBuffer);
}

void hexToDecimal(StringBuffers *buffers) {
    char *endPointer;
    long long num = strtoll(buffers->hexBuffer, &endPointer, 16);

    if (*endPointer != '\0') {
        return;
    }

    sprintf(buffers->decimalBuffer, "%lld", num);
    buffers->decimalCursor = strlen(buffers->decimalBuffer);
}

void addToBuffer(StringBuffers *buffers, char c, BufferType type) {
    switch (type) {
        case Decimal: {
            if (!(c >= '0' && c <= '9')) {
                return;
            }
            addToBufferDecimal(buffers, c);
            break;
        }
        case Binary: {
            if (!(c == '0' || c == '1')) {
                return;
            }
            addToBufferBinary(buffers, c);
            break;
        }
        case Hex: {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
                return;
            }
            addToBufferHex(buffers, c);
            break;
        }
        default:
            return;
    }
}

void addToBufferDecimal(StringBuffers *buffers, char c) {
    if (buffers->decimalCursor < 10) {
        buffers->decimalBuffer[buffers->decimalCursor++] = c;
        buffers->decimalBuffer[buffers->decimalCursor] = '\0';
    }

    decimalToBinary(buffers);
    decimalToHex(buffers);
}

void addToBufferBinary(StringBuffers *buffers, char c) {
    if (buffers->binaryCursor < 33) {
        buffers->binaryBuffer[buffers->binaryCursor++] = c;
        buffers->binaryBuffer[buffers->binaryCursor] = '\0';
    }

    binaryToDecimal(buffers);
    decimalToHex(buffers);
}

void addToBufferHex(StringBuffers *buffers, char c) {
    if (buffers->hexCursor < 8) {
        buffers->hexBuffer[buffers->hexCursor++] = c;
        buffers->hexBuffer[buffers->hexCursor] = '\0';
    }

    hexToDecimal(buffers);
    decimalToBinary(buffers);
}

void removeFromBuffer(StringBuffers *buffers, BufferType type) {
    if ((type == Decimal && buffers->decimalCursor <= 0) || (type == Binary && buffers->binaryCursor <= 0) ||
        (type == Hex && buffers->hexCursor <= 0)) {
        return;
    }

    switch (type) {
        case Decimal: {
            removeFromBufferDecimal(buffers);
            break;
        }
        case Binary: {
            removeFromBufferBinary(buffers);
            break;
        }
        case Hex: {
            removeFromBufferHex(buffers);
            break;
        }
    }
}

bool inline checkIfEmpty(char *buffer) { return buffer[0] == '\0'; }

void removeFromBufferDecimal(StringBuffers *buffers) {
    (buffers->decimalCursor)--;
    buffers->decimalBuffer[buffers->decimalCursor] = '\0';

    if (checkIfEmpty(buffers->decimalBuffer)) {
        resetBuffers(buffers);
    } else {
        decimalToBinary(buffers);
        decimalToHex(buffers);
    }
}

void removeFromBufferBinary(StringBuffers *buffers) {
    (buffers->binaryCursor)--;
    buffers->binaryBuffer[buffers->binaryCursor] = '\0';

    if (checkIfEmpty(buffers->binaryBuffer)) {
        resetBuffers(buffers);
    } else {
        binaryToDecimal(buffers);
        decimalToHex(buffers);
    }
}

void removeFromBufferHex(StringBuffers *buffers) {
    (buffers->hexCursor)--;
    buffers->hexBuffer[buffers->hexCursor] = '\0';

    if (checkIfEmpty(buffers->hexBuffer)) {
        resetBuffers(buffers);
    } else {
        hexToDecimal(buffers);
        decimalToBinary(buffers);
    }
}

void resetBuffers(StringBuffers *buffers) {
    buffers->decimalBuffer[0] = '\0';
    buffers->binaryBuffer[0] = '\0';
    buffers->hexBuffer[0] = '\0';

    buffers->decimalCursor = 0;
    buffers->binaryCursor = 0;
    buffers->hexCursor = 0;
}
