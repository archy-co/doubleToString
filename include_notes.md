# General recomendations
It is important to split large files but is even more important to keep care of your files logic. Split subprojects into separate directories. For most parts, it is enough to have two files for one class:
- one header `.h` 
- one code `.cpp` files. 
Header `main.h` is mostly useless so one should not create it without adequate justification.

# The `include` directory

Since there is no standard C or C++ project structure, you can choose one of the two structures proposed below. The rationale behind such decision is that these two are best suited and therefore most commonly used for small-scale projects.

- The `include` directory contains all the header files included by your `.c` or `.cpp` files with corresponding names.
For example:

```text
src/
    main.cpp
    dispatcher.cpp
    helper_funcs.cpp
include/
    dispatcher.h
    helper_funcs.h
```

- The `include` directory serves as a public interface for your program or library. This means that whenever your program or library is added as a dependency for another project, the corresponding declarations for interfaces will have be located in the headers in your `include` directory. All other headers that are not intended to be used by other projects are considered to be private and should not be located in the `include` directory.
For example:

```text
src/
    main.cpp
    dispatcher.cpp
    helper_funcs.cpp
    main.h
    helper_funcs.h
include/
    dispatcher.h
```

## Header files

A_flag header file is a file containing C/C++ declarations and definitions that are shared between several source files. The source files can copy the contents of the header file by using `#include` directive, performed by the C preprocessor. 

**Including a header file produces the same results as copying the contents of the header file into the source file**. Manual copying would be time-consuming and error-prone. With a header file, the related declarations appear in only one place. If they need to be changed, they can be changed in one place, and programs that include the header file will automatically use the new version when next recompiled.

**By convention, header files use the `.h` extension**

### Include syntax

There are two ways to issue an `#include` directive:

- `#include <file>`
- `#include "file"`

If the first variant is used, the preprocessor will look for the header file only in the standard list of system directories. **This is most commonly used when including system header files**, for example

```C
#include <math.h>
#include <string.h>
#include <stdlib.h>
```

If the second variant is used, the preprocessor will first look in the directory containing the file which issued the directive, then in `quote` directories and then in the standard list of system directories. **This is typically used for user-defined headers** used in a program. For example

```C
#include "main.h"
#include "mylib.h"
```

 The `quote` directories can be specified in GCC using the `-iquote` argument. To avoid searching in the system directories, GCC option `-nostdinc` can be used. To explicitly view which directories are scanned, use the `-v` option.

**Note**: while these options are useful for testing, **avoid using them when submitting your work**. Use appropriate [**Cmake commands**](#cmake), such as `target_include_directories` instead.

**Note**: when including your user-defined headers, **never use absolute paths!**

### Include guards

If the header is included twice in the same program, the preprocessor will copy it twice. This will lead to unwanted behaviour, most likely an error. The standard way to prevent this is to use a conditional define:

```C
#ifndef MY_FUNC_HEADER
#define MY_FUNC_HEADER
...
#endif
```

The rest of the header is wrapped inside the conditional statement. This prevents repeated inclusion, since when the file will be included again, `#ifndef MY_FUNC_HEADER` will be `false`. This is known as an **include guard**

**Note**: It is crucial to **use an include guard in every header**, since other programs will expect it to have one and this might lead to unwanted errors. All system header files use include guards.

### Cmake

To include a directory use the `target_include_directories(target LINK_TYPE ${INCLUDE_DIR})` command. `LINK_TYPE` has to be either `PUBLIC`, `PRIVATE` or `INTERFACE`.

- `PRIVATE`: use only for this specified build target
- `PUBLIC`: use it for specified target and for targets which links with this project
- `INTERFACE`: use it only for targets which links with the current project 

Use `PUBLIC` if your `include` directory is a public interface (i.e. you are using the second folder structure).

Afterwards, the header files must be added as sources for your library/executable. This can be done via `add_executable`/`add_library` or via `target_sources`.

### Header file guidelines

Please make sure that your header file comply to all following guideline before submitting your work.

- **Always use “include guards” in a header file**
- **Your header files should only contain**
    - function declarations
    - definitions and macros
    - structure type declarations
    - global variable extern declarations
    - class declaration and member function declaration (C++)
    - Trivial member function defintions(C++)
- **Only include necessary header files**
- **The content of a header file should compile correctly by itself**
