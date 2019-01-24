# Compiler-for-babyC
<br>*(assume babycode.bc contains babyC code in .bc file)<br><br>

This programs reads a file(like testx.bc) and outputs 2 files(testx.iloc: this contains assembly code, report.txt: this contains variable declarations and compiling ERRORS if any).<br>
  1). If the code is indeed without error then it outputs the assembly level equivalent to testx.iloc file and has variables declared in report.txt file.<br>
  2). If there is comipling error on the file then the program does output the testx.iloc file and in the report.txt it states which line the error occured.<br>

<br>If there are no error on report.txt file then there was no compile error for the code.

So far compiler works for:
  1). Making sure variable is declared and of proper type.
  2). If/else statements
  3). While Loops
  
*compiler works for nested if/else/while loops.*
If there is any issue with those three, the program spits out where the line where the error occured following a somewhat specfic error.
