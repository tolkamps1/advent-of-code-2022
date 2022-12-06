#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>

int main(){
    std::ifstream infile;
    infile.open("day6input.txt", std::ios::in);
    char leading_char;
    int count, message_count, packet_count = 0;
    std::deque<char> four_chars;
	while(infile.get(leading_char)){
        count++;
        if(std::find(four_chars.begin(), four_chars.end(), leading_char) == four_chars.end()){
            four_chars.push_back(leading_char);
            if(four_chars.size() == 4 && packet_count == 0){
                packet_count = count;
            }
            if(four_chars.size() == 14){
                message_count = count;
                break;
            }
        }else{
            while(four_chars.front() != leading_char){
                four_chars.pop_front();
            }
            four_chars.pop_front();
            four_chars.push_back(leading_char);
        }
    }
    infile.close();
    std::cout << "Part 1: Start-of-packet marker complete after: " << packet_count << " characters. \n";
    std::cout << "Part 2: Start-of-message marker complete after: " << message_count << " characters. \n";
    return 0;

}