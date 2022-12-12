#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>

#define NUM_OF_ROUNDS 10000

struct MonkeyTest{
    int divisible_by;
    int true_monkey;
    int false_monkey;
};

class Monkey {
    private:
        int mult_op;
        int add_op;
        int relief_factor = 3;
        MonkeyTest test;
        long inspectOp(long worry);
        long relief(long worry);
        int passToMonkey(long worry);
        int inspection_count = 0;
        std::deque<long> items;
    public:
        Monkey(int mult, int add, MonkeyTest tests){
            mult_op = mult;
            add_op = add;
            test = tests;
        }
        int getCount(){ return inspection_count;}
        void addItem(long newitem) {items.push_back(newitem);}
        void updateRelief(int relief_factor) {this->relief_factor = relief_factor;}
        long getItem(){ 
            if(items.empty()) return -1;
            return items.front();
            }
        void removeItem(){ items.pop_front(); }
        void printItems();
        int takeTurn(); 
};

long Monkey::inspectOp(long worry){
    inspection_count ++;
    if(mult_op == -1){
        return worry*worry + add_op;
    }
    else{
        return worry * mult_op + add_op;
    }
}

long Monkey::relief(long worry){
    worry = worry % relief_factor;
    if(worry == 0 ){
        worry = relief_factor;
    }
    return worry;
    // Part 1: return worry/3;
}

int Monkey::passToMonkey(long worry){
    if(worry % test.divisible_by == 0){
        return test.true_monkey;
    } return test.false_monkey;
}

/**
 * Monkey's turn.
 * 1. Take first item.
 * 2. Calculate new worry after inspection operation and relief.
 * 3. Test which monkey will recieve item.
 * 4. Remove item from monkey items.
 * @return newMonkey The monkey number to receive the first item.
*/
int Monkey::takeTurn(){
    if(this->items.empty()){
        return -1;
    }
    long item = items.front();
    item = inspectOp(item);
    item = relief(item);
    int newMonkey = passToMonkey(item);
    items.pop_front();
    items.push_front(item);
    return newMonkey;
}

void Monkey::printItems(){
    for(int x = 0; x < items.size(); x++){
        std::cout << " " << items.at(x);
    }
}

inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v"){
    s.erase(0, s.find_first_not_of(t));
    return s;
}

int main(){
    std::ifstream infile;
    infile.open("day11input.txt", std::ios::in);
    std::vector<Monkey> monkeys;
    std::vector<long> items;
    std::vector<int> divisibles;
    int mult;
    int add;
    MonkeyTest test;
    std::string line;
    while (getline(infile, line)){
        if(line == "") continue;
        std::istringstream iss(ltrim(line));
        std::vector<std::string> tokens;
        std::string token;
        while(getline(iss, token, ' ')){
            tokens.push_back(token);
        }
        if(tokens[0] == "Monkey" && tokens[1] != "0:"){
            Monkey newMonkey = Monkey(mult, add, test);
            for(auto it = items.begin(); it != items.end(); ++it){
                newMonkey.addItem(*it);
            }
            std::string monkey_num = tokens[1];
            monkey_num[1] = '\0';
            monkeys.push_back(newMonkey);
            items = {};
            continue;
        }
        if(tokens[1] == "items:"){
            for(int x = 2; x < tokens.size(); x++){
                std::string num = tokens[x];
                if(*(num.end()-1) == ','){
                    num.erase(num.end()-1);
                }
                items.push_back(stoi(num));
            }
            continue;
        }
        if(tokens[0] == "Operation:"){
            if(tokens[4] == "*"){
                if(tokens[5] == "old"){
                    mult = -1;
                    add = 0;
                }else{
                    mult = stoi(tokens[5]);
                    add = 0;
                }
            }
            else{
                mult = 1;
                add = stoi(tokens[5]);
            }
            continue;
        }
        if(tokens[0] == "Test:"){
            test.divisible_by = stoi(tokens[3]);
            divisibles.push_back(stoi(tokens[3]));
            continue;
        }
        if(tokens[1] == "true:"){
            test.true_monkey = stoi(tokens[5]);
            continue;
        }
        if(tokens[1] == "false:"){
            test.false_monkey = stoi(tokens[5]);
            continue;
        }
    }
    infile.close();

    // Part 2. Calculate the LCM of all tests in order to keep item 
    // worry under control.
    int max = divisibles.back();
    for(int &num : divisibles){
        if(num > max) max = num;
    }
    int new_relief;
    while(true){
        int count = 0;
        for(int &num : divisibles){
            if(max % num == 0) count++;
            else{
                max++;
                count = 0;
            }
        }
        if (count == divisibles.size()){
            new_relief = max;
            break;
        }
    }
    
    //add last monkey
    Monkey newMonkey = Monkey(mult, add, test);
    for(auto it = items.begin(); it != items.end(); ++it){
        newMonkey.addItem(*it);
    }
    monkeys.push_back(newMonkey);

    //update releif factor in all monkeys
    for(int y = 0; y < monkeys.size(); y++){
        monkeys.at(y).updateRelief(new_relief);
    }

    // Execute rounds
    for(int x = 0; x < NUM_OF_ROUNDS; x++){
        for(int y = 0; y < monkeys.size(); y++){
            Monkey cur_monkey = monkeys.at(y);
            for(long monkey_item = cur_monkey.getItem(); monkey_item != -1; monkey_item = cur_monkey.getItem()){
                int newMonkey = cur_monkey.takeTurn();
                monkey_item = cur_monkey.getItem();
                cur_monkey.removeItem();
                cur_monkey.printItems();
                monkeys.at(y) = cur_monkey;
                monkeys.at(newMonkey).addItem(monkey_item);
                monkeys.at(newMonkey).printItems();
            }
        }
    }

    // print monkey state
    for(int y = 0; y < monkeys.size(); y++){
        std::cout << "Monkey : " << y << " ";
        monkeys.at(y).printItems();
        std::cout << "\n";
    }

    // Calculate two most mischievous monkeys
    long max1 = 0;
    long max2 = 0;
    for(int y = 0; y < monkeys.size(); y++){
        if(monkeys.at(y).getCount() >= max1){
            max2 = max1;
            max1 = monkeys.at(y).getCount();
        } else if(monkeys.at(y).getCount() >= max2){
            max2 = monkeys.at(y).getCount();
        }
    }
    long monkey_business = max1 * max2;

    std::cout << "Part 2: Monkey business after " << NUM_OF_ROUNDS << " rounds: " << monkey_business << "\n";

    return 0;

}