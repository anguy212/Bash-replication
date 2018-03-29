# Project:

## This program does the following 
* Runs bash commands with the following connectors ( "||", "&&", ";" )
  * The "&&" connector makes sure the first command works before moving on to the next one
  * The "||" connector makes sure to move onto the second command if the first command does not work and, if it does, the second command does not work
  * The ";" connector executes all commands before and after the connector
* Runs bash commands with precendence (i.e. with parenthesis)
* Runs path validation along with any other commands with it
  * test -e "pathname" or with brackets
  * -f : if valid file
  * -d : if valid directory
  * -e : both 
* Runs bash commands which utilize input/output redirection with the following connectors ( "<", ">>", ">", "|" )
  * the "<" connector utilizes input redirection 
  * the ">>" connector utilizes output redirection to append to a file
  * the ">" connector utilizes output redirection to rewrite a file
  * the "|" connector utilizes output redirection to next command

## This is the project work distribution
### For Assignment 2:
  * Task 1: make execvp work for one function (20%) 
  * Task 2: make Composite class for connectors and commands (20%)
  * Task 3: parse user input into commands and empty connectors (20%)
  * Task 4: connect commands and empty connectors to make tree (20%)
  * Task 5: pull project together with user prompt (5%)
  * Task 6: make JSON file and makefile (5%)
  * Task 7: make testing shell scripts (5%)
  * Task 8: organize github set up structure with folders and tags (5%)
* Alice completed:
  * Task 1: make execvp work for one function (20%) 
  * Task 2: make Composite class for connectors and commands (20%)
  * Task 3: parse user input into commands and empty connectors (20%)
* Jesus completed:
  * Task 4: connect commands and empty connectors to make tree (20%)
  * Task 5: pull project together with user prompt (5%)
  * Task 7: make testing shell scripts (5%)
  * Task 8: organize github set up structure with folders and tags (5%)
  * Task 6: make JSON file and makefile (5%)
### For Assignment 3:
  * Task 1: make stat function work for filepath check (25%)
  * Task 2: code filepath connector for Command (25%)
  * Task 3: parse and execute Parenthesis (25%)
  * Task 4: parse and execute check for "test" and "[ ]" (25%)
* Alice completed:
  * Task 3: parse and execute Parenthesis (25%)
  * Task 4: parse and execute check for "test" and "[ ]" (25%)
* Jesus completed:
  * Task 1: make stat function work for filepath check (25%)
  * Task 2: code filepath connector for Command (25%)
### For Assignment 4:
  * Task 1: code pipe connector (20%)
  * Task 2: code append connector (15%)
  * Task 3: code input redirection connector (15%)
  * Task 4: code output redirection connector (15%)
  * Task 5: debugging projects (15%)
  * Task 6: make parsing work for new connectors (15%)
  * Task 7: github set up (2.5%)
  * Task 8: code shell test cases (2.5%)
* Alice completed:
  * Task 1: code pipe connector (20%)
  * Task 5: debugging projects (15%)
  * Task 6: make parsing work for new connectors (15%)
* Jesus completed:
  * Task 2: code append connector (15%)
  * Task 3: code input redirection connector (15%)
  * Task 4: code output redirection connector (15%)
  * Task 6: github set up (2.5%)
  * Task 7: code shell test cases (2.5%)

### Bugs
  * Pipe commands after first input will begin to behave out of order
  * Ending command with abort after a line of commands will not end the program, needs to be entered as single command
