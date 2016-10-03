// Breaks up every file in the directory into its component 4-grams
// Replace variables with VAR
// Find files with the most similar number of grams (low frequency)

#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>

#define VAR 1
#define OTHER 2
#define STRING 3
#define NUM 4
#define OPERATOR 5

using namespace std;

string fileArr[] = {};
int count = 0;

int main() {
    int state;
    // http://www.cplusplus.com/forum/beginner/9173/
        DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir("../sgde/data") ){
                while(entry = readdir(pDIR)){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
			count++;
                        cout << entry->d_name << "\n";
    char path[300];
    strcpy(path, "../sgde/data/");
    strcat(path, entry->d_name);
    cout << path << endl;
    ifstream file(path);
    string line;
    vector<string> gramArray;
    int lineCount = 0;
    string resArray[] = {"include", "int", "string", "long", "using", "typedef", "define", "for", "else", "break", "continue", "if", "while", "float", "freopen", "scanf", "printf", "cout", "std", "endl", "double"};

    while (getline(file, line)) {
        lineCount++;
        cout << "Line " << lineCount << endl;
        string fourGram[4];
        int currentNo = 0;
	int tokPos = 0;
        int next = 0;
        bool dualSym = false;
        bool alphaNum = false;
	bool startString = false;
        string charString;
        char sym;
	char prevChar = 'x';

	// Read line by line
        for(int i=0;i<line.length();i++) {
            /* cout << "Pos: " << i << "    " << line[i] << "     CurrentNo:" << currentNo << "   " << dualSym << endl; */

		// Determine type of token
		if (currentNo == 0) {
			next++;
		}
		if (tokPos == 0) {
		if (line[i] == '\'' || line[i] == '"') {
			if (startString) {
				startString = false;
				fourGram[currentNo] = line[i];
				tokPos++;
			}
			else {
				startString = true;
				fourGram[currentNo] = line[i];
				tokPos++;
			}
		}
		else if (!startString) {
			if (isdigit(line[i]) || (line[i] == '-' && prevChar == ' ')) {
				state = NUM;
				fourGram[currentNo] = line[i];
				tokPos++;
			}
               		else if (line[i] == '+' || line[i] == '-' || line[i] == '<' || line[i] == '>' || line[i] == '=' || line[i] == '|') {
                   		state = OPERATOR;
				fourGram[currentNo] = line[i];
				tokPos++;
			}
			else if (isalpha(line[i])) {
				state = VAR;
				fourGram[currentNo] = line[i];
				tokPos++;
			}
			else if (line[i] != ' ' && line[i] != '\t') {
				if (isdigit(toascii(line[i])) && toascii(line[i]) < 128 && toascii(line[i]) > 0) {
				state = OTHER;
				fourGram[currentNo] = line[i];
				currentNo++;
				tokPos = 0;
				}
			}
		}
		else {
			next++;
		}
		}

		else if (line[i] == ' ' || line[i] == '\t') {
			if (!startString) {
				if (state == VAR) {
						/* bool resWord = false;
						for (int f = 0; f<21; f++) {
							if (currentNo < 4) {
							if (resArray[f] == fourGram[currentNo]) {
								resWord = true;
							}
							}
						}
						if (!resWord) {
							fourGram[currentNo] = "var";
						} */
				}
				currentNo++;
				tokPos = 0;
			}
			else {
				fourGram[currentNo] = fourGram[currentNo] + line[i];
			}
		}

		// Add character to token
		else {

			switch(state) {
				case VAR:
					if (isalpha(line[i]) || isdigit(line[i])) {
						fourGram[currentNo] = fourGram[currentNo] + line[i];
					}
					else {
						if (isdigit(toascii(line[i])) && toascii(line[i]) < 128 && toascii(line[i]) > 0) {
						/*bool resWord = false;
						for (int f = 0; f<21; f++) {
							if (currentNo < 4) {
							if (resArray[f] == fourGram[currentNo]) {
								resWord = true;
							}
							}
						}
						if (!resWord) {
							fourGram[currentNo] = "var";
						} */
						currentNo++;
						tokPos = 0;
						i--;
						}
					}
					break;
				case NUM:
					if (isdigit(line[i]) || line[i] == '.') {
						fourGram[currentNo] = fourGram[currentNo] + line[i];
					}
					else if (isdigit(toascii(line[i])) && toascii(line[i]) < 128 && toascii(line[i]) > 0) {
						currentNo++;
						tokPos = 0;
						i--;
					}
					break;
				case OTHER:
					currentNo++;
					tokPos = 0;
					i--;
					break;
				default:
					if (isdigit(toascii(line[i])) && toascii(line[i]) < 128 && toascii(line[i]) > 0) {
						fourGram[currentNo] = line[i];
					}
				
			}

		}

            /* Add complete 4-gram to array and reset */
            if (currentNo == 4) {
                string fGram = fourGram[0] + ' ' + fourGram[1] + ' ' + fourGram[2] + ' ' + fourGram[3];
                cout << "Line " << lineCount << endl;
                cout << "Next: " << next << endl;
                cout << "Current: " << i << endl << endl;
                cout << fGram << endl;
                gramArray.push_back(fGram);
                currentNo = 0;
                if (i != (line.length() - 1)) {
                    i = next - 1;
                }
            }
		prevChar = line[i];
        }
    }

    ofstream output;
    char outpath[300];
    strcpy(outpath, "output8/");
    strcat(outpath, entry->d_name);
    output.open (outpath);
    for (int i=0;i<gramArray.size();i++) {
        output << gramArray.at(i) << endl;
    }
    output.close();
    }

                }
                closedir(pDIR);
        }
    return 0;
}
