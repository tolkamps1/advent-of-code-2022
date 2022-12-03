#include <iostream>
#include <fstream>

using namespace std;

/*
X: Rock
Y: Paper
Z: Scissors

X > Z, Y > X, Z > Y
1 > 3, 2 > 1, 3 > 2

1 - 1 = 0

op - me  = 0
1 - 3 = -2
2 - 1 = 1
3 - 2 = 1

op - me = 6
3 - 1 = 2
2 - 3 = -1
1 - 2 = -1

A, X = 3
B, Y = 3
C, Z = 3

A, Y = 6
A, Z = 0
*/


int winScore(int opponent, int me){
    opponent = opponent % 64;
    me = me % 87;
    if (opponent == me){
        return 3;
    }else if (opponent == 1 && me == 3){
        return 0;
    }else if (opponent == 3 && me == 1){
        return 6;
    }else if(opponent > me){
        return 0;
    }else {
        return 6;
    }
}

int choiceScore(char me){
    int score = int (me) % 87;
    return score;
}

int main(){
    ifstream infile("day2input.txt");
    int total_score_p1 = 0;
    int total_score_p2 = 0;
    char opponent, me;
    while(infile >> opponent >> me){
        total_score_p1 += winScore(int (opponent),int (me)) + choiceScore(me);
        //cout << int (me) % 85 << "\n";
        cout << "win score" << ((int(me)% 85) % 3 * 3) << "\n";
        cout << ((int (opponent) % 64 + (int (me)%87 ))% 3 +1) << "\n";
        total_score_p2 += ((int(me)% 85) % 3 * 3) + ((int (opponent) % 64 + (int (me)%87 ))% 3 +1 ) ;
    }
    infile.close();
    cout << "Part 1: Total score of rock paper scissors game: " << total_score_p1 << "\n";
    cout << "Part 2: Total score of rock paper scissors game: " << total_score_p2 << "\n";


    return 0;
}
