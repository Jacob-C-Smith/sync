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
#include <stdbool.h>

// sync 
#include <sync/sync.h>

// Preprocessor definitions
#define NTH_FIBONACCI_NUMBER 1000000000

// Enumeration definitions
enum sync_examples_e
{
    SYNC_TIMER_EXAMPLE     = 0,
    SYNC_MUTEX_EXAMPLE     = 1,
    SYNC_SEMAPHORE_EXAMPLE = 2,
    SYNC_MONITOR_EXAMPLE   = 3,
    SYNC_EXAMPLE_QUANTITY  = 4
};

// Forward declarations
/** !
 * Print a usage message to standard out
 * 
 * @param argv0 the name of the program
 * 
 * @return void
 */
void print_usage ( const char *argv0 );

/** !
 * Parse command line arguments
 * 
 * @param argc            the argc parameter of the entry point
 * @param argv            the argv parameter of the entry point
 * @param examples_to_run return
 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run );

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
    bool examples_to_run[SYNC_EXAMPLE_QUANTITY] = { 0 };

    // Parse command line arguments
    parse_command_line_arguments(argc, argv, examples_to_run);

    // Formatting
    printf(
        "╭──────────────╮\n"\
        "│ sync example │\n"\
        "╰──────────────╯\n"\
        "The sync library provides cross platform synchronization primitives and high-precision timing\n"\
        "Sync provides %d abstractions. The timer, the mutex, the semaphore, and the monitor.\n\n"\
        "A timer is used to collect high percision timestsamps.\n"\
        "A mutex is the most basic synchronization primitive. It provides mutual exclusion to code.\n"\
        "A semaphore is an abstraction for controlling access to a resource.\n"\
        "A monitor is an abstraction for blocking and signaling threads in a critical section.\n\n",
        SYNC_EXAMPLE_QUANTITY
    );

    //////////////////////
    // Run the examples //
    //////////////////////

    // Run the thread example program
    if ( examples_to_run[SYNC_TIMER_EXAMPLE] )

        // Error check
        if ( sync_timer_example(argc, argv) == 0 ) goto failed_to_run_timer_example;
    
    // Run the mutex example program
    if ( examples_to_run[SYNC_MUTEX_EXAMPLE] )

        // Error check
        if ( sync_mutex_example(argc, argv) == 0 ) goto failed_to_run_mutex_example;
    
    // Run the semaphore example program
    if ( examples_to_run[SYNC_SEMAPHORE_EXAMPLE] )

        // Error check
        if ( sync_semaphore_example(argc, argv) == 0 ) goto failed_to_run_semaphore_example;
    
    // Run the monitor example program
    if ( examples_to_run[SYNC_MONITOR_EXAMPLE] )

        // Error check
        if ( sync_monitor_example(argc, argv) == 0 ) goto failed_to_run_monitor_example;

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        failed_to_run_timer_example:

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


void print_usage ( const char *argv0 )
{

    // Argument check
    if ( argv0 == (void *) 0 ) exit(EXIT_FAILURE);

    // Print a usage message to standard out
    printf("Usage: %s [timer] [mutex] [semaphore] [monitor]\n", argv0);

    // Done
    return;
}

void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run )
{

    // If no command line arguments are supplied, run all the examples
    if ( argc == 1 ) goto all_examples;

    // Error check
    if ( argc > SYNC_EXAMPLE_QUANTITY + 1 ) goto invalid_arguments;

    // Iterate through each command line argument
    for (size_t i = 1; i < argc; i++)
    {
        
        // Timer example?
        if ( strcmp(argv[i], "timer") == 0 )

            // Set the thread example flag
            examples_to_run[SYNC_TIMER_EXAMPLE] = true;

        // Mutex example?
        else if ( strcmp(argv[i], "mutex") == 0 )
            
            // Set the thread pool example flag
            examples_to_run[SYNC_MUTEX_EXAMPLE] = true;

        // Semaphore example?
        else if ( strcmp(argv[i], "semaphore") == 0 )

            // Set the schedule example flag
            examples_to_run[SYNC_SEMAPHORE_EXAMPLE] = true;
        
        // Monitor example?
        else if ( strcmp(argv[i], "monitor") == 0 )

            // Set the schedule example flag
            examples_to_run[SYNC_MONITOR_EXAMPLE] = true;

        // Default
        else goto invalid_arguments;
    }
    
    // Success
    return;

    // Set each example flag
    all_examples:
    {

        // For each example ...
        for (size_t i = 0; i < SYNC_EXAMPLE_QUANTITY; i++)
        
            // ... set the example flag
            examples_to_run[i] = true;
        
        // Success
        return;
    }

    // Error handling
    {

        // Argument errors
        {
            invalid_arguments:
                
                // Print a usage message to standard out
                print_usage(argv[0]);

                // Abort
                exit(EXIT_FAILURE);
        }
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

    // Formatting
    printf(
        "╭───────────────╮\n"\
        "│ timer example │\n"\
        "╰───────────────╯\n"\
        "In this example, the timer is initialized. The program samples a timestamp t0,\n"\
        "computes the 1,000,000,000th fibonacci number, and samples another timestamp t1.\n"\
        "The difference of the timestamps (t1 - t0) is printed to standard out.\n\n"
    );

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

    // Format
    putchar('\n');

    // Success
    return 1;
}

int sync_mutex_example ( int argc, const char *argv[] )
{

    // Initialized data
    mutex m = { 0 };

    // Formatting
    printf(
        "╭───────────────╮\n"\
        "│ mutex example │\n"\
        "╰───────────────╯\n"\
        "In this example, a mutex is created and locked. The program does a pretend\n"\
        "critical section, then the mutex is unlocked. Finally, the mutex is destroyed\n\n"
    );

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

    // Format
    putchar('\n');

    // Success
    return 1;
}

int sync_semaphore_example ( int argc, const char *argv[] )
{

    // Initialized data
    semaphore s = { 0 };
    
    // Formatting
    printf(
        "╭───────────────────╮\n"\
        "│ semaphore example │\n"\
        "╰───────────────────╯\n"\
        "In this example, a semaphore is created and locked. The program does a pretend\n"\
        "critical section, then the semaphore is unlocked. Finally, the semaphore is destroyed\n\n"
    );

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

    // Format
    putchar('\n');

    // Success
    return 1;
}

int sync_monitor_example ( int argc, const char *argv[] )
{

    // Initialized data
    monitor m = { 0 };
    
    // Formatting
    printf(
        "╭─────────────────╮\n"\
        "│ monitor example │\n"\
        "╰─────────────────╯\n"\
        "TODO\n\n"
    );

    // Create
    if ( monitor_create(&m) == 0 ) return EXIT_FAILURE;

    // ... (Pretend) critical section ...
    printf("[sync] [monitor] TODO\n");

    // Destroy
    (void) monitor_destroy(&m);

    // Format
    putchar('\n');
    
    // Success
    return 1;
}
