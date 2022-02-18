# Lab work <mark>1</mark>: <mark>compare performance of different C++ tools</mark>
Authors (team): <mark>[Yaroslav Revera](https://github.com/archy-co), [Hanna Yershova](https://github.com/hannusia)<br>
Variant: <mark>4</mark>
## Prerequisites

<mark>have CMAKE, GCC, Qt, and boost downloaded</mark>

### Compilation

<mark>program compiles as you run python script
  ```$ python main.py 10 in.txt out.txt```</mark>

### Installation

<mark>clone repository and run python script</mark>

### Usage

<mark>```$ python main.py 10 in.txt out.txt```
  
To run experiments you have to execute python script, specify number of times that experiment will run, and two files: from first program will read data and second is to store results. These files doesn't require some specific names, as data is generated automatically at the beginning of each execution and is written to file that you specify.
  
After running program will print the minimum time for each method, and will check if all results coinside</mark>

### Important!

<mark>WHAT ELSE SHOULD WE KNOW ABOUT YOUR WORK? (E.G. KNOWN ISSUES, BUGS, SPECIAL BEHAVIOR ETC)</mark>

### Results

<mark>
  All methods are in src/methods.cpp file.
  
| method               	| description                                 	|
|----------------------	|---------------------------------------------	|
| method1_stringstream 	| use std::stringstream from iostream library 	|
| method2_to_string    	| use to_string from standard library         	|
| method3_sprintf      	| use sprintf from csdio library              	|  
  </mark>

# Additional tasks
<mark>IF APPLICABLE, LIST ALL THE EXTRA FEATURES YOU ADDED. PROVIDE DETAILS<mark>
