#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix mat_mult_cpp(NumericMatrix a, NumericMatrix b) {
  int row = a.nrow();
  int col = b.ncol();
  int inner = a.ncol();
  
  NumericMatrix ab(row,col);
  //mat_mult_cpp(col,trans_mat)
  
  
  for (int x = 0; x < row; x++) {
    for (int y = 0; y < col; y++) {
      for (int z = 0; z < inner; z++) {
        ab(x,y) += (a(x,z) * b(z,y));
      }
    }
  }
  return ab;
}
// [[Rcpp::export]]
NumericMatrix  find_prob_dist_cpp(NumericMatrix init, NumericMatrix trans_mat) {
  NumericMatrix temp;
  NumericMatrix output(trans_mat.nrow(), trans_mat.ncol());
  NumericMatrix temp_vec(1,trans_mat.ncol());
  //    simulate_rolls(col,trans_mat)
  
  for (int i = 0; i < trans_mat.nrow(); i++) {
    if (i == 0) {
      temp = mat_mult_cpp(init, trans_mat);
      output(0,_) = temp(0,_);
    } 
    else {
      temp_vec(0,_) = output((i-1),_);
      temp = mat_mult_cpp(temp_vec, trans_mat);
      output(i,_) = temp(0,_);
    }
  }
  
  
  return output;
}

