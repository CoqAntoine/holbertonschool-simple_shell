# Simple Shell

The *Simple Shell* is a simplified reproduction of a Linux command terminal. You can use it to perform basic tasks on your computer. 

## Flowchart

*Flowchart coming soon !*

## Installation

To use the *Simple Shell*, you may download all the files in this repository, and compile them using this command line (note that it uses the GNU Compiler Collection) :

````
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
````

Then, you can access the *Simple Shell* in your terminal by executing the **hsh** file. 
## Manual Page

You can found the manual page of the *Simple Shell* by typing this command line in your terminal :

````C
command line

````
## Usage/Examples

- **Enter commands**

As the *Simple Shell* handle the PATH environment variable, you can use commands by typing their entire path, or simply the command name if they are available in the PATH.  
You can also add arguments to your commands while using the *Simple Shell*. 

````
$ ls
file_1 file_2 file_3
$ /bin/ls -l
-rw-r--r-- 1 John John     8 Aug 18 16:20 file_1
-rwxr-xr-x 1 John John 17888 Aug 19 11:03 file_2
-rw-r--r-- 1 John John  4221 Aug 19 11:03 file_3
````

- **Built-in commands**

The *Simple Shell* have a bunch of built-in commands, such as **env** and **exit**. You can directly type them in your terminal to print your environment variables or exit the *Simple Shell*.  

- **Exit the *Simple Shell***

To exit the *Simple Shell*, you can either use **exit** or the command **Ctrl+D**.

````
$ exit
```` 

## Code Specifications

This project was made using the **C89** programmation language. It is also using the **Betty** coding style to organise the files. 
## Authors

- [@CoqAntoine](https://github.com/CoqAntoine)
- [@GuillaumeLerayGirardeau](https://github.com/GuillaumeLerayGirardeau)
