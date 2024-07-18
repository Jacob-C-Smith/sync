# sync 

[![sync](https://github.com/Jacob-C-Smith/sync/actions/workflows/cmake.yml/badge.svg)](https://github.com/Jacob-C-Smith/sync/actions/workflows/cmake.yml)
 
 Cross platform synchronization primatives and high precision timestamps

 > 0 [Try it](#try-it)
 >
 > 1 [Download](#download)
 >
 > 2 [Build](#build)
 >
 > 3 [Example](#example)
 >
 >> 3.1 [Example output](#example-output)
 >
 > 4 [Definitions](#definitions)
 >
 >> 4.1 [Type definitions](#type-definitions)
 >>
 >> 4.2 [Function definitions](#function-definitions)

## Try it
[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/Jacob-C-Smith/sync?quickstart=1)

Wait for a few moments, then click the play button on the bottom of the window. This will run the example program.

 ## Download
 To download sync, execute the following command
 ```bash
 $ git clone https://github.com/Jacob-C-Smith/sync
 ```
 ## Build
 To build on UNIX like machines, execute the following commands in the same directory
 ```bash
 $ cd sync
 $ cmake .
 $ make
 ```
  This will build the example program, the tester program, and dynamic / shared libraries

  To build sync for Windows machines, open the base directory in Visual Studio, and build your desired target(s)
 ## Example
 To run the example program, execute this command
 ```
 $ ./sync_example
 ```
 ### Example output
 [ NONE ]

 [Source](main.c) 
 ## Definitions
 ### Type definitions
 ```c
 typedef ...    mutex;
 typedef ...    semaphore;
 typedef size_t timestamp;
 ```
 *NOTE: mutex and semaphore definitions are platform dependent*
 ### Function definitions
 ```c 
 // Subsystem initialization
 void sync_init ( void );
 
 // Timestamps
 timestamp timer_high_precision  ( void );
 size_t    timer_seconds_divisor ( void );
 
 // Constructors
 int mutex_create      ( mutex     *p_mutex );
 int semaphore_create  ( semaphore *p_semaphore, int count );
 
 // Lock operations
 int mutex_lock        ( mutex     _mutex );
 int semaphore_wait    ( semaphore _semaphore );
 
 // Unlock operations
 int mutex_unlock      ( mutex     _mutex );
 int semaphore_signal  ( semaphore _semaphore );
  
 // Destructors
 int mutex_destroy     ( mutex     *p_mutex );
 int semaphore_destroy ( semaphore *p_semaphore );
 ```

Written by Jacob Smith, 2023
