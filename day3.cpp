#include <iostream>
#include <fstream>
#include <set>

using namespace std;

#define NUM_OF_LETTERS 52

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
    int group_priorities = 0;
    int group = 1;
    int group_letters[NUM_OF_LETTERS+1] = {};
    infile.open("day3input.txt", ios::in);
    while(getline(infile, line)){
        int letters[NUM_OF_LETTERS+1] = {};
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
        //Part 2
        set<int> line_letters;
        int letter = 0;
        while(letter < line.length()){
            line_letters.insert(getPriority(line[letter]));
            letter++;
        }
        for(auto& num: line_letters){
            group_letters[num] += 1;
        }
        group++;
        if(group > 3){
            group = 1;
            for(int x = 1; x < NUM_OF_LETTERS+1; x++){
                if(group_letters[x] >= 3){
                    group_priorities += x;
                    break;
                }
            }
            std::fill_n(group_letters, 53, 0);
        }
        
    }
    infile.close();
    cout << "Part 1: Total missplaced priorities: " << missplaced_priorities << "\n";
    cout << "Part 2: Total priorities for each group: " << group_priorities << "\n";
    return 0;
}