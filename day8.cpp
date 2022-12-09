#include <iostream>
#include <fstream>
#include <vector>

/**
 * Find the visible trees from outside the grid looking only left, right, up, and down.
 * Tree height is denoted through 0 - 9 where trees can only be seen if the trees in
 * front of them are all shorter.
*/

#define ASCII_ZERO 48

void printForest(std::vector<std::vector<int>> forest){
    for (std::vector<int> &row : forest) {
        for (int &num : row) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }
}

bool isTallestInLine(std::vector<int> line, int start){
    int tallest = line[start];
    start++;
    while(start < line.size()){
        if(line[start] >= tallest) return false;
        start ++;
    }
    return true;
}

bool isTallestInCol(std::vector<std::vector<int>> forest, int row, int col, int dir){
    int tallest = forest[row][col];
    if(dir > 0){ // Check column above
        row --;
        for(int x = row; x >= 0; x--){
            if (forest[x][col] >= tallest) return false; 
        }
        return true;
    }else{ // Check column below
        row++;
        for(int x = row; x < forest[0].size(); x++){
            if (forest[x][col] >= tallest) return false; 
        }
        return true;
    }
}

int calcScenicScore(std::vector<std::vector<int>> forest, int row, int col){
    int curr_tree_height = forest[row][col];
    int score = 0;
    // Check col above
    for(int x = row-1; x >= 0; x--){
        if(forest[x][col] < curr_tree_height){ //next tree is shorter
            score++;
        }else{
            score++;
            break;
        }
    }
    int visible_trees = 0;
    // Check col below
    for(int x = row+1; x < forest[0].size(); x++){
        if(forest[x][col] < curr_tree_height){ //next tree is shorter
            visible_trees++;
        }else{
            visible_trees++;
            break;
        }
    }
    score *= visible_trees;
    visible_trees = 0;
    // Check row before
    for(int x = col-1; x >= 0; x--){
        if(forest[row][x] < curr_tree_height){ //next tree is shorter
            visible_trees++;
        }else{ 
            visible_trees++;
            break;
        }
    }
    score *= visible_trees;
    visible_trees = 0;
    // Check row after
    for(int x = col+1; x < forest.size(); x++){
        if(forest[row][x] < curr_tree_height){ //next tree is shorter
            visible_trees++;
        }else{ 
            visible_trees++;
            break;
        }
    }
    score *= visible_trees;
    return score;
}


int main(){
    std::ifstream infile;
    infile.open("day8input.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<int>> forest;
	while(std::getline(infile, line)){
        std::vector<int> row;
        for(char &c : line){
            row.push_back(c-ASCII_ZERO);
        }
        forest.push_back(row);
    }
    infile.close();

    // Part 1
    int visible_trees = 0;
    for(int row = 0; row < forest.size(); row++){
        int tallest_left = -1;
        for(int col = 0; col < forest[0].size(); col++){
            if(tallest_left < forest[row][col]){
                visible_trees++;
                tallest_left = forest[row][col];
                continue; 
            }else if(isTallestInLine(forest[row], col)){ // check rest of row
                visible_trees++;
                continue;
            }else if(isTallestInCol(forest, row, col, 1)){ //check col above
                visible_trees++;
                continue;
            }else if(isTallestInCol(forest, row, col, -1)){ // check col below
                visible_trees++;
                continue;
            }
        }
    }

    //Part 2
    int highest_scenic_score = 0;
    for(int row = 1; row < forest.size()-1; row++){
        for(int col = 1; col < forest[0].size()-1; col++){
            int score = calcScenicScore(forest, row, col);
            if(score > highest_scenic_score){
                highest_scenic_score = score;
            }
        }
    }

    std::cout << "Part 1: Total number of trees visible: " << visible_trees << "\n";
    std::cout << "Part 2: Highest scenic score of a tree: " << highest_scenic_score << "\n";
    return 0;
}