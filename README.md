# Compiler-for-babyC <nr>

babyC is C language with the use of variables, conditional statements and while loop. 

This programs reads a file(like testx.bc) which contains the BabyC code and outputs <strong>2 files</strong>(testx.iloc: this contains assembly code, report.txt: this contains compiling ERRORS if any).<br><br>
  1). If the code is without error then it outputs the assembly level equivalent to testx.iloc file and report.txt file has no errors.<br>
  2). If the code indeed has errors then the program outputs the testx.iloc(up to the point of error) and in the report.txt it states which line the error occured.<br>

If there are no error on report.txt file then there was no compile error for the code.

So far compiler works for:<br>
  1). Making sure variable is declared. It also checks to be sure variables that are being assigned/reassigned are being assigned value of their type.(i.e. name is of type string, then the compiler checks if name is being assined to string value. If not, compiler gives error gives error)<br>
  2). If/else statements<br>
  3). While Loops<br>
  
*compiler works for nested if/else/while loops.*<br>
If there is any issue with those three, the program spits out line number where the error occured with a specific message.
