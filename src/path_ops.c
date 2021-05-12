// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "path_ops.h"

const char kExtensionSeparator = '.';
const char kPathSeparator =

#ifdef _WIN32
  #ifndef _WIN32
     #define __WIN32__
  #endif
#endif

#ifdef __WIN32__
                            '\\';
#else
                            '/';
#endif



void filename_replace_extension(char * filename, char * new_ext, size_t maxlen) {

    // Use a temp work string in case out and in filename are the same pointer
    char temp[MAX_FILE_STR];
    char ext_sep[2] = {'\0'}; // default to empty string

    // Add leading . to path if needed
    if (new_ext[0] != kExtensionSeparator) {
        ext_sep[0] = kExtensionSeparator;
        ext_sep[1] = '\0';
    }

    // Strip extension from filename, append new extension
    filename_remove_extension(filename);
    snprintf(temp, maxlen, "%s%s%s", filename, ext_sep, new_ext);
    snprintf(filename, maxlen, "%s", temp);
}


void filename_replace_path(char * filename, char * new_path, size_t maxlen) {

    // Use a temp work string in case out and in filename are the same pointer
    char temp[MAX_FILE_STR];
    char path_sep[2] = {'\0'}; // default to empty string

    // Add trailing slash to path if needed
    if ((new_path[(strlen(new_path)-1)] != kPathSeparator)) {
        path_sep[0] = kPathSeparator;
        path_sep[1] = '\0';
    }

    // Strip path from path+filename, pre-pend new path
    snprintf(temp, maxlen, "%s%s%s", new_path, path_sep, get_filename_from_path(filename));
    snprintf(filename, maxlen, "%s", temp);
}


const char * get_filename_from_path(const char * path)
{
    size_t i;

    // Returns string starting at last occurrance of path separator char
    for(i = strlen(path) - 1; i; i--) {
        if (path[i] == kPathSeparator) {
            return &path[i+1];
        }
    }
    return path;
}


void filename_remove_extension(char * path)
{
    char * last_ext;
    char * last_slash;

    // Find the last path separator if present
    // Starting from here ensures that no path ".." characters
    // get mistaken as extension delimiters.
    last_slash = strrchr (path, kExtensionSeparator);
    if (!last_slash)
        last_slash = path;

    // Then check to see if there is an extension (starting with the last occurance of '.')
    // (tries to remove *all* trailing extensions backward until the last slash)
    last_ext = strrchr (last_slash, kExtensionSeparator);
    while (last_ext) {
        if (last_ext != NULL) {
            // If an extension is found then overwrite it with a string terminator
            *last_ext = '\0';
        }
        last_ext = strrchr (last_slash, kExtensionSeparator);
    }
}

