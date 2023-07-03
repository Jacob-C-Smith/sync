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
    mutex     m = { 0 };
    semaphore s = { 0 };

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