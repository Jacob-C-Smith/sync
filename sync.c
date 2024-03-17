/** !
 * Cross platform synchronization primitives 
 * 
 * @file sync.c 
 * 
 * @author Jacob Smith
 */

// Header file 
#include <sync/sync.h>

// Static data
static signed SYNC_TIMER_DIVISOR = 0;
static const signed SEC_2_NS = 1000000000;

int mutex_create ( mutex *const p_mutex )
{

    // Argument check
    if ( p_mutex == (void *) 0 ) goto no_mutex;

    // Platform dependent implementation
    #ifdef _WIN64

        // Create a mutex
        *p_mutex = CreateMutex(0, FALSE, 0);

        // Return
        return ( *p_mutex != 0 );
    #else

        // Return
        return ( pthread_mutex_init(p_mutex, NULL) == 0 );
    #endif

    // Error handling
    {
        
        // Argument errors
        {
            no_mutex:
                #ifndef NDEBUG
                    printf("[sync] Null pointer provided for \"p_mutex\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

#ifdef BUILD_SYNC_WITH_SEMAPHORE
int semaphore_create ( semaphore *const p_semaphore, unsigned int count )
{

    // Argument check
    if ( p_semaphore == (void *) 0 ) goto no_semaphore;
    
    // Platform dependent implementation
    #ifdef _WIN64

        // Create a semaphore with the specified count
        *p_semaphore = CreateSemaphore(NULL, count, count, NULL);

        // Return
        return ( p_semaphore != 0 );
    #else

        // Return
        return ( sem_init(p_semaphore, 0, count) == 0 );
    #endif

    // Error handling
    {
        
        // Argument errors
        {
            no_semaphore:
                #ifndef NDEBUG
                    printf("[sync] Null pointer provided for \"p_semaphore\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
int monitor_create ( monitor *const p_monitor )
{
    // Argument check
    if ( p_monitor == (void *) 0 ) goto no_monitor;
    
    // Platform dependent implementation
    #ifdef _WIN64
        // TODO
        //

    #else

        // Return
        return ( pthread_cond_init(&p_monitor->_cond, NULL) == 0 ) && ( pthread_mutex_init(&p_monitor->_mutex, NULL) == 0 );
    #endif

    // Error handling
    {
        
        // Argument errors
        {
            no_monitor:
                #ifndef NDEBUG
                    printf("[sync] Null pointer provided for \"p_monitor\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
#endif

int mutex_lock ( mutex _mutex )
{

    // Platform dependent implementation
    #ifdef _WIN64

        // Platform dependent argument check
        if ( _mutex == INVALID_HANDLE_VALUE ) goto no_mutex;

        // Return
        return ( WaitForSingleObject(_mutex, INFINITE) == WAIT_FAILED ? 0 : 1 );
    #else

        // Return
        return ( pthread_mutex_lock(&_mutex) == 0 );
    #endif

    // Error handling
    {

        // Argument error
        {
            #ifdef _WIN64
                no_mutex:
                    #ifndef NDEBUG
                        printf("[sync] Invalid parameter provided for \"_mutex\" in call to function \"%s\"\n", __FUNCTION__);
                    #endif

                    // Error
                    return 0;
            #endif
        }
    }
}

#ifdef BUILD_SYNC_WITH_SEMAPHORE
int semaphore_wait ( semaphore _semaphore )
{

    // Platform dependent implementation
    #ifdef _WIN64
        
        // Platform dependent argument check
        if ( _semaphore == INVALID_HANDLE_VALUE ) goto no_semaphore;
        
        // Return
        return ( WaitForSingleObject(_semaphore, INFINITE) == WAIT_FAILED ? 0 : 1 );
    #else

        // Return
        return ( sem_wait(&_semaphore) == 0 );
    #endif

    // Error handling
    {

        // Argument error
        {
            #ifdef _WIN64
                no_semaphore:
                    #ifndef NDEBUG
                        printf("[sync] Invalid parameter provided for \"_semaphore\" in call to function \"%s\"\n", __FUNCTION__);
                    #endif

                    // Error
                    return 0;
            #endif
        }
    }
}
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
int monitor_wait ( monitor _monitor )
{

    // Platform dependent implementation
    #ifdef _WIN64
        
        // TODO
    #else

        // Return
        return ( pthread_cond_wait(&_monitor._cond, &_monitor._mutex) == 0 );
    #endif
}
#endif

int mutex_unlock ( mutex _mutex )
{

    // Platform dependent implementation
    #ifdef _WIN64
        // Platform dependent argument check
    if ( _mutex == INVALID_HANDLE_VALUE ) goto no_mutex;
        // Return
        return ReleaseMutex(_mutex);
    #else

        // Return
        return ( pthread_mutex_unlock(&_mutex) == 0 );
    #endif

    // Error handling
    {

        // Argument error
        {

            #ifdef _WIN64
                no_mutex:
                    #ifndef NDEBUG
                        printf("[sync] Invalid parameter provided for \"_mutex\" in call to function \"%s\"\n", __FUNCTION__);
                    #endif

                    // Error
                    return 0;
            #endif
        }
    }
}

#ifdef BUILD_SYNC_WITH_SEMAPHORE
int semaphore_signal ( semaphore _semaphore )
{

    // Platform dependent implementation
    #ifdef _WIN64

        // Platform dependent argument check
        if ( _semaphore == INVALID_HANDLE_VALUE ) goto no_semaphore;

        // Return
        return ( ReleaseSemaphore(_semaphore, 1, 0) );
    #else

        // Return
        return ( sem_post(&_semaphore) == 0 );
    #endif



    // Error handling
    {

        // Argument errors
        {
            #ifdef _WIN64
                no_semaphore:
                    #ifndef NDEBUG
                        printf("[sync] Invalid parameter provided for \"_semaphore\" in call to function \"%s\"\n", __FUNCTION__);
                    #endif

                    // Error
                    return 0;
            #endif
        }
    }
}
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
int monitor_notify ( monitor _monitor )
{

    // Platform dependent implementation
    #ifdef _WIN64
        
        // TODO
    #else

        // Return
        return ( pthread_cond_signal(&_monitor._cond) == 0 );
    #endif
}

int monitor_notify_all ( monitor _monitor )
{

    // Platform dependent implementation
    #ifdef _WIN64
        
        // TODO
    #else

        // Return
        return ( pthread_cond_broadcast(&_monitor._cond) == 0 );
    #endif
}
#endif

int mutex_destroy ( mutex *const p_mutex )
{

    // Argument check
    if ( p_mutex == (void *) 0 ) goto no_mutex;

    // Platform dependent implementation
    #ifdef _WIN64

        // Return
        return ( CloseHandle(*p_mutex) );
    #else

        // Return
        return ( pthread_mutex_destroy(p_mutex) == 0 );
    #endif

    // Error handling
    {
        
        // Argument errors
        {
            no_mutex:
                #ifndef NDEBUG
                    printf("[sync] Null pointer provided for \"p_mutex\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

#ifdef BUILD_SYNC_WITH_SEMAPHORE
int semaphore_destroy ( semaphore *const p_semaphore )
{

    // Argument check
    if ( p_semaphore == (void *) 0 ) goto no_semaphore;

    // Platform dependent implementation
    #ifdef _WIN64

        // Return
        return ( CloseHandle(*p_semaphore) );
    #else

        // Return
        return ( sem_destroy(p_semaphore) == 0 );
    #endif

    // Error handling
    {
        
        // Argument errors
        {
            no_semaphore:
                #ifndef NDEBUG
                    printf("[sync] Null pointer provided for \"p_semaphore\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
int monitor_destroy ( monitor *const p_monitor )
{
    
    // Argument check
    if ( p_monitor == (void *) 0 ) goto no_monitor;

    // Platform dependent implementation
    #ifdef _WIN64
        // TODO
        //

    #else

        // Return
        return ( pthread_cond_destroy(&p_monitor->_cond) == 0 ) && ( pthread_mutex_destroy(&p_monitor->_mutex) == 0 );
    #endif

    // Error handling
    {
        
        // Argument errors
        {
            no_monitor:
                #ifndef NDEBUG
                    printf("[sync] Null pointer provided for \"p_monitor\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
#endif

timestamp timer_high_precision ( void )
{
    
    // Initialiized data
    timestamp ret = 0;

    // Platform dependent implementation
    #ifdef _WIN64

        // Query the performance counter
        QueryPerformanceCounter((LARGE_INTEGER *)&ret);
    #else

        // Initialized data
        struct timespec ts;

        // Populate the time struct using the monotonic timer
        clock_gettime(CLOCK_MONOTONIC, &ts);

        // Compute the monotonic time in nanoseconds
        ret = ( (signed)ts.tv_sec * SEC_2_NS ) + ( (signed) ts.tv_nsec );
    #endif

    // Error
    return ret;
}

signed timer_seconds_divisor ( void )
{

    // Success
    return SYNC_TIMER_DIVISOR;
}

void timer_init ( void )
{
    
    // Platform dependent implementation
    #ifdef _WIN64
        QueryPerformanceFrequency((LARGE_INTEGER *)&SYNC_TIMER_DIVISOR);
    #else

        // Set the sync timer divisor
        *(signed *)(&SYNC_TIMER_DIVISOR) = SEC_2_NS;
        
    #endif

    // Return
    return;
}
