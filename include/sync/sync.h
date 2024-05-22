/** !
 * Header for cross platform synchronization primitives 
 * 
 * @file sync/sync.h 
 * 
 * @author Jacob Smith 
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <time.h>

// log module
#include <log/log.h>

// Platform dependent includes
#ifdef _WIN64
    #include <windows.h>
    #include <process.h>
#else
    #include <unistd.h>
    #include <pthread.h>
    #include <semaphore.h>
#endif

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Platform dependent typedefs
#ifdef _WIN64
    typedef HANDLE mutex;
    typedef HANDLE semaphore;
    typedef HANDLE thread;
#else
    typedef pthread_mutex_t mutex;
    typedef sem_t           semaphore;
    typedef struct
    {
        pthread_mutex_t _mutex;
        pthread_cond_t  _cond;
    } monitor;
#endif

// Typedefs
typedef signed timestamp;

// Initializer
/** !
 * This gets called at runtime before main. 
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void sync_init ( void ) __attribute__((constructor));

// Timer
/** !
 * Get a high precision time stamp. Compute differences,
 * and use the SYNC_TIMER_DIVISOR constant to convert 
 * time to seconds
 * 
 * @param void
 * 
 * @sa timer_seconds_divisor
 * @sa sync_init
 * 
 * @return a high precision time stamp
 */
DLLEXPORT timestamp timer_high_precision ( void );

/** !
 * Get a constant for converting time to seconds. Dividing
 * the difference of two timestamp by the return yields the
 * time between timestamps in seconds.
 * 
 * @param void
 * 
 * @sa timer_high_precision
 * @sa sync_init
 * 
 * @return a constant integer for converting time to seconds
 */
DLLEXPORT signed timer_seconds_divisor ( void );

// Constructors
/** !
 * Create a mutex
 * 
 * @param p_mutex result
 * 
 * @sa mutex_destroy
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int mutex_create ( mutex *p_mutex );

#ifdef BUILD_SYNC_WITH_SEMAPHORE
/** !
 * Create a semaphore
 * 
 * @param p_semaphore result
 * @param count       the initial count
 * 
 * @sa semaphore_destroy
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_create ( semaphore *p_semaphore, unsigned int count );
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
/** !
 * Create a monitor
 * 
 * @param p_monitor result
 * 
 * @sa monitor_destroy
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int monitor_create ( monitor *p_monitor );
#endif

// Lock operations
/** !
 * Lock a mutex
 * 
 * @param p_mutex the mutex
 * 
 * @sa mutex_unlock
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int mutex_lock ( mutex *p_mutex );

#ifdef BUILD_SYNC_WITH_SEMAPHORE
/** !
 * Wait on a semaphore
 * 
 * @param _semaphore the semaphore
 * 
 * @sa semaphore_signal
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_wait ( semaphore _semaphore );
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
/** !
 * Wait on a monitor
 * 
 * @param p_monitor the monitor
 * 
 * @sa monitor_notify
 * @sa monitor_notify_all
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int monitor_wait ( monitor *p_monitor );
#endif

// Unlock operations
/** !
 * Unlock a mutex
 * 
 * @param p_mutex the mutex
 * 
 * @sa mutex_lock
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int mutex_unlock ( mutex *p_mutex );

#ifdef BUILD_SYNC_WITH_SEMAPHORE
/** !
 * Signal a semaphore
 * 
 * @param _semaphore the semaphore
 * 
 * @sa semaphore_wait
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_signal ( semaphore _semaphore );
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
/** !
 * Signal one thread
 * 
 * @param p_monitor the monitor
 * 
 * @sa monitor_wait
 * @sa monitor_notify_all
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int monitor_notify ( monitor *p_monitor );

/** !
 * Signal all threads
 * 
 * @param p_monitor the monitor
 * 
 * @sa monitor_wait
 * @sa monitor_notify
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int monitor_notify_all ( monitor *p_monitor );
#endif

// Destructors
/** !
 * Free a mutex
 * 
 * @param p_mutex the mutex
 * 
 * @sa mutex_create
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int mutex_destroy ( mutex *p_mutex );

#ifdef BUILD_SYNC_WITH_SEMAPHORE
/** !
 * Free a semaphore
 * 
 * @param p_semaphore the semaphore
 * 
 * @sa semaphore_create
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_destroy ( semaphore *p_semaphore );
#endif

#ifdef BUILD_SYNC_WITH_MONITOR
/** !
 * Free a monitor
 * 
 * @param p_monitor the monitor
 * 
 * @sa monitor_create
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int monitor_destroy ( monitor *p_monitor );
#endif

// Cleanup
/** !
 * This gets called at runtime after main
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void sync_exit ( void ) __attribute__((destructor));
