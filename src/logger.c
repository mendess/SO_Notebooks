#include "logger.h"
#include "colors.h"
#include "utilities.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static inline char* paintMessage(char* color, char* message, size_t len){
    size_t cLen = strlen(color);
    size_t mLen = len;
    size_t rLen = strlen(RESET);
    char* m = malloc(sizeof(char) * (cLen + mLen + rLen + 1));
    strncpy(m, color, cLen);
    strncpy(m + cLen, message, mLen);
    strncpy(m + cLen + mLen, RESET, rLen);
    m[cLen + mLen + rLen] = '\0';
    return m;
}

void LOG_FATAL(char* message){
    char* paintedMsg = paintMessage(RED, message, strlen(message));
    write(2, paintedMsg, strlen(paintedMsg));
    free(paintedMsg);
}

void LOG_FATAL_STRING(String message){
    char* paintedMsg = paintMessage(RED, message.s, message.length);
    write(2, paintedMsg, strlen(paintedMsg));
    free(paintedMsg);
}

void _log_CRITICAL(char* message){
    char* paintedMsg = paintMessage(YELLOW, message, strlen(message));
    write(2, paintedMsg, strlen(paintedMsg));
    free(paintedMsg);
}

void LOG_PARSE_ERROR(String line, int lineNumber, char* message, int errOffset){
    char lineN[12];
    size_t lineNlen = int2string(lineNumber, lineN, 12);
    size_t totalLen =
            strlen(BOLD) + strlen("line ") + lineNlen + 1
            + strlen(": " RED "error: " RESET) + strlen(message) +
            strlen("\n\t")
            + line.length + strlen("\n")
            + strlen("\t") + strlen(" ") * errOffset +
            strlen(GREEN "^" RESET "\n") + strlen("\0");
    char* output = malloc(sizeof(char) * totalLen);
    strcat(output, BOLD "line ");
    strncat(output, lineN, lineNlen);
    strcat(output, ": " RED "error: " RESET);
    strcat(output, message);
    strcat(output, "\n\t");
    strncat(output, line.s, line.length);
    strcat(output, "\n\t");
    for(int i = 0; i < errOffset; i++)
        strcat(output, " ");
    strcat(output, GREEN "^" RESET "\n");

    write(2, output, totalLen);
    free(output);
}

void LOG_WARNING_STRING(String message){
    char* paintedMsg = paintMessage(PURPLE, message.s, message.length);
    write(2, paintedMsg, strlen(paintedMsg));
    free(paintedMsg);
}

void LOG_WARNING(char* message){
    char* paintedMsg = paintMessage(PURPLE, message, strlen(message));
    write(2, paintedMsg, strlen(paintedMsg));
    free(paintedMsg);
}
