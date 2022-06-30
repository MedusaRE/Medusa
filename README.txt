 __  __          _                 
|  \/  | ___  __| |_   _ ___  __ _ 
| |\/| |/ _ \/ _` | | | / __|/ _` |
| |  | |  __/ (_| | |_| \__ \ (_| |
|_|  |_|\___|\__,_|\__,_|___/\__,_|

What is Medusa?
Medusa is a project to create a cross platform debugger, code editor, and
general development environment, targeting lower level development.
The Medusa project also includes the desire to create a better piece of software
for reverse engineering, as all of them have their own problems.
For example:
    - Cutter: not very featureful, essentially a radare2 GUI, doesn't have
      debugger and/or emulation support to my knowledge, and more.
    - Ghidra: personal favorite currently, still doesn't have emulation support
      or code editing, and is written in Java (besides the decompiler), which is
      one of my least favorite languages.
    - IDA (Pro): expensive, closed source, does not have emulation support,
      or code editing
    - Radare2: does not have emulation support, or code editing.

Planned features include:
    - support for multiple architectures
    - assembly editing
    - C/C++ editing
    - assembling, and compilation support for a large number of architectures
    - a debugger, with the ability to step forward and backward through
      instructions, view and modify registers, edit memory, scripting support,
      an API for writing things such as syscall handlers, and more.
    - both a GUI and TUI interface, as well as a scripting platform & network
      support, think of something like LLDB and its ability to debug over a
      network.
    - binary loading
    - multiple executable formats supported, Mach-O, ELF, PE, etc
    - a disassembler to aid in reverse engineering
    - possibly decompiler support (Ghidra?)
    - and more!

Credits:
    spv           - project founding
    Capstone Team - Capstone
    Unicorn Team  - Unicorn
    Keystone Team - Keystone
    LIEF Project  - LIEF
    QEMU          - QEMU
    
    and probably more...
