#include <fstream>
#include <iostream>
#include <vector>
#include <set>


#define ROW_OF_INTEREST 2000000


typedef std::pair<int,int> coord;


std::set<coord> beaconIsNot(std::set<coord> row, coord sensor, coord beacon){
    int man_distance = abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
    std::cout << "Man distance: " << man_distance << "\n";
    if(abs(ROW_OF_INTEREST - sensor.second) <= man_distance){
        //row.insert(sensor.first);
        int left_over = man_distance - abs(ROW_OF_INTEREST - sensor.second);
        std::cout << "Left over " << left_over << "\n";
        for(coord const& range : row){
            if(range.first > sensor.first-left_over){
                // x > newx
                if(range.second < sensor.first + left_over){
                    // if y < newy 
                    //insert new range
                    row.insert({sensor.first-left_over, sensor.first +left_over});
                    row.erase(range);
                    break;
                }else{
                    if(sensor.first + left_over < range.first){
                        // newy < x
                        if(*(row.rbegin()) == range){
                            row.insert({sensor.first-left_over, sensor.first +left_over});
                            break;
                        }
                        else continue;
                    }else{
                        // shift lower bound
                        row.erase(range);
                        row.insert({sensor.first-left_over, range.second});
                        break;
                    }
                }
            }else{
                // x < newx
                if(range.second < sensor.first + left_over){ // y < newy
                    if(sensor.first - left_over > range.second){ // newx < y 
                        if(*(row.rbegin()) == range){
                            row.insert({sensor.first-left_over, sensor.first +left_over});
                            break;
                        }
                        else continue;
                    }else{ //newx < y
                        // shift upper bound
                        row.erase(range);
                        row.insert({range.first, sensor.first + left_over});
                        break;
                    }
                }else{
                    //new range fully contained
                    break;
                }
            }
        }
        if(row.size() == 0){
            row.insert({sensor.first-left_over, sensor.first +left_over});
        }
    }
    std::cout << "\n";
    return row;
}


int main(){
    std::ifstream infile;
    infile.open("day15input.txt", std::ios::in);
    std::string line;
    int max_x;
    int min_x;
    int index = 0;
    std::set<coord> row;
	while(std::getline(infile, line)){
        int count = 0;
        coord sensor(0,0);
        coord beacon(0,0);
        coord* x_y = &sensor;
        std::string cur_num = "";
        for(char &c : line){
            count++;
            if(c == ','){
                // std::cout << cur_num <<".";
                x_y->first = stoi(cur_num);
                std::cout << x_y->first <<",";
                cur_num = "";
                continue;
            }
            if(count == line.size()){
                cur_num.push_back(c);
                // std::cout << cur_num <<".";
                x_y->second = stoi(cur_num);
                std::cout << x_y->second <<"\n";
                cur_num = "";
                row = beaconIsNot(row, sensor, beacon);
                std::cout << "RANGE: ";
                for(coord const& i : row){
                    std::cout << i.first << "-" << i.second << ",";
                }
                std::cout << "\n";
            }
            if(c == ':'){
                // std::cout << cur_num <<".";
                x_y->second = stoi(cur_num);
                std::cout << x_y->second <<"\n";
                cur_num = "";
                x_y = &beacon;
                if(index == 0){
                    max_x = sensor.first;
                    min_x = sensor.first;
                }
                else if(max_x < sensor.first) max_x = sensor.first;
                else if(min_x > sensor.first) min_x = sensor.first;
            }
            else if(isdigit(c) || c =='-'){
                cur_num.push_back(c);
                continue;
            }
        }
        index++;
    }
    infile.close();

    std::cout << "\n";
    std::cout << "RANGE: ";
    int position_count = 0;
    int prev_y = 0;
    for(coord const& i : row){
        std::cout << i.first << "-" << i.second << ",";
        position_count += (i.second - i.first);
        if(prev_y != 0 && prev_y > i.first){
            position_count -= (prev_y - i.first);
        }
        prev_y = i.second;
    }
    std::cout << "\n";


    std::cout << "Part 1: Number of positions that cannot contain a beacon: " << position_count << "\n";
    

    return 0;


}
