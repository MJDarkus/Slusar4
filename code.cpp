#include  "mpi.h"
#include  <ctime>
#include  <cstdlib>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv){
int rank, size, m, n, i, j, k, l;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

int r=atoi(argv[1]);
m=r * size;
n=m * 2;
int array[m][n];

ifstream f;
for(i=0; i<m; i++){
	f.open("file" + to_string(i) + ".in", std::ifstream::in);
	for(j=0; j<n; j++){
		f>>array[i][j];
	}
	f.close();
}
MPI_Barrier(MPI_COMM_WORLD);
for (i=0; i<m; i++) {
	for (j=0; j<n; j++){
		if (!rank) cout << array[i][j] << "\t";
	}
	if(!rank) cout <<endl;
}
int local_max;
int temp_max=0;
for (k=0; k<size; k++, l=0){
  if (k==rank){
    for(int c=0; c<r; c++){
      for(l=0; l<n; l++)
        if (array[r*k+c][0] <array[r*k+c][l])
	 array[r*k+c][0]=array[r*k+c][l];
        if (local_max<array[r*k+c][0] )
          local_max=array[r*k+c][0];
      }
    }
}
int full_max=0;
MPI_Reduce(&local_max, &full_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD) ;

if (full_max){
	cout <<"-------------------- \nMax is "<< full_max << endl << "--------------------\n";
}
MPI_Finalize();
return EXIT_SUCCESS;
}
