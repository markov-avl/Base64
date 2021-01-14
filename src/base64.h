#ifndef BASE64_BASE64_H
#define BASE64_BASE64_H
#include <iostream>


extern char TABLE[];


std::string encodeBase64(std::string& line);
std::string decodeBase64(std::string& line);

#endif