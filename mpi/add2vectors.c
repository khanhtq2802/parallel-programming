// #include <mpi.h>
// #include <stdio.h>

// int main(int argc, char** argv) 
// {
//     int N = 10;
//     int A[N], B[N], C[N];
//     for(int i = 0; i < N; i++){
//         A[i] = i;
//         B[i] = 2*i;
//     }
//     MPI_Init(&argc, &argv);
//     // Find out rank, size
//     int world_rank;
//     MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//     int world_size;
//     MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
//     int domain_size = N / world_size;
//     int start = world_rank*domain_size;
//     int end = (world_rank+1)*domain_size;

//     if(world_rank != world_size - 1){
//         for(int i = start; i < end; i++){
//             C[i] = A[i] + B[i];
//         }
//     } else{
//         for(int i = start; i < N ; i++){
//             C[i] = A[i] + B[i];
//         }
//     }
//     MPI_Finalize();

//     for(int i = 0; i<N; i++){
//         printf("%d ", C[i]);
//     }
// }


#include <stdio.h>
#include <mpi.h>
#include <malloc.h>
int main(int argc, char *argv[]){
  int N = 12,NP,RANK;
  MPI_Init (&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD,&NP);
  MPI_Comm_rank(MPI_COMM_WORLD,&RANK);
  MPI_Status Warning;
  int i,p;
  int *A,*B,*C; 
  A = (int *) malloc (N*sizeof(int));
  B = (int *) malloc (N*sizeof(int));
  C = (int *) malloc (N*sizeof(int));
  // Innitialize Input Data
  if (RANK==0)
    for (i=0;i<N;i++) {*(A+i) = i; *(B+i) = 2*i;}
  // Domain Decomposition
  int Ns = N/NP;
  int *As,*Bs,*Cs;
  As = (int *) malloc (Ns*sizeof(int));
  Bs = (int *) malloc (Ns*sizeof(int));
  Cs = (int *) malloc (Ns*sizeof(int));
  // Distribute Input Data
  if (RANK==0){
    //Assign first subdomain for RANK 0
    for (i=0;i<Ns;i++) { *(As+i) = *(A+i); *(Bs+i) = *(B+i);}
    //Send each part of A and B to correct other RANK
    for (p=1;p<NP;p++){
       MPI_Send(A+p*Ns,Ns,MPI_INT,p,p,MPI_COMM_WORLD);
       MPI_Send(B+p*Ns,Ns,MPI_INT,p,1000+p,MPI_COMM_WORLD);}
  } else {
    //Receive correct part of A and B from RANK 0
         MPI_Recv(As,Ns,MPI_INT,0,RANK,MPI_COMM_WORLD,&Warning);
         MPI_Recv(Bs,Ns,MPI_INT,0,1000+RANK,
                                       MPI_COMM_WORLD,&Warning);
   }
   // Calculation
   for (i=0;i<Ns;i++) *(Cs+i) = *(As+i) + *(Bs+i);
   // Gather Output
   if (RANK!=0){
    	//Send to RANK 0
    	MPI_Send(Cs,Ns,MPI_INT,0,2000+RANK,MPI_COMM_WORLD);
   } else {
    	//Assign first domain
    	for (i=0;i<Ns;i++) *(C+i) = *(Cs+i);
    	//Receive subdomain from other RANK and store correctly
    	for (p=1;p<NP;p++)
    	  MPI_Recv(C+p*Ns,Ns,MPI_INT,p,2000+p,
    	                         MPI_COMM_WORLD,&Warning);
    	for (i=0;i<N;i++) printf("%d ", *(C+i));
    	
   }
  MPI_Finalize();
  return 0;
}