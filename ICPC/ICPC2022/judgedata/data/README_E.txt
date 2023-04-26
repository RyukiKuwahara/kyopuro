Problem E has multiple answers for a single input dataset.  The provided
answer files are examples of correct answers.  A program to judge if an
answer is correct or not (validator program) is also provided.

E_validator.cpp is the source code of the validator.
This validator takes three command line arguments: the path name of the 
input file, the correct answer for this input file, and the output of your
program to be judged.  The judge result is returned as the exit status
of the program; 0 means correct and non-zero values mean wrong answer.
The detailed judge status is also output to stderr.

Example:
(Assume your program is solve_E.py, and E_validator.cpp is compiled
to E_validator.  You need to prepare testlib.h distributed at
https://github.com/MikeMirzayanov/testlib/ to compile the validator.)
$ cat ./E1 | python solve_E.py > ./E1.out
$ ./E_validator ./E1 ./E1.ans ./E1.out
$ echo $?
(If the answer is correct, 0 is printed.  Otherwise a non-zero value
is printed.)
