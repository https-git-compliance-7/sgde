#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include<stdio.h>
#include <string.h>

#define VAR 1
#define OTHER 2
#define STRING 3
#define NUM 4
#define OPERATOR 5

using namespace std;
vector<string> tokens;
vector<string> tok_freq;
vector<string> file_names;
int tok[100000];
string highest;


int main() {
			int current = 0;
			int max = 0;
    // http://www.cplusplus.com/forum/beginner/9173/
        DIR *p1DIR;
        struct dirent *entry1;
        if( p1DIR=opendir(".") ){
                while(entry1 = readdir(p1DIR)){
			if( strcmp(entry1->d_name, ".") != 0 && strcmp(entry1->d_name, "..") != 0 && strcmp(entry1->d_name, "test") != 0 && strcmp(entry1->d_name, "test4.cpp") != 0 && strcmp(entry1->d_name, "freq.cpp") != 0 && strcmp(entry1->d_name, "results") != 0) {
				file_names.push_back(entry1->d_name);
    				ifstream file0(entry1->d_name);
				string lines;
			 	while (getline(file0, lines)) {
					bool matchfound = false;
					for (int z=0;z<tok_freq.size();z++) {
						if (lines == tok_freq.at(z)) {
							matchfound = true;
							tok[z]++;
							break;
						}
					}
					if (!matchfound) {
						tok_freq.push_back(lines);
						int n = tok_freq.size()-1;
						tok[n] = 1;
					}
				}
			}
		}
	}
	ofstream output2;
    	output2.open("freq.cpp");
	for (int y=0;y<tok_freq.size();y++) {
   		output2 << tok_freq.at(y) << " " << tok[y] << endl;
	}
   	 output2.close();

	while(file_names.size() > 0) {
			string thisFile = file_names.at(0);
        DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir(".") ){
                while(entry = readdir(pDIR)){

                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, thisFile.c_str()) != 0 && strcmp(entry->d_name, "test") != 0 && strcmp(entry->d_name, "test4.cpp") != 0 && strcmp(entry->d_name, "freq.cpp") != 0 && strcmp(entry->d_name, "results") != 0) {
			tokens.clear();
    			ifstream file(thisFile.c_str());
   			 string line;

   			 while (getline(file, line)) {
				tokens.push_back(line);
    			}
			
			current = 0;
                        cout << entry->d_name << "\n";
    			ifstream file2(entry->d_name);
			string matches = "";
			 while (getline(file2, line)) {
				cout << "reading line" << endl;
				for (int i=0;i<tokens.size();i++) {
					if (line == tokens.at(i)) {
						int counter = 0;
						for (int x=0;x<tok_freq.size();x++) {
							if (line == tok_freq.at(x)) {
								counter = tok[x];
							}
						}
						if (counter > 0 && counter < 10) {
							current++;
							matches = matches + line + "\n";
						}
							//current++;
							//matches = matches + line + "\n";
						tokens.erase(tokens.begin() + i);
						break;
					}
				}
			}
			if (current > 5) {
			stringstream ss;
			ss << current;
			string str = ss.str();
    			ofstream output;
   			 char outpath[300];
			string firstBit = str + file_names.at(0);
    			strcpy(outpath, "results/");
    			strcat(outpath, firstBit.c_str());
   			 strcat(outpath, entry->d_name);
    			output.open (outpath);
   			 output << matches;
   			 output.close();
			}

			if (current > max) {
				max = current;
				highest = entry->d_name;
			}
		        }
		}
	}
    cout << highest << " " << max << endl;
    remove(thisFile.c_str());
    file_names.erase (file_names.begin());
    }
}
