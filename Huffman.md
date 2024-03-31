# Reference Manual of Hamming Coding

## Introduction

All methods are static, and all methods are templates.  

The arguments "Type" and "Key" are template variables, so:  

```
"std::vector<>" stands for "std::vector<Type>"

"std::unordered_map<>" stands for "std::unordered_map<Key, std::vector<Type> >"
```

## <h2 id = "0">Methods List</h2>

1. [Encode(const Key&, const std::unordered_map<>&): inline std::vector<>](#1.1)

1. [Decode(const std::vector<>&, const std::unordered_map<>&): inline Key](#1.2)

1. [CreateDict(const Key&): inline std::unordered_map<>](#1.3)

## Methods Descriptions

### <h2 id = "1.1">Encode(input, codeDict)</h2>

Encoding the message to binary stream.  

#### Params

input: The message to be encoded.  

codeDict: The coding dictionary for encoding and decoding.  

#### Return

The encoded binary stream, or empty container if the arguments are invalid.  

### <h2 id = "1.2">Decode(input, codeDict)</h2>

Decoding the binary stream to the original message.  

#### Params

input: The binary stream to be decoded.  

codeDict: The coding dictionary for encoding and decoding.  

#### Return

The decoded message, or empty container if the arguments are invalid.  

### <h2 id = "1.3">CreateDict(input)</h2>

Creating the coding dictionary for the whole message.  

This method uses priority queue as the container of heap sort.  

**The algorithm of this method is:**  

1. Taking the two elements with the smallest frequency from huffman tree(completed binary tree).

1. Encoding these two elements, lower branch(the smallest one) will be fill with 0,
    and the upper branch(the second smallest one) will be filled with 1.

1. Combine these two elements together, and then push it into the tree.

1. Repeat the steps mentioned before, until the number of element is only one.

#### Param

input: The whole message.  

#### Return

The coding dictionary, or empty dictionary if the argument is invalid.  
