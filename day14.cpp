#include <fstream>
#include <iostream>
#include <vector>


/**
 * Values to reduce coordinates by to keep graph managable.
*/
#define MAX_GRAPH 350
#define X_REDUCTION 325
#define SAND_START 500 - X_REDUCTION

typedef std::pair<int,int> coord;

/**
 * Prints 2D vector of chars
*/
void printGraph(std::vector<std::vector<char>> graph, int max_y){
    std::cout << "X-axis start: " << X_REDUCTION;
    int row_count = 0;
    for (std::vector<char> &row : graph) {
        if(row_count > max_y) break;
        std::cout << '\n' << row_count << " ";
        for (char &c : row) {
            std::cout << c;
        }
        row_count++;
    }
    std::cout << "\n\n";
}

/**
 * Helper function to keep coordinates managable when printing.
*/
int reduceX(int num){
    return num-X_REDUCTION;
}

/**
 * Insert sand starting at start position. Print graphwhen full of sand.
*/
int insertSand(std::vector<std::vector<char>> graph, int max_y){
    bool fell_off = false;
    bool sand_stopped = false;
    int sand_caught = 0;
    coord sand_pos = {SAND_START, 0};
    while(!sand_stopped && !fell_off){
        if(sand_pos.second + 1 > max_y){
            fell_off = true;
            printGraph(graph, max_y);
            continue;
        }
        else if(graph[sand_pos.second+1][sand_pos.first] == '.'){ //Moves down
            sand_pos.second += 1;
            continue;
        }
        else if(graph[sand_pos.second+1][sand_pos.first-1] == '.'){ //Moves down-left
            sand_pos.second += 1;
            sand_pos.first -= 1;
            continue;
        }
        else if(graph[sand_pos.second+1][sand_pos.first+1] == '.'){// Moves down-right
            sand_pos.second += 1;
            sand_pos.first += 1;
            continue;
        }else{
            sand_stopped = true;
            sand_caught++;
            graph[sand_pos.second][sand_pos.first] = 'o';
            // Add new sand unit
            if(sand_pos.first == SAND_START && sand_pos.second == 0){
                printGraph(graph, max_y);
                return sand_caught;
            }
        }
    }
    if(fell_off) return sand_caught;
    else return sand_caught + insertSand(graph, max_y);
}

int main(){
    std::ifstream infile;
    infile.open("day14input.txt", std::ios::in);
    std::string line;
    std::vector<char> y(MAX_GRAPH, '.');
    std::vector<std::vector<char>> rock_graph(MAX_GRAPH-150, y);
    int max_y = 0;
	while(std::getline(infile, line)){
        int count = 0;
        coord start(0,0);
        coord end(0,0);
        coord* x_y = &start;
        std::string cur_num = "";
        for(char &c : line){
            count++;
            if(c == ','){
                x_y->first = reduceX(stoi(cur_num));
                cur_num = "";
                continue;
            }
            if(c == '>' || count == line.size()){
                if(count == line.size()) cur_num.push_back(c);
                x_y->second = stoi(cur_num);
                cur_num = "";
                if(count > 10){
                    int s_x = start.first;
                    int s_y = start.second;
                    if(end.second > max_y) max_y = end.second;
                    while(s_x != end.first || s_y != end.second){
                        rock_graph[s_y][s_x] = '#';
                        if(s_x - end.first == 0){
                            if((s_y - end.second) > 0) s_y--;
                            else s_y++;
                        }else{
                            if((s_x - end.first) > 0) s_x--;
                            else s_x++;
                        }
                    }
                    rock_graph[s_y][s_x] = '#';
                    start.first = end.first;
                    start.second = end.second;
                }
                x_y = &end;
                continue;
            }
            else if(isdigit(c)){
                cur_num.push_back(c);
                continue;
            }
        }
    }
    infile.close();

    // Part 1
    int caught_p1 = insertSand(rock_graph, max_y);
    
    // Part 2: insert floor
    max_y += 2;
    std::vector<char> floor(MAX_GRAPH, '#');
    rock_graph[max_y] = floor;
    int caught_p2 = insertSand(rock_graph, max_y);

    std::cout << "Part 1: Number of sand units caught: " << caught_p1 << "\n";
    std::cout << "Part 2: Number of sand units caught with floor: " << caught_p2 << "\n";

    return 0;
}