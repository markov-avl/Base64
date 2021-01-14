#include "base64.h"
#include <string>
#include <cstring>
#include <vector>
#define BITS_TO_DECODE 6
#define BITS_TO_ENCODE 8


char TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
               "abcdefghijklmnopqrstuvwxyz"
               "0123456789+/";


std::string getBinary(int n, bool isEncoding) {
    int count = isEncoding ? BITS_TO_ENCODE : BITS_TO_DECODE;
    std::string result;
    for (int i = 0; i < count; ++i) {
        result = (n % 2 ? '1' : '0') + result;
        n /= 2;
    }
    return result;
}


std::vector<int> getIndexing(std::string line, bool isEncoding) {
    int digitCount = isEncoding ? BITS_TO_DECODE : BITS_TO_ENCODE;
    int segmentCount = line.length() / digitCount;
    bool hasNotFilled = digitCount * segmentCount != line.length();
    if (hasNotFilled) {
        segmentCount += 1;
    }
    std::vector<int> indexing(segmentCount);
    std::string buffer;
    for (int i = 0; i < segmentCount; ++i){
        if (hasNotFilled && i == segmentCount - 1){
            buffer = line.substr(0,line.length() % digitCount);
            buffer.append(digitCount - line.length() % digitCount,'0');
        } else {
            buffer = line.substr(0, digitCount);
        }
        indexing[i] = std::stoi(buffer, nullptr, 2);
        line.erase(0, digitCount);
    }
    return indexing;
}


std::string base64(std::string line, bool isEncoding) {
    std::string binary;
    std::string result;
    int index;
    for (char letter : line) {
        if (!isEncoding) {
            for (index = 0; index < strlen(TABLE) && TABLE[index] != letter; ++index);
        } else {
            index = static_cast<int>(letter);
        }
        binary += getBinary(index, isEncoding);
    }
    std::vector<int> indexing = getIndexing(binary, isEncoding);
    for (int i : indexing) {
        result += isEncoding ? TABLE[i] : static_cast<char>(i);
    }
    if (result.back() == '\0') {
        result.pop_back();
    }
    return result;
}


std::string encodeBase64(std::string& line) {
    return base64(line, true);
}


std::string decodeBase64(std::string& line) {
    return base64(line, false);
}