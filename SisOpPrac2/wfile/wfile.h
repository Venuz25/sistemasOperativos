
#ifndef __WINDOWS_FILE_H__
#define __WINDOWS_FILE_H__

#include <windows.h>
#include <stdbool.h>

/// @brief Check if the len of the string is more than the maximum size
/// @param str the string to check
/// @param maximum The maximum number
/// @return True in case of str being lower than maximum, else false
bool checkLenStr(const char *str, size_t maximum);

/// @brief Help create a file with the windows api
/// @param path Where is going to be the file including name and that...
/// @param accessMode How access, read, write or both
/// @param shareMode If you want to let other programs see the file while this program is using it
/// @param CreatorMode Is the file is going to be created, read and that
/// @return The handle of the file, INVALID_HANDLE_VALUE in case of an error
HANDLE fileCreator(const char *path, unsigned long accessMode, unsigned long shareMode, unsigned long CreatorMode);

/// @brief fwrite, but using WIN32 API
/// @param file The Handle obtained by CreateFile
/// @param buffer The data to write to the file
/// @param bytesToWrite The amount of bytes to write present on the buffer
/// @return True in case of success, otherwise false
bool windowsFWrite(HANDLE file, const void *buffer, unsigned long bytesToWrite);

/// @brief The same thing as fclose, just using WIN32 API
/// @param file The file to close
/// @return True in success
bool windowsFClose(HANDLE file);

#endif