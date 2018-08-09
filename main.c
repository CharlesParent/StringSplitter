#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "fonts.h"

#define MAX_LENGTH_LINE 50
#define PIXEL_LINE_WIDTH 110
#define LINES_ON_SCREEN 6

void printLines(char lines[5][MAX_LENGTH_LINE]);
int test_string(const char * string);

int main(){
    test_string("Another U2F device was used to register in this application.");
    test_string("Un autre appreil U2F a été utilisé pour s'enregister dans l'application");
    test_string("Do you really want to change language to FR ?");
    test_string("Do you really want to change the home screen?");
    test_string("Le chargement d'une graine privée n'est pas recommandé. Continuer si seulement vous savez ce que vous faites!");
    test_string("Voulez-vous vraiment changer l'écran d'accueil?");
    test_string("Voulez-vous vraiment changer l'écran d'accueil? En vrai il est vraiment cool celui-là je comprends pas pourquoi vous voulez pas le garder srx !!");
}


int test_string(const char * string)
{
    char lines[6][MAX_LENGTH_LINE] = {0};
    char c;
    int lineIndex = 0;

	int wordPixelLen = 0;
	int linePixelLen = 0;
    int start = 0;
    int end = 0;
    for(int i = 0; i <= (int) strlen(string); i++) {
		if (string[i] == ' ' || string[i] == '\0' || string[i] == '\n') {
			if(linePixelLen + wordPixelLen <= PIXEL_LINE_WIDTH) {
				linePixelLen += wordPixelLen;
			} else {
				strncat(lines[lineIndex], &string[start], (int) (strlen(&string[start]) - strlen(&string[end])));
				start = end + 1;
				if (lineIndex < LINES_ON_SCREEN - 1) {
				lineIndex++;
				linePixelLen = wordPixelLen;
				} else
					break;
			}
			end = i;
			wordPixelLen = 0;
			if(string[i] == '\n' && lineIndex < LINES_ON_SCREEN - 1) {
				strncat(lines[lineIndex], &string[start], (int) (strlen(&string[start]) - strlen(&string[end])));
				start = i + 1;
				lineIndex++;
				linePixelLen = 0;
			}
			if(string[i] == '\0')
				strncat(lines[lineIndex], &string[start], (int) (strlen(&string[start])));
		}
		wordPixelLen += fontCharWidth(FONT_STANDARD & 0x7f, string[i]) + 1;
    }
    printLines(lines);

    return 0;
}

void printLines(char lines[6][MAX_LENGTH_LINE]){
    for(int i = 0; i < 6; i++)
        printf("Line Number %d is:%s\r\n", i+1, (char *) lines[i]);
    printf("\n");
}