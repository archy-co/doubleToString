# Double to string conversion benchmark 🧐

This project aims to compare performance of different C++ methods to convert double numbers to string.

Tis is test-function prototype that takes vector of numbers as argument and returns pair with method's working time and average length of strings in input vector.
```
std::pair<size_t, double> method_x(const std::vector<double> & numbers);
```

This project was written and tested only on Linux(we use Arch btw), so usage on other systems is experimental.
If you can help with testing on Windows or MacOS, contact us.

Already we have implemented 14 methods.

#### Copyright note on subdirectories
* **double-conversion** -- google's double conversion headers and source files (https://github.com/google/double-conversion)
* **ryu** -- ryu double conversion algoritm (https://github.com/ulfjack/ryu)
* **floaxie** -- Floaxie (https://github.com/aclex/floaxie)
* **strtk** -- String toolkit (www.partow.net/programming/strtk/index.html)
* **custom.h** & **custom.cpp** -- float to string implementation found on stack overflow (https://stackoverflow.com/questions/7228438/convert-double-float-to-string)

## Prerequisites
<mark>Have CMAKE, GCC, Qt, and boost installed</mark>

## Installation
Clone repository
```{bash}
$ git clone https://github.com/archy-co/doubleToString.git
```

## Usage
You can compile program manually using cmake.

Or you can python script that will compile and execute program:
```{bash}
$ python main.py 10 in.txt out.txt
```

To run python script you have to specify number of times that experiment will run, and two files: from first program will read data and second is to store results. These files doesn't require some specific names, as data is generated automatically at the beginning of each execution (if you have your specific input data you want to run just comment the line in python script that generates data) and is written to file that you specify.
  
After running program will print the minimum time for each method, and will check if all results of the method coinside

### Important!
Method #12 **write to file** runs about 75-80 times slower than other methods. Therefore in python script the number of runs to take min time is lower than for all the other methods by default. If you want, you can configure it for your own needs but current configurations are alright for normal run and comparison of times

## Results

All methods are in ```src/methods.cpp file```. Here is a table with time required for each method to convert 1GB file with doubles to strings.
  
| method               	| description                                 	| time(mcs) 	|
|----------------------	|---------------------------------------------	|-----------	|
| method1_stringstream 	| use std::stringstream from iostream library 	| 3220381   	|
| method2_to_string    	| use to_string from standard library         	| 2885071   	|
| method6_sprintf      	| use sprintf from csdio library              	| 2849224   	|
| method4_boost          	| use boost::lexical_cast                                       	| 5390497   	|
| method5_qt             	| use QString::number from Qt                                   	| 1129615   	|
| method6_ruy            	| use [Ryu](https://github.com/ulfjack/ryu) algorythm               | 12794348  	|
| method7_google         	| use [Google](https://github.com/google/double-conversion) double conversion                                  	| 306035    	|
| method8_gctv           	| use stdlib.h function to convert double to string              	| 2962320   	|
| method9_ostringstream  	| use std::ostringstream                                        	| 3348719   	|
| method10_strtk         	| use [String Toolkit Library](http://www.partow.net/programming/strtk/index.html)                                                          	| 5466267   	|
| method11_custom        	| use custom implementation from  [Stack overflow](https://stackoverflow.com/questions/7228438/convert-double-float-to-string)              	| 285272    	|
| method12_write_to_file 	| write all doubles to file, then read from this file as string 	| 317985684 	|
| method13_to_wstring    	| use to_wstring                                                	| 3133414   	|
| method14_floaxie       	| use [floaxie](https://github.com/aclex/floaxie) library           | 524469    	|

Here is histogram of different methods performance:
  
  ![cool1](https://user-images.githubusercontent.com/71673095/154725757-3f662f99-4861-4437-bad8-b66bdd6b65a3.png)
  
and another one without ```write_to_file``` method:
  
  ![cool](https://user-images.githubusercontent.com/71673095/154725297-a4080a50-6e29-4a13-bb1f-8205becfce90.png)
  
## Contributing:
If you want to add other methods or contribute other ways, open an issue or clone and install the project using the abovementioned installation instructions, opening up the pull request once you are finished. Also you can contact us through [twitter](https://twitter.com/hannusiaa).

Fell free to contact us anytime and ask some questions or give your feedback and suggestions.

## Authors:
[Hanna Yershova](https://github.com/hannusia)

[Yaroslav Revera](https://github.com/archy-co)

## License
MIT License
