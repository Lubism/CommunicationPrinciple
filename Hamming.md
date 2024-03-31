# Reference Manual of Hamming Coding

## Introduction

All methods in class Hamming are static, and all the methods are templates.  

The argument "Type" is a template variable, so "std::vector<>" will stand for "std::vector\<Type>".  

## <h2 id = "0">Methods List</h2>

### [Encoding, Decoding and Error Correcting](#0.1)

1. [ErrorCorrect(const std::vector<>&, const std::vector<>&): inline std::vector<>](#1.1)
1. [ErrorCorrect(const std::vector<>&, const Type&): inline std::vector<>](#1.2)

1. [ErrorDetect(const std::vector<>&, const std::vector<>&): inline Type](#1.3)
1. [ErrorDetect(const std::vector<>&, const Type&): inline Type](#1.4)

1. [Encode(const std::vector<>&, const std::vector<>&): inline std::vector<>](#1.5)
1. [Encode(const std::vector<>&, const Type&): inline std::vector<>](#1.6)

1. [Decode(const std::vector<>&, const std::vector<>&): inline std::vector<>](#1.7)
1. [Decode(const std::vector<>&, const Type&): inline std::vector<>](#1.8)

### [Matrix Generating](#0.2)

1. [MatrixH(const Type&): inline std::vector<>](#2.1)
1. [MatrixR(const Type&): inline std::vector<>](#2.2)
1. [MatrixG(const Type&): inline std::vector<>](#2.3)
1. [MatrixP(const Type&): inline std::vector<>](#2.4)
1. [MatrixI(const Type&): inline std::vector<>](#2.5)

### [Basic Algorithms](#0.3)

1. [MatrixMulti(const std::vector<>&, const std::vector<>&): inline std::vector<>](#3.1)

1. [ArraySum(const std::vector<>&, Type): inline std::vector<>](#3.2)

1. [InList(const std::vector<>&, const Type&): inline bool](#3.3)

1. [BitListParity(const Type&): inline std::vector<>](#3.4)

1. [BitListData(const Type&): inline std::vector<>](#3.5)

1. [CvtBinToDec(const std::vector<>&): inline Type](#3.6)

1. [CvtParityToData(const Type&): inline Type](#3.7)

1. [CvtDataToParity(const Type&): inline Type](#3.8)

1. [IsTwoPower(Type): inline bool](#3.9)

1. [Mod2Multi(const std::vector<>&, const std::vector<>&): inline std::vector<>](#3.10)

1. [RecursiveArraySum(const std::vector<>&, Type): inline std::vector<>](#3.11)

## Methods Descriptions

### <h2 id = "0.1">Encoding, Decoding and Error Correcting</h2>

#### <h2 id = "1.1">ErrorCorrect(message, matrixH)</h2>

Detect and correct the error bit in the message.  

This method is the matrix overload version, only execute the part of matrix calculating.  

##### Params

message: The bit stream to be corrected.  

matrixH: The error detection and correction matrix,
    click [this](#2.1) for further explanation.  

##### Return

The corrected message. Or empty container if arguments are invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "1.2">ErrorCorrect(message, bitsParity)</h2>

Detect and correct the error bit in the message.  

This method is the parity bits overload version, the argument "bitsParity" will be used to generate the matrix H, and then executing the same as another overload version.  

For the matrix H, see [another overload version](#1.1).  

##### Params

message: The bit stream to be corrected.  

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The corrected message. Or empty container if arguments are invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "1.3">ErrorDetect(message, matrixH)</h2>

Detect the error and find the location of error.  

This method is the matrix overload version, only execute the part of matrix calculating.  

##### Params

message: The bit stream to be detected.  

matrixH: The error detection and correction matrix,
    click [this](#2.1) for further explanation.  

##### Return

The error location in the message.  

If the arguments are invalid, returns -1.  

It returns zero if there is no error or the error cannot be detected in the message.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "1.4">ErrorDetect(message, bitsParity)</h2>

Detect the error and find the location of error.  

This method is the parity bits overload version, the argument "bitsParity" will be used to generate the matrix H, and then executing the same as another overload version.  

For the matrix H, see [another overload version](#1.3).  

##### Params

message: The bit stream to be detected.  

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The error location in the message.  

If the arguments are invalid, the method will return -1.  

It returns zero if there is no error or the error cannot be detected in the message.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "1.5">Encode(message, matrixG)</h2>

Encoding the message to hamming coding format.  

This method is the matrix overload version, only execute the part of matrix calculating.  

##### Params

message: The bit stream to be encoded.  

matrixG: The encoding message generating matrix,
    click [this](#2.3) for further explanation.  

##### Return

Encoded message, er empty container if argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "1.6">Encode(message, bitsParity)</h2>

Encoding the message to hamming coding format.  

This method is the parity bits overload version, the argument "bitsParity" will be used to generate the matrix G, and then executing the same as another overload version.  

For the matrix G, see [another overload version](#1.5).  

##### Params

message: The bit stream to be encoded.  

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The encoded message, or empty container if the arguments are invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "1.7">Decode(message, matrixR)</h2>

Decoding the message to original format.  

This method is the matrix overload version, only execute the part of matrix calculating.  

##### Params

message: The bit stream to be encoded.  

matrixR: The recovery matrix for decoding message,
    click [this](#2.2) for further explanation.  

##### Return

Encoded message, er empty container if argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "1.8">Decode(message, bitsParity)</h2>

Decoding the message to original format.  

This method is the parity bits overload version, the argument "bitsParity" will be used to generate the matrix R, and then executing the same as another overload version.  

For the matrix R, see [another overload version](#1.7).  

##### Params

message: The bit stream to be encoded.  

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The encoded message, or empty container if the arguments are invalid.  

---
[BACK TO THE LIST](#0)

### <h2 id = "0.2">Matrix Generating</h2>

#### <h2 id = "2.1">MatrixH(bitsParity)</h2>

Generate the error detecting matrix H.  

This matrix is consist of matrix I and matrix P.  

For the column which is parity bit(bit number is satisfied with 2^(N - 1) and N is integer),
    will be filled with the content of matrix I;  

For the other columns will be filled with the content of matrix P.  

##### Params

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The error detecting matrix, or empty container if argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "2.2">MatrixR(bitsParity)</h2>

Generate the decoding recovering matrix.  

This matrix is consist of matrix I and empty matrix.  

For the column which is parity bit(bit number is satisfied with 2^(N - 1) and N is integer),
    will be filled with the content of empty matrix;  

For the other columns will be filled with the content of matrix I.  

##### Params

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The decoding recovering matrix, or empty container if argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "2.3">MatrixG(bitsParity)</h2>

Generate the encoding generating matrix.  

This matrix is consist of matrix P and matrix I.  

For the row which is parity bit(bit number is satisfied with 2^(N - 1) and N is integer), will be filled with the content of matrix P;  

For the other rows will be filled with the content of matrix I.  

##### Params

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The encoding generating matrix, or empty container if argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "2.4">MatrixP(bitsParity)</h2>

Generate the constructing matrix.  

This matrix aims to show how much data bits can be covered by one parity bit(bit number is satisfied with 2^(N - 1) and N is integer), and display the result in boolean style.  

**For example, the number of parity bits is 3, it will be 1, 2, 4; For the data bits, it will be 3, 5, 6, 7.**  

And the major process of generating the matrix P would be like this:  

| Parity bit | 3 = 1 + 2 | 5 = 1 + 4 | 6 = 2 + 4 | 7 = 1 + 2 + 4 |
| :-: | :-: | :-: | :-: | :-: |
| 1 | 1 | 1 | 0 | 1 |
| 2 | 1 | 0 | 1 | 1 |
| 4 | 0 | 1 | 1 | 1 |

So, the generating result of matrix P will be like this:  

$$\begin{bmatrix}
1 & 1 & 0 & 1\\
1 & 0 & 1 & 1\\
0 & 1 & 1 & 1\\
\end{bmatrix}$$  

**One more example, if the parity bits is *1, 2, 4, 8*, and the data bits is *3, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15*, the major process of generating matrix P would be like this:**  

| Parity bit | 3 = 1 + 2 | 5 = 1 + 4 | 6 = 2 + 4 | 7 = 1 + 2 + 4 | 9 = 1 + 8 | 10 = 2 + 8 | 11 = 1 + 2 + 8 | 12 = 4 + 8 | 13 = 1 + 4 + 8 | 14 = 2 + 4 + 8 | 15 = 1 + 2 + 4 + 8 |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1 | 1 | 1 | 0 | 1 | 1 | 0 | 1 | 0 | 1 | 0 | 1 |
| 2 | 1 | 0 | 1 | 1 | 0 | 1 | 1 | 0 | 0 | 1 | 1 |
| 4 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 1 | 1 | 1 | 1 |
| 8 | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |

And the generating result of matrix P will be like this:  

$$\begin{bmatrix}
1 & 1 & 0 & 1 & 1 & 0 & 1 & 0 & 1 & 0 & 1\\
1 & 0 & 1 & 1 & 0 & 1 & 1 & 0 & 0 & 1 & 1\\
0 & 1 & 1 & 1 & 0 & 0 & 0 & 1 & 1 & 1 & 1\\
0 & 0 & 0 & 0 & 1 & 1 & 1 & 1 & 1 & 1 & 1\\
\end{bmatrix}$$  

##### Params

bitsParity: The number count of special bits, these bits are used to detect hamming code and checking the error.  

##### Return

The constructing matrix, or empty container if argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "2.5">MatrixI(width)</h2>

Generate the identity matrix.  

##### Params

width: The number of elements should be filled in a row/column.  

##### Return

The identity matrix, or empty container if argument is invalid.  

---
[BACK TO THE LIST](#0)

### <h2 id = "0.3">Basic Algorithms</h2>

#### <h2 id = "3.1">MatrixMulti(left, right)</h2>

The multiplication operation of matrix and vector.  

Both the result of left.size() and right.size() should not be zero, otherwise the method will return empty container.  

The result of left.size() % right.size() must be zero, otherwise the method will return empty container.  

##### Params

left: The matrix to do operation.  

right: The column vector to do operation.  

##### Return

The row vector after doing multiplication. Or empty container if arguments are invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.2">ArraySum(left, target)</h2>

Query the sum of some elements is equal to the target, which all the elements are unique.  

This method uses the combination of pruning and recursive tracing-back algorithms.  

And the whole algorithm is more like a branch of the sum of sub-set question.  

##### Params

left: The sequence list of unique elements.  

target: The target element of the summation.  

##### Return

The sequence list of the summation.  

If the target cannot reach, or the arguments are invalid, the method will return the empty container.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.3">InList(left, target)</h2>

Identify the target element is in the sequence list.  

##### Params

left: The sequence list to searched.  

target: The target element.  

##### Return

If the target element is in the list, return true, otherwise return false.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.4">BitListParity(bitsTotal)

Find the parity bits(bit number is satisfied with 2^(N - 1) and N is integer) in a certain range, and make them a list.  

##### Param

bitsTotal: The number of bit in the whole message.  

##### Return

The sequence list of parity bits. Or empty container if the argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.5">BitListData(bitsTotal)

Find the data bits(bit number is not satisfied with 2^(N - 1) when N is integer) in a certain range, and make them a list.  

##### Param

bitsTotal: The number of bit in the whole message.  

##### Return

The sequence list of data bits. Or empty container if the argument is invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.6">CvtBinToDec(input)</h2>

Convert the binary code to decimal.  

##### Param

input: The binary sequence list.  

##### Return

The converted number.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.7">CvtParityToData(bitsParity)</h2>

Convert the number count of parity bits to the number count of data bits.  

##### Param

bitsParity: The number count of parity bits.  

##### Return

The number count of data bits.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.8">CvtDataToParity(bitsData)</h2>

Convert the number count of data bits to the number count of parity bits.  

This is an estimated method, which only offers the minimum number of parity bits.  

##### Param

bitsData: The number count of data bits.  

##### Return

The minimum number of parity bits.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.9">IsTwoPower(num)</h2>

Identify the argument is satisfied with 2^(N - 1).  

##### Param

num: The number to be checked.  

##### Return

If the argument is satisfied with the condition, return true, or return false otherwise.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.10">Mod2Multi(left, right)</h2>

This is a protected method, only available for inherited object.  

This method will first do matrix multiplication to obtain the vector,
    and then take the reminder of 2 for every element in the vector.  

For another multiplication version, click [MatrixMulti(left, right)](#3.1)

##### Params

left: The matrix to be operated.  
right: The vector to be operated.  

##### Return

The row vector after doing operation. Or empty container if arguments are invalid.  

---
[BACK TO THE LIST](#0)

#### <h2 id = "3.11">RecursiveArraySum(left, target)</h2>

This is a protected method, only available for inherited object.  

This method is the core method of [ArraySum(left, right)](#3.2),
    uses trace-back to obtain the sequence list of the summation.  

##### Params

left: The sequence list of unique elements.  

target: The target element of the summation.  

##### Return

The sequence list of the summation.  

---
[BACK TO THE LIST](#0)
