// File: a1.hpp
// Sourav
// Bihani
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A1_HPP
#define A1_HPP

#include <vector>
#include <mpi.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <random>
#include <bits/stdc++.h>
#include <algorithm> 
using namespace std;
// IMPLEMENT ME!
template <typename T, typename Pred>
void mpi_extract_if(MPI_Comm comm, const std::vector<T>& in, std::vector<T>& out, Pred pred) {
  
  
  int rank,size;
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);
  int mycount =0 ;
  int sz = in.size();
  vector<int> temp;
  vector<T> vec_op;
  vector<int> random_num;
  vector<int> store;
  vector<int> temp_store;
  vector<int> storex;
  vector<int> global_store;
  vector<int> vec_op1;
  vector<int> sdispls;
  vector<int> rdispls;
  
  temp.resize(sz);
  for(int i=0;i<in.size();i++)
  {
  	if(pred(in[i]))
  	temp[i]=1;
  	else
  	temp[i]=0;
  }
  mycount = count(temp.begin(),temp.end(),1);
  vec_op.resize(mycount);
  int j=0;
  for(int i=0;i<sz;i++)
  {
  	if(temp[i])
  	{
  		vec_op[j]=in[i];
  	    j++; 
	} 	
  }
  
  random_num.resize(mycount);
  random_device rand_dev;
  mt19937 generator(rand_dev());
  uniform_int_distribution<int> distr(0, size - 1);

  for(int i=0;i<mycount;i++)
  {
  	random_num[i]=distr(generator) ;
  }
   store.resize(size);
 
  for(int i=0;i<size;i++)
  {
  	store[i]=count (random_num.begin(), random_num.end(), i);
  } 
  storex.resize(size);
  MPI_Alltoall(&store[0],1,MPI_INT,&storex[0],1,MPI_INT,comm);
  
  int sum=0;
  for(int i=0;i<size;i++)
  {
  	sum=sum+storex[i];
  }
    out.resize(sum);
 
    sdispls.resize(size);
    rdispls.resize(size);
    int sum1 = 0;
    int sumx = 0;
    for(int i = 0 ; i < size ; i++) 
    {
    	sdispls[i] = sum1;
        sum1 += store[i];
    }
 
    vec_op1.resize(mycount);
    temp_store.resize(size);
    temp_store=sdispls;     

    for(int i=0;i<mycount;i++)
    {
     	vec_op1[temp_store[random_num[i]]]=vec_op[i];
	    temp_store[random_num[i]]++;
    }	
    
        for(int i = 0 ; i < size ; i++)
    {
    	rdispls[i] = sumx;
        sumx += storex[i];
    } 
	

     MPI_Alltoallv(&vec_op1[0],&store[0],&sdispls[0], MPI_INT, &out[0],&storex[0],&rdispls[0],MPI_INT,comm);
  
    
  
  
	
  	
     
    
  
  

} // mpi_extract_if

#endif // A1_HPP
