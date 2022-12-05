#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream infile;
	int contained_pairs = 0;
    int overlapping_pairs = 0;
    infile.open("day4input.txt", ios::in);
	int a, b, c, d;
    char e;
	while(infile >> a >> e >> b >> e >> c >> e >> d){
		if ((a <= c && b >= d) || (a >= c && b <= d)){
			contained_pairs ++;
		}
        if (b < c || a > d){
			overlapping_pairs --;
		}
        overlapping_pairs ++;
	}
	infile.close();
	cout << "Part 1: Total number of completely overlaping sections: " << contained_pairs << "\n";
	cout << "Part 2: Total number of overlaping sections: " << overlapping_pairs << "\n";
    return 0;
}