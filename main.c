// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sync
#include <sync/sync.h>

// Entry point
int main()
{

    // Initialized data
    mutex     m  = { 0 };
    semaphore s  = { 0 };
    timestamp t1 = 0, 
              t2 = 0,
              td = 0;

    // Timer
    {
        
        // Initialized data
        size_t N = 0;
        double s = 0;

        // Initialize the timer
        timer_init();

        // Record a timestamp
        t1 = timer_high_precision();

        // Iterate 1,000,000,000 times, accumulating a bogus variable
        for (size_t i = 0; i < 1,000,000,000; i++)
            N += i;
        
        // Record another timestamp
        t2 = timer_high_precision();

        // Compute the difference
        td = t2 - t1;

        // Convert the difference to seconds
        s = (double) td / (double) timer_seconds_divisor();

        // Print the time difference in seconds
        printf("%f\n", s);
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
    {

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

    // Success
    return EXIT_SUCCESS;
}