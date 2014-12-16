#include "ProbDist.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * The first line contains the number of ladders and snakes, separated by a comma. 
 * 3,7     3 ladders, 7 snakes
 * The second is a list of comma separated pairs indicating the starting and ending squares of the ladders. 
 * The first point is the square from which a player can ascend and the second point is his final position. 
 * 32,62 42,68 12,98
 * The third is a list of comma separated pairs indicating the starting and ending (mouth and tail) squares of the snakes. 
 * the first point is the position of the mouth of the snake and the second one is the tail. 
 * 95,13 97,25 93,37 79,27 75,19 49,47 67,17
 */

map< int, int > string_to_pair(string str) {

    map < int, int > str_pair;


    string delimiter1 = " ";
    string delimiter2 = ",";

    int pos, pos2, first, second = 0;
    string token;
    while ((pos = str.find(delimiter1)) != string::npos) {
        token = str.substr(0, pos);

        pos2 = token.find(delimiter2);
        first = atoi(token.substr(0, pos2).c_str());
        second = atoi(token.substr(pos2 + delimiter2.length(), token.length()).c_str());
        str_pair.insert(make_pair(first, second));

        str.erase(0, pos + delimiter1.length());
    }

    first = atoi(str.substr(0, str.find(delimiter2)).c_str());
    second = atoi(str.substr(str.find(delimiter2) + delimiter2.length(), str.length()).c_str());
    str_pair.insert(make_pair(first, second));
    return str_pair;

}

vector< vector<float> > fill_trans_mat(map<int, int> ladders, map<int, int> snakes, int board_size, int dice_sides, float prob) {
    vector< vector<float> > trans_mat;

    trans_mat.resize(board_size + 1);
    for (int x = 0; x < board_size + 1; x++) { // current square
        // resize and zero out
        trans_mat[x].resize(board_size + 1);
        for (int y = 0; y < board_size + 1; y++) {
            trans_mat[x][y] = 0;
        }

        // probability of landing in future square
        //        if (ladders.find(x) == ladders.end() && snakes.find(x) == snakes.end() && x != 0) {
        for (int i = 1; i < dice_sides + 1; i++) {
            if (x + i < board_size + 1) { // within gameboard
                if (ladders.find(x + i) != ladders.end()) { // if future square is bottom of a ladder
                    trans_mat[x][ladders.find(x + i)->second] = trans_mat[x][ladders.find(x + i)->second] + prob; // then go to the top
                } else if (snakes.find(x + i) != snakes.end()) { // if future square is mouth of a snake
                    trans_mat[x][snakes.find(x + i)->second] = trans_mat[x][snakes.find(x + i)->second] + prob; // then go to the tail
                } else
                    trans_mat[x][x + i] += prob;
            } else // finished game
                trans_mat[x][board_size] += prob;

        }
        //        }
    }

    return trans_mat;
}

void print_pairs(map<int, int> p) {
    for (map<int, int >::const_iterator it = p.begin(); it != p.end(); ++it) {
        std::cout << it->first << " " << it->second << endl;
    }
    cout << endl;

}


int main(int argc, char** argv) {
    ProbDist pb;
    
    string input_ladders = "5,6"; // bottom,top
    string input_snakes = "4,3 8,7"; //mouth,tail
    int board_size = 10;
    float dice_sides = 3.0;
    float prob = (1.0 / dice_sides);

    map<int, int> ladders = string_to_pair(input_ladders);
    map<int, int> snakes = string_to_pair(input_snakes);
    vector< vector<float> > ab, prob_dist, trans_mat;

    trans_mat = fill_trans_mat(ladders, snakes, board_size, dice_sides, prob);

//    print_pairs(ladders);
//    print_pairs(snakes);
    pb.print_matrix(trans_mat);


    // First roll will always start off the board
    vector<float > col;
    col.resize(trans_mat.size());
    for (int i = 0; i < trans_mat.size(); i++)
        col[i] = 0;
    col[0] = 1;

    prob_dist = pb.simulate_rolls(col, trans_mat);

    pb.print_matrix(prob_dist);



    return 0;
}

