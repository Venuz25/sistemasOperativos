
#ifndef __INPUTS_CUST_H__
#define __INPUTS_CUST_H__

#include <stdint.h>

/// @brief Check if the value is an int and is positive
/// @param msj The messaje to ask to the user on screen
/// @param val Where to store the data
void checkIntPosValue(const char *msj, int *val);

/// @brief Check that the input string from stdio is the correct len and is up to 1024 chars
/// @param msj The messaje to show to the user
/// @param str There to save the data
/// @param len The leng of the string (You know buffer overflow...) 
void checkStrValue(const char *msj, char *str, size_t len);

#endif