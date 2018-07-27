#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH_LINE 22

void firstImplem(const char *);
void printLines(char lines[5][MAX_LENGTH_LINE]);
void secondImplem(const char * stringToSplit, char lines [5][MAX_LENGTH_LINE]);

#define PIXEL_LINE_WIDTH 100

int main()
{
    //const char * string = "Another U2F device was used to register in this application.";
    //const char * string = "Un autre appreil U2F a été utilisé pour s'enregister dans l'application";

    //const char * string = "Do you really want to change the home screen?";
    const char * string = "Voulez-vous vraiment changer l'écran d'accueil pour ce magnifique écran de la mort qui tue sa maman ???";

    char stringToSplit[strlen(string) + 1];
    strcpy(stringToSplit, string);
    

    char lines[5][MAX_LENGTH_LINE] = {0};

    int lineIndex = 0;

    int maxLines = 5;
	int wordPixelLen = 0;
	int linePixelLen = 0;
    int start = 0;

	for(int i = 0; i < (int) strlen(stringToSplit); i++)
	{
		wordPixelLen += 2 + 1;
		if (strncmp(&stringToSplit[i], " ", 1) == 0) {
			if(linePixelLen + wordPixelLen <= PIXEL_LINE_WIDTH) {
				strncat(lines[lineIndex], &stringToSplit[start], (int) (strlen(&stringToSplit[start]) - strlen(&stringToSplit[i]) + 1));
				linePixelLen += wordPixelLen;
				wordPixelLen = 0;
			} else if (lineIndex < maxLines - 1) {
				lineIndex++;
				linePixelLen = wordPixelLen;
				wordPixelLen = 0;
				strncat(lines[lineIndex], &stringToSplit[start], (int) (strlen(&stringToSplit[start]) - strlen(&stringToSplit[i]) + 1));
			}
            start = i + 1;
		} else {
			wordPixelLen += 2 + 1;
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
    char firstLine[MAX_LENGTH_LINE] = "";

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