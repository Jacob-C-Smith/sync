# sync 
[![CMake](https://github.com/Jacob-C-Smith/sync/actions/workflows/make.yml/badge.svg)](https://github.com/Jacob-C-Smith/sync/actions/workflows/make.yml)

 Cross platform synchronization primatives and high precision timestamps

 > 0 [Try it](#try-it)
 >
 > 1 [Download](#download)
 >
 > 2 [Build](#build)
 >
 >> 2.1 [Build > Targets](#build--targets)
 >>
 >> 2.2 [Build > Dependencies](#build--dependencies)
 >
 > 3 [Example](#example)
 >
 >> 3.1 [Example > Input](#example--input)
 >>
 >> 3.1 [Example > Output](#example--output)
 >
 > 4 [Test](#test)
 >
 >> 4.1 [Test > Input](#test--input)
 >>
 >> 4.1 [Test > Output](#test--output)
 >
 > 5 [Definitions](#definitions)
 >
 >> 5.1 [Definitions > Enumerations](#definitions--enumerations)
 >>
 >> 5.2 [Definitions > Structures](#definitions--structures)
 >>
 >> 5.3 [Definitions > Types](#definitions--types)
 >>
 >> 5.4 [Definitions > Functions](#definitions--functions)
 >>
 >> 5.5 [Definitions > Macros](#definitions--macros)
 >
 > 6 [Manual](#manual)
 >
 >> 6.1 [Manual > A](#manual--a)
 >>
 >> 6.2 [Manual > B](#manual--b)
 >>
 >> 6.3 [Manual > C](#manual--c)
 >
 > 7 [Commentary](#commentary)
## Try it
[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/Jacob-C-Smith/sync?quickstart=1)

Wait for a few moments, then continue to follow instructions from the [build](#build) section
 ## Download
 To download sync, execute the following command
 ```bash
 $ git clone https://github.com/Jacob-C-Smith/sync
 $ cd sync
 ```
 ## Build
 To build sync, execute the following commands in repository directory
 ```bash
 $ make
 ```

  This will build the example program and dynamic / shared libraries
 ### Build > Targets
 | Name                       | Description                               | Output                                                  |
 |----------------------------|-------------------------------------------|---------------------------------------------------------|
 | **all**                    | Make everything                           | *N/A*                                                   |
 | **clean**                  | Clean everything                          | *N/A*                                                   |
 | **sync**              | Build the sync library shared object | ```lib/libsync.so```                               |
 | **[project_example]**      | Build the sync library example       | ```lib/libsync.so``` ```build/sync_example``` |
 | **[project_example_run]**  | Run the sync library example         | ```lib/libsync.so``` ```build/sync_example``` |
 
 ### Build > Dependencies
 | Name    | Description                       | Files               | Status                                                                                                                                                 |
 |---------|-----------------------------------|---------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------|
 | **log** | *Error handling, debug logs, etc* | ```lib/liblog.so``` | [![CMake](https://github.com/Jacob-C-Smith/log/actions/workflows/make.yml/badge.svg)](https://github.com/Jacob-C-Smith/log/actions/workflows/make.yml) |
 | **...** | ...                               | ```...```           |                                                                                                                                                        |

 ## Example
 To run the example program, execute this command
 ```
 $ ./build/sync_example
 ```

 ### Example > Input
 ``` [None] ```

 ### Example > Output
 ``` [None] ```

 [Source code](main.c)
 ## Test 
 ``` [None] ```
 
 ### Test > Input
 ``` [None] ```

 ### Test > Output
 ``` [None] ```
 
 ## Definitions
 ### Definitions > Enumerations 
 ``` [None] ```

 ### Definitions > Structures 
 ``` [None] ```

 ### Definitions > Types
 ``` [TODO] ```

 ### Definitions > Functions
 ``` [None] ```

 ### Definitions > Macros
 ``` [None] ```

 ## Manual
 ``` [None] ```

 ### Manual > A
 ``` [None] ```

 ### Manual > B
 ``` [None] ```

 ### Manual > C
 ``` [None] ```

## Commentary
``` [ None ] ```