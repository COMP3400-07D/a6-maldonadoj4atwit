#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * 
 * initializes processes based on CPU bursts
 * allocates an array of PCBs on the heap
 * each PCB has a PID, burst_left, and wait initialized
 * 
 */

struct pcb* init_procs(int* bursts, int blen) {
    struct pcb* procs = malloc( sizeof( struct pcb ) * blen ) ;
    for ( int i = 0 ; i < blen ; i++ ) {
        procs[ i ].pid = i ;
        procs[ i ].burst_left = bursts[ i ] ;
        procs[ i ].wait = 0 ;
    }

    return procs ;
}

/**
 * 
 * prints all PCB information.
 * 
 */
void printall(struct pcb* procs, int plen) {
    for ( int i = 0 ; i < plen ; i++ ) {
        printf( "PID %d: Burst Left %d, Wait %d\n", procs[ i ].pid, procs[ i ].burst_left, procs[ i ].wait ) ;
    }
}

/**
 * 
 * run the current process by amount time units
 * reduces burst_left of current process
 * increases wait time for all other unfinished processes
 * 
 */

void run_proc(struct pcb* procs, int plen, int current, int amount) {
    procs[ current ].burst_left -= amount ;
    for ( int i = 0 ; i < plen ; i++ ) {
        if ( i != current && procs[ i ].burst_left > 0 ) {
            procs[ i ].wait += amount ;
        }
    }
}

/**
 * 
 * first-Come-first-serve scheduling
 * runs each process in order until completion
 * returns total time elapsed
 * 
 */

int fcfs_run(struct pcb* procs, int plen) {
    int time = 0 ;

    for ( int i = 0 ; i < plen ; i++ ) {
        int burst = procs[ i ].burst_left ;
        run_proc( procs, plen, i, burst ) ;
        time += burst ;
    }

    return time ;
}

/**
 * 
 * find the next process to run for Round-Robin scheduling
 * loops after the current index
 * returns -1 if all processes are finished
 * 
 */

int rr_next(int current, struct pcb* procs, int plen) {
    for ( int i = 1 ; i <= plen ; i++ ) {
        int idx = ( current + i ) % plen ;
        if ( procs[ idx ].burst_left > 0 ) {
            return idx ;
        }
    }

    return -1 ;
}

/**
 * 
 * round Robin scheduling
 * runs each process up to quantum time units
 * returns total time elapsed
 * 
 */

int rr_run(struct pcb* procs, int plen, int quantum) {
     int time = 0;
    int current = -1; // Start before the first index

    while ( 1 ) {
        current = rr_next( current, procs, plen );
        if ( current == -1 ) {
            break;
        }
        int amount = ( procs[ current ].burst_left < quantum ) ? procs[ current ].burst_left : quantum ;
        run_proc( procs, plen, current, amount ) ;
        time += amount ;
    }

    return time ;
}

