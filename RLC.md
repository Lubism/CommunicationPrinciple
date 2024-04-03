# Reference Manual of Range Length Coding

## Introduction

All methods are static, and all methods are templates.  

The argument "Arg" is the template variable.  So:  

```
"std::function<>" stands for "std::function<Arg(int)>"
```

## Methods List

Improved(const Arg&, std::function<>)  

Basic(const Arg&, std::function<>)

## Methods Description

### Improved(input, cvtFunc)

Convert the sequence list into RLC type.  

Improved: If the number count of one character is only one,
    this method will not add the number at the front of the character.  

#### Arguments

input: The sequence to be encoded.  

cvtFunc: The function that can convert integer to the Arg.  

#### Return

The encoded message. Or empty container if the arguments are invalid.  

### Basic(input, cvtFunc)

Convert the sequence list into RLC type.  

Unlike the improved method, this method will add the number count,
    even if the number count of the character is only one.  

#### Arguments

input: The sequence to be encoded.  

cvtFunc: The function that can convert integer to the Arg.  

#### Return

The encoded message. Or empty container if the arguments are invalid.  
