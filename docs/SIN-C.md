#SIN-C

A barebones C-like language that can be compiled for execution on the SIN-VM.


##Overview

###Grammar
- `<PROGRAM> = <EMPTY> | <PROGRAM> <LINE>` - Programs can be empty or lines.
- `<LINE> = (<STATEMENT> | <EXPRESSION>) '\n'` - Lines are statements or expressions terminated by a newline.

- `<STATEMENT> = <TYPE> <IDENTIFIER>` - Initializing identifier to datatype default.
- `<STATEMENT> = <TYPE> <IDENTIFIER> '=' <EXPRESSION>` - Initializing identifier to value.
- `<STATEMENT> = <IDENTIFIER> '=' <EXPRESSION>` - Identifiers can be set to evaluated expressions.

- `<EXPRESSION> = <INT> | <UINT> | <FLOAT> | <BOOL>` - Numbers evaulate to themselves.

###Data Types
- `int` : 32 bit signed integer
- `uint` : 32 bit unsigned integer
- `float` : 32 bit floating point real
- `bool` : can be equal to 'true' or 'false'




