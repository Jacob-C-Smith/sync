// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sync submodule
#include <sync/sync.h>

// Entry point
int main ( int argc, const char *argv[] )
{

    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    mutex     m  = { 0 };
    
    timestamp t1 = 0, 
              t2 = 0,
              td = 0;

    // Timer
    {
        
        // Initialized data
        double sec = 0;

        // Initialize the timer
        timer_init();

        // Record a timestamp
        t1 = timer_high_precision();

        // Iterate 1,000,000,000 times, accumulating a bogus variable
        for (size_t i = 0; i < 1000000000; i++);
        
        // Record another timestamp
        t2 = timer_high_precision();

        // Compute the difference
        td = t2 - t1;

        // Convert the difference to seconds
        sec = (double) td / (double) ( timer_seconds_divisor() );

        // Print the time difference in seconds
        (void)printf("%lf seconds\n", sec);
    }

    // Mutex
    {

        // Create
        if ( mutex_create(&m) == 0 )

            // Error
            return EXIT_FAILURE;

        // Lock
        (void) mutex_lock(m);

        // ... Critical section ...

        // Unlock
        (void) mutex_unlock(m);

        // Destroy
        (void) mutex_destroy(&m);
    }

    // Semaphore
    #ifdef BUILD_SYNC_WITH_SEMAPHORE
    {
        
        // Initialized data
        semaphore s  = { 0 };
        
        // Create
        if ( semaphore_create(&s, 10) == 0 )

            // Erorr
            return 0;
        
        // Wait
        (void) semaphore_wait(s);

        // Signal
        (void) semaphore_signal(s);

        // Destroy
        (void) semaphore_destroy(&s);
    }
    #endif

    // Success
    return EXIT_SUCCESS;
}
