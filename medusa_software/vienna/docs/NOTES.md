# Vienna Notes
As for the procedure for decompilation, these are my general thoughts.

First, take machine code and disassemble it into assembly language. Then,
recognize patterns of assembly language that may correspond to higher-level
pseudo-code.

Example of assembly -> pseudocode patterns: (my ARM assembly is slightly rusty)

Also, note: `a`, `b`, ..., `z` are placeholders for different registers. Replace
all `a`'s synactically with `r0`, or `r1`, etc.

```
mov a, b
add a, a, c lsl #2
ldr d, a           ; or mov d, [a]
```

Which could be translated to:
```c
d = b[c]; // assuming b is a uint32_t* or equivalent.
```

Another example of assembly could be:
```
mov a, b
add a, a, c
```

Pseudocode:
```c
a = b + c;
```

Assembly:
```
movw a, #0x4141
movt a, #0x4242
blx a
```

Pseudocode:
```c
FUNC_0x42424141();
```

Assembly:
```
mov r0, a
blx b
```

Pseudocode:
```c
FUNC_b(a);
```

And the pseudocode:
```c
__fake_type_t a = b;
c(a);
```

Could be refined into:
```c
c(b);
```

Finally, combining multiple patterns, the assembly:
```
mov r0, r1
add r0, r0, r2 lsl #2
ldr r3, r0
mov r0, r3
blx r4
```

Could be translated into the pseudocode:
```c
__fake_type_t tmp1 = r1[r2];
FUNC_r4(tmp1);
```

Which could be refined into:
```c
FUNC_r4(r1[r2]);
```
