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
  All methods are in src/methods.cpp file. Here you can find time required for each method to convert 1GB file with doubles to strings.
  
| method               	| description                                 	| time(mcs) 	|
|----------------------	|---------------------------------------------	|-----------	|
| method1_stringstream 	| use std::stringstream from iostream library 	| 3220381   	|
| method2_to_string    	| use to_string from standard library         	| 2885071   	|
| method6_sprintf      	| use sprintf from csdio library              	| 2849224   	|
  </mark>

  Here is histogram of different methods performance:
  
  ![cool1](https://user-images.githubusercontent.com/71673095/154725757-3f662f99-4861-4437-bad8-b66bdd6b65a3.png)
  
and another one without ```write_to_file``` method:
  
  ![cool](https://user-images.githubusercontent.com/71673095/154725297-a4080a50-6e29-4a13-bb1f-8205becfce90.png)

# Additional tasks
<mark>
  
| method                 	| description                                                   	| time(mcs) 	|
|------------------------	|---------------------------------------------------------------	|-----------	|
| method4_boost          	| use boost::lexical_cast                                       	| 5390497   	|
| method5_qt             	| use QString::number from Qt                                   	| 1129615   	|
| method6_ruy            	| use [Ryu](https://github.com/ulfjack/ryu) algorythm             | 12794348  	|
| method7_google         	| use [Google](https://github.com/google/double-conversion) double conversion                                  	| 306035    	|
| method8_gctv           	| ...                                                           	| 2962320   	|
| method9_ostringstream  	| use std::ostringstream                                        	| 3348719   	|
| method10_strtk         	| ...                                                           	| 5466267   	|
| method11_custom        	| using custom implementation from  [Stack overflow](https://stackoverflow.com/questions/7228438/convert-double-float-to-string)              	| 285272    	|
| method12_write_to_file 	| write all doubles to file, then read from this file as string 	| 317985684 	|
| method13_to_wstring    	| using to_wstring                                              	| 3133414   	|
| method14_floaxie       	| using [floaxie](https://github.com/aclex/floaxie) library       | 524469    	|
  
  <mark>
