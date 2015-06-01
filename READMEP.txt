=======================
HOW TO RUN THE PROGRAM
=======================
	- make interpreter // It will generated the object file interpreter.o.

 	- to run the code, interpreter <inputfile> <outputfile>

	- make clean // to remove the existing object file.

==============================
GUIDELINES TO RUN THE PROGRAM
==============================

	- The input s-expression will be taken from a input file and the output is printed onto a output file.
	- The input s-expression must be terminated with ";".
		EX: (MinuS 2 -9);
				(ATOM (QUOTE
				(2 . 3)));

	- The DEFUNC s-expression must be provided in the input file as shown below:
		(DEFUN F1 (A B) (MINUS A B));(F1.(5.(3.NIL)));
