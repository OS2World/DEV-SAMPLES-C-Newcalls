rem - You will receive a slew of LNK4085 notices (these are not errors
rem   or warnings,  but a NOTICE),  so I redirect the output to "out".

rem - This program does not use any C runtime calls (/Gn).  If you
rem   add any,  take into account that the *.def file has "INITGLOBAL"
rem   and "SINGLE SHARED" data;  both of which tend to make C runtimes
rem   sick.

icc /Gn /O /Fenewcalls.dll newcalls.c newfwd.def os2386.lib >out
