#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>


#define ASCII_LC_A 97

typedef std::pair<int,int> node;
typedef int (*heuristic_func)(node, node);

int heuristic(node, node);
void printGraph(std::vector<std::vector<int>>);
void reconstructPath(std::map<node, node>, node);
bool AStarSearch(node, node, std::vector<std::vector<int>>, heuristic_func);


/**
 * Struct to set default mapping to infinite
*/
struct IntDefaultedToMaxInt {
    int i = INT32_MAX;
    operator int() const {return i;}
};

/**
 * globally used map. Used in priority queue custom operator below.
*/
std::map<node, IntDefaultedToMaxInt> f_score;

/**
 * Custom compare for the priority queue to utilize f_score.
*/
struct {
        bool operator() (const node left, const node right) const {
            return f_score[left] > f_score[right]; }
    } fScore;

/**
 * Prints 2d vector
*/
void printGraph(std::vector<std::vector<int>> graph){
    for (std::vector<int> &row : graph) {
        for (int &num : row) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }
}

/**
 * Heuristic function for A* search. Caculates the shortest path between the current node
 * and the goal. That is, the most diagnoal path assuming it is possible.
 * @returns steps The number of steps required.
*/
int heuristic(node cur_node, node end){
    static node goal = end;
    int steps = abs(cur_node.first - goal.first) + abs(cur_node.second - goal.second);
    //std::cout << "Heuristic for node " << cur_node.first << "," << cur_node.second << ": " << steps << "\n";
    return steps;
}

/**
 * Reconstruct shortest path. Prints out path size.
*/
void reconstructPath(std::map<node, node> came_from, node current){
    static int minTotal = came_from.size();
    std::deque<node> total_path;
    total_path.push_back(current);
    while(came_from.find(current) != came_from.end() ){
        current = came_from[current];
        total_path.push_front(current);
    }
    // for(node &path_node : total_path){
    //     std::cout << "(" << path_node.first << ',' << path_node.second << ") ";
    // }
    if(total_path.size()-1 < minTotal) minTotal = total_path.size()-1;

    std::cout << "\n";
    std::cout << "Part 1: Number of steps for the shortest path: " << total_path.size()-1 << "\n";
    std::cout << "Part 2: Min number of steps for the shortest path from any 'a': " << minTotal << "\n";
}

/**
 * An implementation of A* Search that finds the cheapest (shortest) path from start to goal.
 * @returns True if path is found. False otherwise.
*/
bool AStarSearch(node start, node goal, std::vector<std::vector<int>> graph, heuristic_func hfunc){
    std::priority_queue<node, std::vector<node>, decltype(fScore)> open_set;
    open_set.push(start);
    std::map<node, int> inOpenSet;
    inOpenSet[start] = 1;
    // Node immediatly preceding n on cheapest path
    std::map<node, node> came_from;
    // Cheapest path from start to n
    std::map<node, IntDefaultedToMaxInt> g_score;
    struct IntDefaultedToMaxInt score;
    score.i = 0;
    g_score.insert(make_pair(start,score));
    // fScore[n] := gScore[n] + h(n)
    // Best guess to how cheap path will be if it goes through n
    struct IntDefaultedToMaxInt fscore;
    fscore.i = hfunc(start, goal);
    f_score.insert(make_pair(start, fscore));

    while(!open_set.empty()){
        node current = open_set.top();
        if(current == goal){
            //reconstruct path, goal is found
            reconstructPath(came_from, current);
            return true;
        }
        open_set.pop();
        inOpenSet.erase(current);
        // Get all admissible neighbours of current
        std::vector<node> cur_neighbours;
        node adjacent;
        if((current.first < graph.size()-1) && ((graph[current.first+1][current.second] - graph[current.first][current.second]) <= 1)){ //below
            adjacent.first = current.first +1;
            adjacent.second =  current.second;
            cur_neighbours.push_back(adjacent);
        } if((current.first > 0) && ((graph[current.first-1][current.second] - graph[current.first][current.second]) <=1 )){ //above
            adjacent.first = current.first -1;
            adjacent.second =  current.second;
            cur_neighbours.push_back(adjacent);
        }if((current.second > 0) && ((graph[current.first][current.second-1] - graph[current.first][current.second]) <=1 )){ //left
            adjacent.first = current.first;
            adjacent.second =  current.second-1;
            cur_neighbours.push_back(adjacent);
        }if((current.second < graph[0].size()-1) && ((graph[current.first][current.second+1] - graph[current.first][current.second]) <=1 )){ //right
            adjacent.first = current.first;
            adjacent.second =  current.second+1;
            cur_neighbours.push_back(adjacent);
        }
        for (node &neighbour : cur_neighbours){
            int tentative_score = g_score[current] + 1;
            if(tentative_score < g_score[neighbour]){
                //This path to neighbour is better
                came_from[neighbour] = current;
                struct IntDefaultedToMaxInt gscore;
                gscore.i = tentative_score;
                g_score[neighbour] = gscore;
                struct IntDefaultedToMaxInt fscore;
                fscore.i = tentative_score + hfunc(neighbour, goal);
                f_score[neighbour] = fscore;
                if(inOpenSet.count(neighbour) < 1){
                    open_set.push(neighbour);
                    inOpenSet[neighbour] = 1;
                }
            }
        }        
    }
    return false;
}

int main(){
    std::ifstream infile;
    infile.open("day12input.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<int>> graph;
    int row_num = 0;
    int col_num = 0;
    node start;
    node end;
    std::vector<node> all_starts;
	while(std::getline(infile, line)){
        std::vector<int> row;
        for(char &c : line){
            if(c == 'a'){
                all_starts.push_back({row_num, col_num});
            }
            if(c == 'S'){
                start.first = row_num;
                start.second = col_num;
                row.push_back(1);
                col_num ++;
                continue;
            }
            else if(c == 'E'){
                end.first = row_num;
                end.second = col_num;
                row.push_back(26);
                col_num ++;
                continue;
            } 
            col_num ++;
            row.push_back((int)c-ASCII_LC_A+1);
        }
        graph.push_back(row);
        row_num++;
        col_num = 0;
    }
    infile.close();

    //printGraph(graph);

    heuristic_func hfunc = &heuristic;
    AStarSearch(start, end, graph, hfunc);
    for(node &astart : all_starts){
        AStarSearch(astart, end, graph, hfunc);
    }
    return 0;
}