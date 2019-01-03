# Matrix-Class
A matrix class for ease at matrix operations

### Build Using:
````c++
g++ <source_file_name>.cpp matrix.cpp console_position.cpp -o <executable_file_name>
````
Example: 
````c++ 
g++ main.cpp matrix.cpp console_position.cpp -o main
````

### Currently supported functions with this Matrix class:
* Entering a Matrix
* Printing a Matrix in [ ] notation
* Matrix Addition
* Matrix Subtraction
* Matrix Multiplication
* Scaler Multiplication to a Matrix
* Scaler Division to a Matrix
* Cofactors of a matrix of a specific order
* Cofactor of the total Matrix
* Determinant of a Matrix
* Transpose of a Matrix
* Adjoint of a Matrix
* Inverse of a Matrix
* Row/Coloumn Operations
  - Adding/Subtracting two Row/Coloumns
  - Multiplying a Row/Coloumn with a scaler Constant
  - Interchanging two Row/Column
* Convert a matix to its Row Reduced Echelon form
  - An option of displying the exact steps for the compution
* Compute Rank of a Matrix(by converting it into a row rduced echelon form)

### Notes on in.txt
A in.txt file has been included for easy inputting of matrix while debugging the code. One can use the in.txt file to save the input in plaintext which may can be used to debug the code without manually inputting on each executuon time.<br>
From [main.cpp](https://github.com/Kinjalrk2k/Matrix-Class/blob/d74f7d0b99529cf788fd33643e1e80345db47973/main.cpp#L6) file:
````c++
freopen("in.txt", "r", stdin);  //  ensures that the plaintext in in.txt is feed into the stdin buffer
````

### Notes on usability
Strictly meant for compilation and usage under Windows only (preferably using MinGW compiler toolkit).
This project has not been made "cross-platform".
It uses functions like system(), getch(), etc...

This project is still under development. Parts of the source codes may not be well documented.
Also suitable prompts may not be available for the user at the moment.

More features and fixes are yet to come. Meanwhile suggestions, ideas, bug reports are welcomed.

<br>***Kinjal Raykarmakar***
