#ifndef ProbDist_H
#define	ProbDist_H
#include<vector>
class ProbDist{
    
public:
    std::vector<std::vector<float> > mat_mult(std::vector<std::vector<float> > a, std::vector<std::vector<float> > b); 
    std::vector<std::vector<float> > vec_to_mat(std::vector<float > v);
    std::vector<std::vector<float> > simulate_rolls(std::vector<float > init, std::vector<std::vector<float> > trans_mat);
    void print_matrix(std::vector<std::vector<float> > m);
};


#endif	

