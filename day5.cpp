#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>

int main(){
    std::ifstream infile;
    infile.open("day5input.txt", std::ios::in);
    std::string line;
    int num, from, to;
    std::string delim;
    std::vector<std::vector<char>> stacks{};
    // Initialize vector of vectors to store crates in stacks
    for (int x = 0; x < 9; x++){
        std::vector<char> astack;
        stacks.push_back(astack);
    }
    int count = 0;
    while (getline(infile, line)){
        count++;
        // Pre-process initial stack set up
        if (count < 9){
            for (int x = 0; x < 9; x++){
                if (std::isspace(line[1 + 4 * x]))
                    continue;
                stacks[x].insert(stacks[x].begin(), line[1 + 4 * x]);
            }
        }
        // Process crate movement.
        else{
            std::istringstream iss(line);
            if (!(iss >> delim >> num >> delim >> from >> delim >> to) || (delim != "to"))
                continue;
            std::vector<char> movedcrates;
            for (int x = 0; x < num; x++){
                movedcrates.push_back(stacks[from - 1].back());
                stacks[from - 1].pop_back();
            }
            // Part 2 moving stacks of crates, rather than one at a time.
            while (!movedcrates.empty()){
                stacks[to - 1].push_back(movedcrates.back());
                movedcrates.pop_back();
            }
        }
    }

    infile.close();

    std::cout << "Part 2: Crates on top of each stack: \n";
    for (int x = 0; x < 9; x++){
        std::cout << "Stack " << x << ": " << stacks[x].back() << "\n";
    }
    return 0;
}