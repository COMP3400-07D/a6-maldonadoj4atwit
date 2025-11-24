#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/**
 * 
 * main function for CPU scheduler simulator.
 * 
 * supports two scheduling algorithms: FCFS and Round-Robin (RR).
 * 
 * program prints the algorithm used, each accepted process and its CPU burst
 * and the average wait times across all processes
 * 
 * Returns 0 on success and 1 on error
 * 
 */

int main(int argc, char* argv[]) {
    //checks if algorithm name is provided
     if ( argc < 2 ) {
        fprintf( stderr, "ERROR: Missing arguments\n" ) ;
        return 1 ;
    }
    //first arg determines the scheduling algorithm
    if ( strcmp( argv[ 1 ], "fcfs" ) == 0 ) {
        if ( argc < 3 ) { 
            fprintf( stderr, "ERROR: Missing arguments\n" ) ;
            return 1 ;
        }

        int plen = argc - 2 ;
        int* bursts = malloc( sizeof( int ) * plen ) ;
        for ( int i = 0 ; i < plen ; i++ ) {
            bursts[ i ] = atoi( argv[ i + 2 ] ) ;
        }

        //initializes PCB array
        struct pcb* procs = init_procs( bursts, plen ) ;
        printf( "Using FCFS\n\n" ) ;

        //prints accepted processe
        for ( int i = 0 ; i < plen ; i++ ) {
            printf( "Accepted P%d: Burst %d\n", i, bursts[ i ] ) ;
        }

        //runs FCFS scheduler
        fcfs_run( procs, plen ) ;

        //computes total wait and average wait times
        int total_wait = 0 ;
        for ( int i = 0 ; i < plen ; i++ ) {
            total_wait += procs[ i ].wait ;
        }

        printf( "Average wait time: %.2f\n", ( double )total_wait / plen ) ;

        free( bursts ) ;
        free( procs ) ;

    } 
    else if ( strcmp( argv[ 1 ], "rr" ) == 0 ) {
        if ( argc < 4 ) { 
            fprintf( stderr, "ERROR: Missing arguments\n" ) ;
            return 1 ;
        }

        //time quantum
        int quantum = atoi( argv[ 2 ] ) ;
        //number of processes
        int plen = argc - 3 ;
        int* bursts = malloc( sizeof( int ) * plen ) ;

        //parses CPU burst times from command-line arguments
        for ( int i = 0 ; i < plen ; i++ ) {
            bursts[ i ] = atoi( argv[ i + 3 ] ) ;
        }

        //initializes PCB array
        struct pcb* procs = init_procs( bursts, plen ) ;
        printf( "Using RR(%d)\n\n", quantum ) ;

        //prints accepted processes
        for ( int i = 0 ; i < plen ; i++ ) {
            printf( "Accepted P%d: Burst %d\n", i, bursts[ i ] ) ;
        }

        //runs Round-Robin scheduler
        rr_run( procs, plen, quantum ) ;

        //computes total wait and average wait times
        int total_wait = 0 ;
        for ( int i = 0 ; i < plen ; i++ ) {
            total_wait += procs[ i ].wait ;
        }

        printf( "Average wait time: %.2f\n", ( double )total_wait / plen ) ;

        free( bursts ) ;
        free( procs ) ;

    } 
    else {
        fprintf( stderr, "ERROR: Unknown algorithm\n" ) ;
        return 1 ;
    }

    return 0 ;
}
