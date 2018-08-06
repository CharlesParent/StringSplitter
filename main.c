#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "fonts.h"

#define MAX_LENGTH_LINE 50

void firstImplem(const char *);
void printLines(char lines[5][MAX_LENGTH_LINE]);
void secondImplem(const char * stringToSplit, char lines [5][MAX_LENGTH_LINE]);

#define PIXEL_LINE_WIDTH 109

int main()
{
    //const char * string = "Another U2F device was used to register in this application.";
    //const char * string = "Un autre appreil U2F a été utilisé pour s'enregister dans l'application";

    //const char * string = "Do you really want to change the home screen?";
    //const char * string = "Voulez-vous vraiment changer l'\xe9""cran d'accueil pour ce magnifique \xe9""cran de la mort qui tue sa maman ???";
    
    // char tx_value[32] = "0.008";
	// char gas_value[32] = "0.00000017";

    // const char* stringVar = "Really send %s paying up to %s for gas?";

    // char string[5*MAX_LENGTH_LINE];

    // sprintf(string, stringVar, tx_value, gas_value);

    char* string;
    printf("Please enter a string to see if it fits in splitted lines:\n");
    gets(string);

    char lines[5][MAX_LENGTH_LINE] = {0};

    int lineIndex = 0;

    int maxLines = 5;
	int wordPixelLen = 0;
	int linePixelLen = 0;
    int start = 0;
    printf("Word pixel length is %d\n", wordPixelLen);
	for(int i = 0; i < (int) strlen(string); i++)
	{
		char currentChar = string[i];
        wordPixelLen = wordPixelLen + fontCharWidth(FONT_STANDARD & 0x7f, currentChar) + 1;
        if (strncmp(&string[i+1], " ", 1) == 0 || strncmp(&string[i+1], "\0", 1) == 0) {
			if(linePixelLen + wordPixelLen <= PIXEL_LINE_WIDTH) {
				strncat(lines[lineIndex], &string[start], (int) (strlen(&string[start]) - strlen(&string[i+1])));
				linePixelLen += wordPixelLen;
				wordPixelLen = 0;
                start = i+1;
			} else if (lineIndex < maxLines - 1) {
				lineIndex++;
				linePixelLen = wordPixelLen;
				wordPixelLen = 0;
				strncat(lines[lineIndex], &string[start + 1], (int) (strlen(&string[start + 1]) - strlen(&string[i+1])));
                start = i+1;
			}
		}
    }
    printLines(lines);

    return 0;
}

void secondImplem(const char * stringToSplit, char lines [5][MAX_LENGTH_LINE]) {
    int maxLines = 5;
    int start = 0;
    int lineNumber = 0;
    int index = MAX_LENGTH_LINE;
    while(index < (int) strlen(stringToSplit)) {
        while(strncmp(&stringToSplit[index], " ", 1)) {
            index -= 1;
        }
        strncpy(lines[lineNumber], &stringToSplit[start], index - start + 1);
        start = index + 1;
        index += MAX_LENGTH_LINE;
        printf("Line number %d is : %s\n", lineNumber, lines[lineNumber]);
        if (lineNumber == maxLines - 1 ) break; 
        lineNumber += 1;
        printf("lineNumber is %d\n", lineNumber);

    }
    
    if (strlen(lines[lineNumber]) + strlen(&stringToSplit[start]) < MAX_LENGTH_LINE) {
        strcat(lines[lineNumber], &stringToSplit[start]);
    } else if (lineNumber < maxLines - 1) {
        strcpy(lines[lineNumber + 1], &stringToSplit[start]);
    }
    printLines(lines);
}

void firstImplem(const char * string) {
    char stringToSplit[strlen(string) + 1];

    char **lines;
    lines = (char **) calloc(5 * sizeof(char *), sizeof(char*));
    for(int i=0;i<10;i++) {
        lines[i]=(char *) calloc(MAX_LENGTH_LINE * sizeof(char), sizeof(char));
    }
    strcpy(stringToSplit, string);


    uint8_t lineNumber = 0;
    while(strlen(stringToSplit)){
        char * ret = strchr(stringToSplit, ' ');
        int stringToSplitLen = (int) (strlen(stringToSplit) + 1);

        if (ret == NULL) {
            if (stringToSplitLen > MAX_LENGTH_LINE) break;
            if (strlen(lines[lineNumber]) + stringToSplitLen > MAX_LENGTH_LINE){
                lineNumber += 1;
            }
            strncat(&lines[lineNumber][strlen(lines[lineNumber])], stringToSplit, stringToSplitLen);
            break;
        }

        if (strlen((char*) lines[lineNumber]) + (int) (strlen(stringToSplit) - strlen(ret) + 1) > MAX_LENGTH_LINE){
            lineNumber += 1;
        }
        strncat(&lines[lineNumber][strlen(lines[lineNumber])], stringToSplit, (int) (strlen(stringToSplit) - strlen(ret) + 1));

        strcpy(stringToSplit, ret + 1);
    }
    //printLines(lines);
};

void printLines(char lines[5][MAX_LENGTH_LINE]){
    for(int i = 0; i < 5; i++)
        printf("Line Number %d is: %s\r\n", i+1, (char *) lines[i]);
}