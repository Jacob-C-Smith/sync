/** !
 * Include header for sync library
 * 
 * @file sync/sync.h 
 * 
 * @author Jacob Smith 
 */

// Include guard
#pragma once

// Includes
#include <stdio.h>

// Platform dependent includes
#ifdef _WIN64
    #include <windows.h>
    #include <process.h>
#else
    #include <pthread.h>
    #include <semaphore.h>
    #include <time.h>
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
#else
    typedef pthread_mutex_t mutex;
    typedef sem_t           semaphore;
#endif

// Typedefs
typedef size_t timestamp;

/** !
 * Initialize the high precision timer
 * 
 * @param void
 * 
 * @sa timer_high_precision
 * 
 * @return void
 */
DLLEXPORT void timer_init ( void );

/** !
 * Get a high precision time stamp. Compute differences,
 * and use the SYNC_TIMER_DIVISOR constant to convert 
 * time to seconds
 * 
 * @return a high precision time stamp.
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
 * @sa timer_init
 * 
 * @return a constant for converting time to seconds
 */
DLLEXPORT size_t timer_seconds_divisor ( void );

// Constructors
/** !
 * Create a mutex
 * 
 * @param p_mutex : ret
 * 
 * @sa mutex_destroy
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int mutex_create ( mutex *const p_mutex );

/** !
 * Create a semaphore
 * 
 * @param p_semaphore : ret
 * @param count       : the initial count
 * 
 * @sa semaphore_destroy
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_create ( semaphore *const p_semaphore, int count );

// Lock operations
/** !
 * Lock a mutex
 * 
 * @param _mutex : the mutex
 * 
 * @sa mutex_unlock
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int mutex_lock ( const mutex _mutex );

/** !
 * Wait on a semaphore
 * 
 * @param _semaphore : the semaphore
 * 
 * @sa semaphore_signal
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_wait ( const semaphore _semaphore );

// Unlock operations
/** !
 * Unlock a mutex
 * 
 * @param _mutex : the mutex
 * 
 * @sa mutex_lock
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int mutex_unlock ( const mutex _mutex );

/** !
 * Signal a semaphore
 * 
 * @param _semaphore : the semaphore
 * 
 * @sa semaphore_wait
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_signal ( const semaphore _semaphore );

// Destructors
/** !
 * Deallocate a mutex
 * 
 * @param p_mutex : pointer to mutex
 * 
 * @sa mutex_create
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int mutex_destroy ( const mutex *const p_mutex );

/** !
 * Deallocate a semaphore
 * 
 * @param p_semaphore : pointer to semaphore
 * 
 * @sa semaphore_create
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_destroy ( const semaphore *const p_semaphore );
