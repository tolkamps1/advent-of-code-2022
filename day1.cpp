#include <iostream> //cout cin
#include <fstream>

using namespace std;

int main(){
    ifstream infile;
    string line;
    int elf_cal = 0;
    int max_one = 0;
    int max_two = 0;
    int max_three = 0;
    infile.open("day1input.txt", ios::in);
    while(getline(infile, line)){
        if(!line.empty()){
            elf_cal += stoi(line);
        }
        else{
            if(elf_cal >= max_one){
                max_three = max_two;
                max_two = max_one;
                max_one = elf_cal;
            }
            else if(elf_cal >= max_two){
                max_three = max_two;
                max_two = elf_cal;
            }
            else if(elf_cal >= max_three){
                max_three = elf_cal;
            }
            elf_cal = 0;
        }
    }
    infile.close();

    cout << "Part 1: Max calories carried by one elf: " << max_one << "\n";
    cout << "Part 2: Total calories carried by three strongest elves: " << max_one + max_two+ max_three << "\n";
    
    return 0;
}