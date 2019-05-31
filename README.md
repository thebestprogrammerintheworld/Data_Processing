# Data processing
## [v0.1](https://github.com/thebestprogrammerintheworld/Data_Processing/tree/master/v0.1)
For the first version the task had to be realized in two different ways, by using:
1. C array
2. std::vector type container

The latter way is obviously easier than the former. By using the vector library the code length was decreased from 278 to 234 lines of code in the functions.cpp file. In addition to the task requirements, a menu was created to facilitate the navigation through the program. Furthermore, an intro alongside with instructions of use was added to create a more professional feel of the program. 
## [v0.2](https://github.com/thebestprogrammerintheworld/Data_Processing/tree/master/v0.2)
The program was further upgraded from the vector type container realization of the code. A new function to read from a file was added. The fstream library was utilized for this task. The program can now read from a .txt file to create new instances (students) of the student class, calculate their final mark and display the results in an aligned manner according to the requirements. Code length increased from 234 to 326 lines of code.
## [v0.3](https://github.com/thebestprogrammerintheworld/Data_Processing/tree/master/v0.3)
In this version, exception handling was added in places where a user has to enter marks for homeworks (it throws an error if it is out of range) and also where the filename has to be specified in order to read from a file. To implement exception handling, try and catch were used. 
## [v0.4](https://github.com/thebestprogrammerintheworld/Data_Processing/tree/master/v0.4)
Further fnctionality was added. The program now includes an option to generate a template .txt file with random results. In accordance with requirements, it generates 5 files of different sizes. After generating the files, the user can read the files in order to sort the students according their results into two separate files. Chrono library was used to perform a speed rate analysis of the program. Code length has increased to 437 lines. At this point the code lacks efficiency and can be optimized at some places to reduce the size of the code and improve readability.

[Release download link](https://github.com/thebestprogrammerintheworld/Data_Processing/releases/tag/v0.1-0.4)

## [v0.5](https://github.com/thebestprogrammerintheworld/Data_Processing/tree/master/v0.5.zip)
The menu was updated with a new function for container testing to measure the running speed of the program. Test files with student count ranging from one hundred up to a million are used for testing of three different containers (vector, deque, list). First, the program loads up a file and places it in a container, then testing is done by sorting the students into groups of students who passed and who failed, finally the students are split into the mentioned groups by creating two new text files containing students who passed and failed. It seems like vector and deque takes about the same time to sort and split, but list takes forever after ten thousand.
