/** !
 * Example sync program
 * 
 * @file main.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sync 
#include <sync/sync.h>

// Preprocessor definitions
#define NTH_FIBONACCI_NUMBER 1000000000

// Forward declarations
/** !
 * Timer example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int sync_timer_example ( int argc, const char *argv[] );

/** !
 * Mutex example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int sync_mutex_example ( int argc, const char *argv[] );

/** !
 * Semaphone example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int sync_semaphore_example ( int argc, const char *argv[] );

/** !
 * Monitor example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int sync_monitor_example ( int argc, const char *argv[] );

// Entry point
int main ( int argc, const char *argv[] )
{

    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    mutex m  = { 0 };

    // Run the timer example program
    if ( sync_timer_example(argc, argv) == 0 ) goto failed_to_run_sync_example;

    // Run the mutex example program
    if ( sync_mutex_example(argc, argv) == 0 ) goto failed_to_run_mutex_example;

    // Run the semaphore example program
    #ifdef BUILD_SYNC_WITH_SEMAPHORE
        if ( sync_semaphore_example(argc, argv) == 0 ) goto failed_to_run_semaphore_example;
    #endif

    // Run the monitor example program
    #ifdef BUILD_SYNC_WITH_MONITOR
        if ( sync_monitor_example(argc, argv) == 0 ) goto failed_to_run_monitor_example;
    #endif
    
    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        failed_to_run_sync_example:

            // Write an error message to standard out
            printf("Failed to run timer example!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_mutex_example:

            // Write an error message to standard out
            printf("Failed to run mutex example!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_semaphore_example:

            // Write an error message to standard out
            printf("Failed to run semaphore example!\n");

            // Error
            return EXIT_FAILURE;
        
        failed_to_run_monitor_example:

            // Write an error message to standard out
            printf("Failed to run monitor example!\n");

            // Error
            return EXIT_FAILURE;
    }
}

int sync_timer_example ( int argc, const char *argv[] )
{

    // Initialized data
    size_t    c   = 0,
              d   = 1;
    double    sec = 0;
    timestamp t1  = 0, 
              t2  = 0,
              td  = 0;

    // Initialize the timer
    timer_init();

    // Record a timestamp
    t1 = timer_high_precision();

    // Iteratively calculate fib(NTH_FIBONACCI_NUMBER) 
    for (size_t i = 0; i < NTH_FIBONACCI_NUMBER; i++)
    {

        // Initialized data
        size_t e = c + d;

        // Iteration
        c = d, d = e;
    }
    
    // Record another timestamp
    t2 = timer_high_precision();

    // Compute the difference
    td = t2 - t1;

    // Convert the difference to seconds
    sec = (double) td / (double) ( timer_seconds_divisor() );

    // Print the time difference in seconds
    (void)printf("%zu\r[sync] [timer] It took %lf seconds to calculate fib(%d)\n", d, sec, NTH_FIBONACCI_NUMBER);

    // Success
    return 1;
}

int sync_mutex_example ( int argc, const char *argv[] )
{

    // Initialized data
    mutex m = { 0 };

    // Create
    if ( mutex_create(&m) == 0 ) return EXIT_FAILURE;

    // Lock
    (void) mutex_lock(m);

    // ... (Pretend) critical section ...
    printf("[sync] [mutex] This message was printed from a critical section\n");

    // Unlock
    (void) mutex_unlock(m);

    // Destroy
    (void) mutex_destroy(&m);

    // Success
    return 1;
}

int sync_semaphore_example ( int argc, const char *argv[] )
{

    // Initialized data
    semaphore s = { 0 };
    
    // Create
    if ( semaphore_create(&s, 1) == 0 ) return EXIT_FAILURE;
    
    // Wait
    (void) semaphore_wait(s);

    // ... (Pretend) critical section ...
    printf("[sync] [semaphore] This message was printed from a critical section\n");

    // Signal
    (void) semaphore_signal(s);

    // Destroy
    (void) semaphore_destroy(&s);

    // Success
    return 1;
}

int sync_monitor_example ( int argc, const char *argv[] )
{

    // Initialized data
    monitor m = { 0 };
    
    // Create
    if ( monitor_create(&m) == 0 ) return EXIT_FAILURE;

    // ... (Pretend) critical section ...
    printf("[sync] [monitor] TODO\n");

    // Destroy
    (void) monitor_destroy(&m);

    // Success
    return 1;
}
