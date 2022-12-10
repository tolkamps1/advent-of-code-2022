#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <utility>


/**
 * Update position of tail so that it is no farther than 1 step away from head.
 * @return new tail position.
*/
std::pair<int, int> updateTail(std::pair <int, int> head, std::pair<int, int>tail){
    if((abs(head.first - tail.first) < 2) && (abs(head.second - tail.second) < 2)){ //no tail movement necessary
        return tail;
    }
    if(head.first != tail.first && head.second != tail.second){ // Must move diagonal
        int x_move = head.first - tail.first;
        int y_move = head.second - tail.second;
        if(abs(x_move) >=2){
            if(x_move > 0) x_move--;
            else x_move++;
        }if(abs(y_move) >=2){
            if(y_move > 0) y_move --;
            else y_move++;
        }
        return std::pair<int,int> (tail.first + x_move, tail.second + y_move);
    }
    else if(head.first > tail.first){ // Move adjacent R
        return std::pair<int,int> (tail.first+1, tail.second);
    }
    else if(head.first < tail.first){ // Move adjacent L
        return std::pair<int,int> (tail.first-1, tail.second);
    }
    else if(head.second > tail.second){ // Move adjacent U
        return std::pair<int,int> (tail.first, tail.second+1);
    }
    else{ // Move adjacent D
        return std::pair<int,int> (tail.first, tail.second-1);
    }
}


int main(){
    std::ifstream infile;
    infile.open("day9input.txt", std::ios::in);
    char dir;
    int steps;
    std::set<std::pair<int, int>> tail_positions;
    std::set<std::pair<int, int>> tail_ten_positions;
    std::vector<std::pair<int,int>> rope_state;
    std::pair<int, int> head(0,0); // x, y
    //entire rope starts at the same position
    for(int x = 0; x < 10; x++){
        rope_state.push_back(head);
    }
    tail_ten_positions.insert(head);
    tail_positions.insert(head);
    while(infile >> dir >> steps){
        while(steps > 0){
            switch(dir){
                case 'R':
                    head.first++;
                    break;
                case 'L':
                    head.first--;
                    break;
                case 'U':
                    head.second++;
                    break;
                case 'D':
                    head.second--;
                    break;
                default:
                    break;
            }
            rope_state.at(0) = head;
            for(int x = 1; x < 10; x++){
                rope_state.at(x) = updateTail(rope_state.at(x-1), rope_state.at(x));
            }
            tail_positions.insert(rope_state.at(1));
            tail_ten_positions.insert(rope_state.at(9));
            steps --;
        }
    }
    infile.close();

    std::cout << "Part 1: Total number spaces visited by the Tail with rope size 2: " << tail_positions.size() << "\n";
    std::cout << "Part 2: Total number spaces visited by the Tail with rope size 10: " << tail_ten_positions.size() << "\n";

    

    return 0;
}