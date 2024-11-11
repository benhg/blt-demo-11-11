#include <stdio.h>
#include <mpi.h>

/**
 * For an explaination of the math behind this approximation, see
 * https://crypto.stanford.edu/pbc/notes/pi/code.html
 */

// These must be global since they need to be sent by the signal handler.
int c = 0,d = 0,i = 0;
int r[res_size + 1];
uint64_t tot = 0;

int main(int argc, char* argv[]) {
	int numprocs;
	int myid;
	init_signals();

	
	MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    // TODO: Set a target size
    int res_size = 2880;

    // This must divide evenly. 2880/320 - 9
    int chunk_size = res_size / numprocs;
    int my_chunk_start = (myid) * chunk_size;
    int my_chunk_end = (myid + 1) * chunk_size;



    
    int k;
    int b;
    for (i = my_chunk_start; i < my_chunk_end; i++) {
		r[i] = 200;

    }
    r[i] = 0;

    for (k = res_size; k > 0; k -= 14) {
	d = 0;

	i = k;
	tot++;
	for (;;) {
	    d += r[i] * 10000;
	    b = 2 * i - 1;

	    r[i] = d % b;
	    d /= b;
	    i--;
	    if (i == 0) break;
	    d *= i;
	}
	printf("%.12d", c + d / 10000);
	c = d % 10000;
    }

    return 0;
}



/**
 * Signal handlers
 */

void init_signals(void){
    sigact.sa_handler = signal_handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGINT, &sigact, (struct sigaction *)NULL);
}

static void signal_handler(int sig){
    if (sig == SIGINT){ printf("Caught signal for Ctrl+C\n");}
    MPI_Finalize();
}

