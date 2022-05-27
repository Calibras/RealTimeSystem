#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct timespec diff_time(struct timespec *start, struct timespec *end) {
	// calculate: dt = start - end
	struct timespec dt;
	if(end->tv_nsec > start->tv_nsec){
	    //"normal Rechnen"
	    dt.tv_sec = (end->tv_sec - start->tv_sec);
	    dt.tv_nsec = end->tv_nsec - start->tv_nsec;
	}
	else if(end->tv_nsec < start->tv_nsec){
	    dt.tv_sec = (end->tv_sec - start->tv_sec) - 1;
	    dt.tv_nsec = -1* (1e-9 - (start->tv_nsec - end->tv_nsec));
	}
	
	return dt;
}

  //  Do not change the function myfunc1 !
int myfunc1 (int in){
    int i, j = in;
    for(i=0; i <= 999; i++) j=j+i;
    return j;
}

  //  Do not change the function myfunc2 !
int myfunc2 (int in){
    int val1, i;
    float val2, val3;
    for (i =0; i < 4500; i++)
    {
        val1 = in*in*i;
        val2 = (in+i) * (in+i) * (in+i);
        val3 = val2 / val1;
    }
    return val3;
}

 // Do 500000 function calls and print the time results.
 // use the first parameter of argv as the probability for calling myfunc1

int main ( int argc , char ** argv ){
    int i, randomValue;
	// time stamps before and after the loop 
    struct timespec t_Start, t_End;
	//  variable for the execution time	
	struct timespec dt_exec; 
    // handle probability argument argv
    int randModifier = argv[1];;
    // get the time stamp for the start time t_Start
	clock_gettime(CLOCK_REALTIME, &t_Start);
	
    for (i = 0; i < 5e5; i++){ //  e stands for exponent. 5e5 = 5 * 10^5 = 500000
        randomValue = rand();
        if (((randomValue % 100) + 1) <= randModifier)
            myfunc1(randomValue);
        else
            myfunc2(randomValue-1234);
    }

    // get the time stamp for the completion time t_Compl
	clock_gettime(CLOCK_REALTIME, &t_End);
	
	// calculate the execution time dt_exec
    dt_exec = diff_time(&t_Start, &t_End);

	// print the results
    printf("Start-time      : %11ld s %9ld \n", t_Start.tv_sec,t_Start.tv_nsec);
    printf("Completion-time : %11ld s %9ld \n", t_End.tv_sec,t_End.tv_nsec);
    printf("Execution-time  : %11ld s %9ld \n", dt_exec.tv_sec,dt_exec.tv_nsec);
    return 0;
}
