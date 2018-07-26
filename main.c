#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_LENGTH_LINE 23

int main()
{
    const char * string = "Another U2F device was used to register in this application. LONGLONGLONGLONGLONGLONGLONGLONGLONGLONGLONGLONGLONGLONGLONLONGLINGLINGLINGLINGLINGLINGLINGLION";
    //const char * string = "Un autre appreil U2F a été utilisé pour s'enregister dans l'application";

    printf("%s", string);
    printf("\r\n");
    printf("length of string is %d.\r\n", (int)strlen(string));

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
    for(int i = 0; i < 5; i++)
    {
        printf("Line Number %d is: %s\r\n", i+1, (char *) lines[i]);
    }
    return 0;
}