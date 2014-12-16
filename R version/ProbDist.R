library(Rcpp)
library(microbenchmark)
library(algs)

pairs_to_mat<-function(str){
  pairs<- unlist(strsplit(str, " "))
  pair<- strsplit(pairs,",")
  first<-do.call( rbind, pair)[,1]
  second<-do.call( rbind, pair)[,2]
  mat<-cbind(first,second)
  return(mat)
}

fill_trans_mat<-function(ladders,snakes,board_size, prob){
  trans_mat<-matrix(0.0,nrow=board_size+1,ncol=board_size+1)
  rownames(trans_mat) = 0:board_size
  colnames(trans_mat) = 0:board_size
  # Create transition matrix
  for(x in 1:(board_size+1)){
    for(face in 1:(dice_sides)){
      if(x+face < board_size+1){
        if( (x+face-1) %in% ladders[,1]){
          trans_mat[x,(strtoi(ladders[match((x+face-1), ladders[,1]),2])+1)] <- (trans_mat[x,(strtoi(ladders[match((x+face-1), ladders[,1]),2])+1)] + prob)
        }
        else  if( (x+face-1) %in% snakes[,1]){
          trans_mat[x,(strtoi(snakes[match((x+face-1), snakes[,1]),2])+1)] <- (trans_mat[x,(strtoi(snakes[match((x+face-1), snakes[,1]),2])+1)] + prob)
        }
        else{
          trans_mat[x,x+face]<-trans_mat[x,x+face] + prob
        }
      }
      else
        trans_mat[x,board_size+1]<-trans_mat[x,board_size+1] + prob
    }
  }
  return (trans_mat)
}

find_prob_dist<-function(initial,trans_mat,board_size){
  prob_dist<-matrix(0.0,nrow=board_size+1,ncol=board_size+1)
  rownames(prob_dist) = 0:board_size
  colnames(prob_dist) = 0:board_size

  # Simulate experiments
  for(count in 1:(board_size+1)){
    if(count == 1){
      prob_dist[1,] <- as.matrix(col) %*% trans_mat
    }
    else{
      temp <- prob_dist[(count-1),] %*% trans_mat
      prob_dist[count,] = temp
    }
  }
  return (prob_dist)
}


board_size<-10
dice_sides<-3
prob<-(1.0 / dice_sides)
ladders_input<-"5,6"
snakes_input<-"4,3 8,7"
ladders<-pairs_to_mat(ladders_input)
snakes<-pairs_to_mat(snakes_input)
trans_mat<-fill_trans_mat(ladders,snakes,board_size,prob)

# First roll will always be off the board 
col<-matrix(0,1,(board_size+1))
col[1,1] = 1

prob_dist<-find_prob_dist(col,trans_mat,board_size)
prob_dist_cpp<-find_prob_dist_cpp(col,trans_mat)

microbenchmark(
find_prob_dist(col,trans_mat,board_size),
find_prob_dist_cpp(col,trans_mat)
)






