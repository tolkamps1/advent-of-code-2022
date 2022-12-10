#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

/**
 * Calculate signal strength (value or register X * clock cycle) where each addx instruction
 * takes two clock cycles and noop takes 1 clock cycle.
*/

#define NUM_OF_SIG_STRENGTHS 6

void checkCycle(int* total_strengths, int cycle, int reg_x){
    static int num_cycles = 0;
    if ((cycle - 20) % 40 != 0 || num_cycles >= NUM_OF_SIG_STRENGTHS){
        return;        
    }
    else{
        *total_strengths += cycle * reg_x;
        num_cycles ++;
    }
}

void CRTDrawPixel(int cycle, int reg_x){
    if(abs(((cycle-1) % 40) - reg_x) <= 1){
        std::cout << "#";
    } else std::cout << ".";
    if(cycle % 40 == 0){
        std::cout << "\n";
    }
}

int main(){
    std::ifstream infile;
    infile.open("day10input.txt", std::ios::in);
    int cycle = 0;
    int reg_x = 1;
    int total_strengths = 0;
    std::string line;
    while (getline(infile, line)){
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while(getline(iss, token, ' ')){
            tokens.push_back(token);
        }

        cycle++;
        CRTDrawPixel(cycle, reg_x);
        checkCycle(&total_strengths, cycle, reg_x);
        if(tokens[0] == "noop"){
            continue;
        }else if(tokens[0] == "addx"){
            cycle++;
            CRTDrawPixel(cycle, reg_x);
            checkCycle(&total_strengths, cycle, reg_x);
            reg_x += stoi(tokens[1]);
        }
    }
    infile.close();

    std::cout << "Part 1: Sum of interesting signal strengths: " << total_strengths << "\n";
    return 0;
}