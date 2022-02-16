<mark>Template for your README. Remove all unused parts and instructions</mark>

# Lab work <mark>NUMBER</mark>: <mark>SHORT TOPIC</mark>
Authors (team): <mark>AUTHORS WITH GITHUB LINKS</mark><br>
Variant: <mark>VARIANT SHOULD BE HERE</mark>
## Prerequisites
Your should have `qt` and `boost` installed

#### Copyright note
**double-conversion** directory contains google's double conversion headers and source files only (https://github.com/google/double-conversion)

**ryu** directory contains ryu double conversion algoritm (https://github.com/ulfjack/ryu)

**cursom** is float to string implementation found on stack overflow. See link in custorm.h and custom.cpp for source

### Compilation
Compile either by hand with CMake file or runing `compile` script which does the job for you.

### Installation

<mark>DESCRIBE THE INSTALLATION PROCESS (USE ./dependencies FOLDER)</mark>

<mark>Note: For Python scripts, You must add `requirenments.txt` 
file and add your env to the `.gitignore` file!</mark>

### Usage
Run python script, found in project root directory, with arguments:
* Number of test for each method -- indicates how many times each method will be run and the minimum number of all this runs will be taken
* Input file, which stores floating point numbers in either normal notation or scientific. If you need to generate data we've already written a little function in `main.py`
* Output file with results -- if it doesn't exist, it will be create by program

### Important!
C++ executable should be in *current working directory* in relation to python script. So this end, you should run python script from **bin** directory (assuming C++ executable is there) in order that python script finds it

### Results

<mark>DESCRIBE THE RESULTS OF THE WORK YOU DID. WHAT DID YOU LEARN OR FIND INTERESTING?</mark>

# Additional tasks
<mark>IF APPLICABLE, LIST ALL THE EXTRA FEATURES YOU ADDED. PROVIDE DETAILS<mark>

# ATTENTION!

Additional tasks not listed in the previous paragraph would not be graded.

Be sure to provide a complete list of authors.

