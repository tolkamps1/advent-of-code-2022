#include <iostream>
#include <fstream>

using namespace std;

int getPriority(char c){
    if(isupper(c)){
        return int(c) - 38;
    }else{
        return int(c) - 96;
    }
}

int main(){
    ifstream infile;
    string line;
    int missplaced_priorities = 0;
    infile.open("day3input.txt", ios::in);
    while(getline(infile, line)){
        int letters[53] = {};
        int x = 0;
        while(x < line.length()){
            int p = getPriority(line[x]);
            if(x < line.length()/2){
                letters[p] += 1;
            }
            else if(letters[p] > 0){
                missplaced_priorities += p;
                break;
            }
            x++;
        }
    }
    infile.close();
    cout << "Part 1: Total missplaced priorities: " << missplaced_priorities << "\n";
    return 0;
}