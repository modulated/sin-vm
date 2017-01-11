#SIN ASM OpCodes
SIN ASM files must have a .san file extention with each line ending in \n.

##Basic OpCodes

| OpCode | Description | Arguments |
|--------|-------------|----------:|
|'end' | Halts program execution | 0|
|'nop' | No operation | 0|
|'set' | Pushes <1> to stack | 1|
|'pop' | Pop top value off stack | 0|
|'get' | Returns top value of stack to output register <1> | 1|
|'clr' | Clear output register <1> | 1|


##Arithmetic
| OpCode | Description | Arguments |
|--------|-------------|----------:|
|'inc' | Increment top value of stack | 0|
|'dec' | Decrement top value of stack | 0|
|'add' | Add top two stack values, push result | 0|
|'sub' | Subtract second stack value from first, push result | 0|
|'mul' | Multiply top two stack values, push result | 0|
|'div' | Divide first stack value from second, push result | 0|
|'mod' | Modulus of first stack value by second, push result | 0|


##Control Flow
| OpCode | Description | Arguments |
|--------|-------------|----------:|
|'jmp' | Jump to <1> instruction | 1|
|'jmt' | Jump to <1> instruction if top of stack positive | 1|
|'jmz' | Jump to <1> instruction if top of stack zero | 1|
|'jmn' | Jump to <1> instruction if top of stack negative | 1|

##Input & Output
| OpCode | Description | Arguments |
|--------|-------------|----------:|
|'ini' | Push int from stdin to stack| 0|
|'out' | Pop int from stack to stdout| 0|
