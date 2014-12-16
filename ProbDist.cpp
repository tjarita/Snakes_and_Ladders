#include "ProbDist.h"
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <iomanip>  
#include <iostream>

using namespace std;

vector<vector<float> > ProbDist::mat_mult(vector<vector<float> > a, vector<vector<float> > b) {
    vector<vector<float> > ab;

    int row = a.size();
    int col = b[0].size();
    int inner;
    if (a[0].size() == b.size())
        inner = a[0].size();


    ab.resize(row);
    for (int x = 0; x < row; x++) {
        ab[x].resize(col);
        for (int y = 0; y < col; y++) {
            for (int z = 0; z < inner; z++) {
                ab[x][y] += a[x][z] * b[z][y];
            }
        }
    }
    return ab;
}

vector<vector<float> > ProbDist::vec_to_mat(vector<float> v) {
    vector<vector<float> > m;

    m.resize(1);
    m[0].resize(v.size());
    for (int i = 0; i < v.size(); i++) {
        m[0] = v;
        //        cout << m[0][i] << " ";
    }
    //    cout << endl;

    return m;
}

vector<vector<float> >  ProbDist::simulate_rolls(vector<float > init, vector<vector<float> > trans_mat) {
    vector<vector<float> > prob_dist;

    prob_dist.resize(trans_mat.size());
    for (int i = 0; i < trans_mat.size(); i++) {
        vector< vector<float> > temp;
        if (i == 0) {
            temp = mat_mult(vec_to_mat(init), trans_mat);
            prob_dist[0] = temp[0];
        } else {

            temp = mat_mult(vec_to_mat(prob_dist[i - 1]), trans_mat);
            prob_dist[i] = temp[0];
        }
    }
    return prob_dist;
}

void ProbDist::print_matrix(vector<vector<float> > m) {
    for (float i = 0.0; i < m[0].size(); i++)
        cout << fixed << setprecision(2) << i << " ";
    cout << endl << endl;


    for (int x = 0; x < m.size(); x++) {
        for (int y = 0; y < m[0].size(); y++) {
            cout << fixed << setprecision(2) << m[x][y] << " ";
        }
        cout << endl;
    }
    cout << endl;
}