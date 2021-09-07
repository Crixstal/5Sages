# **5 Sages by Manon MÉHALIN**

## **Summary**

- [Description](##Description)
- [Informations](##Informations)
- [Work in progress](##Work%20in%20progress)
- [Known issues](##Known%20issues)
- [References](##References)

## **Description**

The project objective is to write a multithreaded program that will solve the riddle of the 5 wise men's dinner.

![Table](table.png "Sages layout")

## **Informations**

The program runs in Debug or Release, platform x64.  
In the zip file "GP2_MEHALIN_M" on sirius you can find :
- the README file
- "table.png" to see the sages layout
- the bin folder which contains "5Sages.exe" (Release) to launch the program

## **Work in progress**

- programmable variables without recompiling the code
- better display in the console
- specific text color and white background per sage name (see `void printName()`)

## **Known issues**

The program only works with 5 sages.

## **References**

C++:
---
- C++ references: https://en.cppreference.com/
- Thread: http://www.cplusplus.com/reference/thread/thread/
- Mutex: http://www.cplusplus.com/reference/mutex/

Change text color in console:
---
- https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
- https://stackoverflow.com/questions/8621578/do-windows-console-color-values-have-official-names-constants-associated-with/49929936#49929936
- https://stackoverflow.com/questions/17125440/c-win32-console-color/17125539

Stack Overflow:
---
- https://stackoverflow.com/questions/6374264/is-cout-synchronized-thread-safe

- https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range/19728404#19728404

- https://stackoverflow.com/questions/14391327/how-to-get-duration-as-int-millis-and-float-seconds-from-chrono