#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream infile("day2input.txt");
    int total_score_p1 = 0;
    int total_score_p2 = 0;
    char opponent, myplay;
    while(infile >> opponent >> myplay){
        int op = int(opponent) % 64;
        int me = int(myplay) % 87;
        total_score_p1 += ((me - op + 4) % 3 * 3) + me;
        total_score_p2 += ((me + 2) % 3 * 3) + ((me + op) % 3 +1 ) ;
    }
    infile.close();
    cout << "Part 1: Total score of rock paper scissors game: " << total_score_p1 << "\n";
    cout << "Part 2: Total score of rock paper scissors game: " << total_score_p2 << "\n";

    return 0;
}
