/** !
 * Include header for sync library
 * 
 * @file sync/sync.h 
 * 
 * @author Jacob Smith 
 */

// Include guard
#pragma once

// Platform dependent includes
#ifdef _WIN64
    #include <windows.h>
    #include <process.h>
#else
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
    typedef HANDLE             mutex;
    typedef HANDLE             semaphore;
    typedef CONDITION_VARIABLE condition_variable;
#else
    typedef pthread_mutex_t mutex;
    typedef sem_t           semaphore;
    typedef pthread_cond_t  condition_variable;
#endif

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
DLLEXPORT int mutex_create ( mutex *p_mutex );

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
DLLEXPORT int semaphore_create ( semaphore *p_semaphore, int count );

/** !
 * Create a condition variable
 * 
 * @param p_condition_variable : ret
 * 
 * @sa condition_variable_destroy
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int condition_variable_create ( condition_variable *p_condition_variable );

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
DLLEXPORT int mutex_lock ( mutex _mutex );

/** !
 * Wait on a semaphore
 * 
 * @param _semaphore : the semaphore
 * 
 * @sa semaphore_signal
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_wait ( semaphore _semaphore );

/** !
 * Wait on a condition with a mutex
 * 
 * @param _condition_variable : the condition variable
 * @param _mutex              : the mutex
 * 
 * @sa condition_variable_signal
 * @sa condition_variable_broadcast
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int condition_variable_wait ( condition_variable _condition_variable, mutex _mutex );

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
DLLEXPORT int mutex_unlock ( mutex _mutex );

/** !
 * Signal a semaphore
 * 
 * @param _semaphore : the semaphore
 * 
 * @sa semaphore_wait
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_signal ( semaphore _semaphore );

/** !
 * Signal a condition variable
 * 
 * @param _condition_variable : the condition variable
 * 
 * @sa condition_variable_wait
 * @sa condition_variable_broadcast
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int condition_variable_signal ( condition_variable _condition_variable );

/** !
 * Signal all condition variables
 * 
 * @param _condition_variable : the condition variable
 * 
 * @sa condition_variable_wait
 * @sa condition_variable_signal
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int condition_variable_broadcast ( condition_variable _condition_variable );

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
DLLEXPORT int mutex_destroy ( mutex *p_mutex );

/** !
 * Deallocate a semaphore
 * 
 * @param p_semaphore : pointer to semaphore
 * 
 * @sa semaphore_create
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int semaphore_destroy ( semaphore *p_semaphore );

/** !
 * Deallocate a condition variable
 * 
 * @param p_condition_variable : pointer to condition variable
 * 
 * @sa condition_variable_create
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int condition_variable_destroy ( condition_variable *p_condition_variable );
