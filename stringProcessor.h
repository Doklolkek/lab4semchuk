#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"

#define STRING_MAX 512ull

const int32_t get_str(const char* msg, char* str, const int32_t limit) {
    if (!msg || !str || limit <= 1) return 0;
    printf("%s", msg);
    int32_t count = 0;
    int ch;
    while (count < limit - 1 && (ch = getchar()) != EOF && ch != '\n') {
        str[count++] = (char)ch;
    }
    str[count] = '\0';
    return count;
}

const size_t strlenn(const char* str) {
    if (!str) return 0;
    size_t length = 0;
    while (str[length]) length++;
    return length;
}

void strcopy(char* dest, char* src, size_t limit) {
    if (!dest || !src || limit == 0) return;
    size_t i = 0;
    while (i < limit - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int32_t strcmpp(const char* str1, const char* str2) {
    if (!str1 || !str2) return 0;
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char* strcatt(char* dest, const char* src) {
    char* end = dest + strlenn(dest);
    while (*src) {
        *end++ = *src++;
    }
    *end = '\0';
    return dest;
}

// is_string_valid ≥ process_string Ч залишаЇмо майже €к у тебе ориг≥нально, але з маленькими зм≥нами в ≥менах зм≥нних
bool is_string_valid(char* str) {
    bool has_word = false;
    bool after_colon = false;
    size_t len = strlenn(str);
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if ((c == ':' || c == ';' || c == ',') && i == 0) return false;
        if (c == ':') {
            after_colon = true;
        }
        else if (after_colon) {
            if (c == ',') {
                if (!isalpha(str[i - 1]) && str[i - 1] != ' ') return false;
                has_word = true;
            }
            if (c == ';') {
                if (!has_word || (!isalpha(str[i - 1]) && str[i - 1] != ' ')) return false;
                after_colon = false;
                has_word = false;
            }
            if (c == ':') return false;
        }
        else {
            has_word = false;
        }
    }
    return true;
}

char* process_string(char* str) {
    size_t len = strlenn(str);
    char* output = (char*)calloc(len + 512, sizeof(char));
    size_t out_idx = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] != ':') {
            output[out_idx++] = str[i];
            continue;
        }
        if (i + 1 >= len || str[i + 1] != ' ') {
            free(output);
            return NULL;
        }
        output[out_idx++] = ':';
        output[out_idx++] = ' ';

        char** words = (char**)calloc(100, sizeof(char*));
        for (int k = 0; k < 100; k++) words[k] = (char*)calloc(STRING_MAX, sizeof(char));
        size_t word_count = 0;

        size_t j = i + 2;
        for (; j < len; j++) {
            if (str[j] == ',' || str[j] == ';') {
                if (str[j] == ';') {
                    quick_sort(words, word_count + 1);
                    for (size_t k = 0; k <= word_count; k++) {
                        strcpy(output + out_idx, words[k]);
                        out_idx += strlenn(words[k]);
                        if (k < word_count) {
                            output[out_idx++] = ',';
                            output[out_idx++] = ' ';
                        }
                        else {
                            output[out_idx++] = ';';
                        }
                    }
                    i = j;
                    break;
                }
                word_count++;
                j++;
            }
            else {
                size_t pos = strlenn(words[word_count]);
                words[word_count][pos] = str[j];
                words[word_count][pos + 1] = '\0';
            }
        }

        for (int k = 0; k < 100; k++) free(words[k]);
        free(words);
    }
    output[out_idx] = '\0';
    return output;
}

#endif