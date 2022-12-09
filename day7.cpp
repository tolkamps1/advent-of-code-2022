#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <deque>
#include <set>


#define MAX_DISK_SIZE 70000000
#define MIN_REQ_SPACE 30000000
#define PT_ONE_MAX 100000


struct file{
    std::string file_name;
    int file_size;
};
typedef struct file File;

struct node{
    std::string dir_name;
    std::vector <File> containing_files;
};
typedef struct node DirNode;


int main(){
    std::ifstream infile;
    infile.open("day7input.txt", std::ios::in);
    std::map <std::string, DirNode> allDir;
    std::deque<std::string> dir_path;
    std::string line;
    while (getline(infile, line)){
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while(getline(iss, token, ' ')){
            tokens.push_back(token);
        }
        if(tokens[1] == "cd"){ //command
            if(tokens[2] == ".."){ //go up one level
                dir_path.pop_back();
                continue;
            }
            else if(tokens[2] == "/"){ //go to home dir
                dir_path.clear();
                dir_path.push_back("/");
                continue;
            }
            else{ //go down one level
                dir_path.push_back(tokens[2]);
                continue;
            }            
        }
        if(tokens[1] == "ls"){// ls command
            continue;
        }
        else if(tokens[0] == "dir"){ //output dir
            continue;
        }
        else{ //output file
            std::string path_name = "";
            //iterate through whole dir path and add file_name to internal files.
            for (auto it = dir_path.begin(); it != dir_path.end(); ++it) {
                path_name += *it;
                File file;
                file.file_name = tokens[1];
                file.file_size = stoi(tokens[0]);
                allDir[path_name].containing_files.push_back(file);
            }
        }
    }
    infile.close();

    int all_sizes_small = 0;
    int closest_to = MAX_DISK_SIZE;
    int size_of_all = 0;
    std::map<std::string, DirNode>::iterator it;
    // Iterate through all directories and calculate their size
    for (auto it = begin(allDir); it != end(allDir); ++it){
        int total_sizes = 0;
        std::vector<File> files = it->second.containing_files;
        std::vector<File>::iterator fileit;
        // Iterate through each directories list of files
        for (fileit = files.begin(); fileit != files.end(); fileit++){
            total_sizes += fileit->file_size;
        }
        // Calculate sizes for Part 1
        if(total_sizes <= PT_ONE_MAX){
            all_sizes_small += total_sizes;
        }
        if(it->first == "/"){
            size_of_all = total_sizes;
            continue;
        }
        // Calculate minimum deletion for part 2
        if(((MAX_DISK_SIZE - size_of_all + total_sizes) >= MIN_REQ_SPACE)){
            if(total_sizes < closest_to){
                closest_to = total_sizes;
            }
        } 
    }

    std::cout << "Part 1: Sum of directory sizes that are <= 100000: " << all_sizes_small << "\n";
    std::cout << "Part 2: Directory size that will make available a total of 30000000 space: " << closest_to << "\n";
   
    return 0;
}

