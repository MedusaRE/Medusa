 __  __          _                 
|  \/  | ___  __| |_   _ ___  __ _ 
| |\/| |/ _ \/ _` | | | / __|/ _` |
| |  | |  __/ (_| | |_| \__ \ (_| |
|_|  |_|\___|\__,_|\__,_|___/\__,_|


Medusa Machine Framework

The Medusa Machine Framework is intended to be a centralized API for
controlling, accessing, and generally manipulating virtual, or real-world
machines for debugging, reverse-engineering, and other similar tasks.

The goal is to create one API that encompasses disassembling, assembling,
emulation, hardware control, and more. The reason for this is to make it easier
to implement new machines into Medusa in a reasonably quick fashion.

Currently, Medusa is based on Capstone and Unicorn, with Keystone being used
"eventually" to allow for assembling of code.

However, ideally, Medusa won't be limited to the architectures that all 3 of
these projects support, and can be adapted to work in stranger real-world
scenarios.

For example, say you would like to work on kernel development for the x86
platform. To do this, you would want more than just an emulated x86 CPU itself,
but a full IBM PC-style hardware platform.

Unicorn does not support this (to my knowledge), so what you could do instead
is write a new machine "description", "library", whatever you want to call it,
that provides known API calls that Medusa expects. Known calls would be things
like reading/writing memory, reading/writing registers, assembling and
disassembling code, and things like that. In addition, a platform like this
may be more usable if you also had the ability to do things like viewing the
screen output within Medusa. Because of this, the goal is to allow writing more
abstract parts of the machine, like a screen, so that even if Medusa does not
alrady have support for the class of hardware you are attempting to use, you
can implement it.

On the other hand, say you want to use Medusa with a real-world machine, or
a program running on a real machine. The goal is to allow you to write code to
support, say, LLDB/GDB connections to this machine and/or programs running on
it. This could allow you to, for example, connect to an iOS device that has
kernel debugging features (say with checkm8), and debug the XNU kernel.

This is part of the goal of Medusa, which is to provide an all-in-one reverse
engineering, development, debugging, and such platform: I'm trying to build
the best reverse engineering software there is.
