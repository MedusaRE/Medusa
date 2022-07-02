![Medusa logo](/res/medusa_logo_lus_rounded.png)

# Medusa
## What is Medusa?
Medusa is a project to create a cross platform general purpose tool for software
research, be that reverse engineering, development, analysis, preservation: any
form of software research.

All current software research tools have their own problems: Medusa is meant to
solve these issues.

For example:
- Cutter: not very featureful, essentially a radare2 GUI, doesn't have
  debugger and/or emulation support to my knowledge, and more.
- Ghidra: personal favorite currently, still doesn't have emulation support
  or code editing, and is written in Java (besides the decompiler), which is
  one of my least favorite languages.
- IDA (Pro): expensive, closed source, does not have emulation support,
  or code editing.
- Radare2: does not have code editing, a GUI, or the level of emulation support
  which I intend to include in Medusa.

Planned features include:
- Support for multiple architectures (armv7, arm64, x86, x84-64, Z80, 6502, 68K,
  Java bytecode, etc. )
- Assembly editing
- C/C++ editing
- Assembling support for many architectures
- Compilation support for many architectures
- A debugger, with the ability to step forward and backward through
  instructions, view and modify registers, edit memory, scripting support,
  an API for writing things such as syscall handlers, and more.
- Both a GUI and TUI interface
- Scripting platform & network interface, à la LLDB
- Support for many executable formats (Mach-O, ELF, PE, MZ, JAR)
- multiple executable formats supported, Mach-O, ELF, PE, Jar, etc. )
- A disassembler to aid in reverse engineering
- Decompiler support ([Ghidra](https://www.ghidra-sre.org)?)
- and more!

## License
Currently, all of the source code written for the Medusa project is licensed
under Version 2 of the GNU General Public License (GPLv2), without the "any
later version" clause.
Other resources are released under CC BY-SA 4.0.

Files should contain a disclaimer indicating their license. If not, (excluding
submodules) go through the chain of parent folders until you find the first
parent folder with a `LICENSE` file: that is the license of the file in
question.

## Credits
```
    spv           - project founding
    Capstone Team - Capstone
    Unicorn Team  - Unicorn
    Keystone Team - Keystone
    LIEF Project  - LIEF
    QEMU          - QEMU
    
    and probably more...
```

## Donations
Lastly, I've (spv) been asked if I accept donations. I will place some wallet
addresses at the end of this section, but keep this in mind. I'm doing fine, and
there are probably organizations more deserving of your money than I am.
Consider donating to these organizations instead:
- [Amnesty International](https://www.amnesty.org/)
- [The Humane Society of The United States](https://www.humanesociety.org/)
- [Feeding America](https://www.feedingamerica.org/)
- More will be added to this list as I find charities I would like to
  support.

If, for some reason, you would still like to donate to me, here are some
cryptocurrency wallets you could donate to.

```
BTC: bc1qjg6jck6c08lqrxdgjnuj5m8c3v0zdrfh7rvjt5
ETH: Will add once I find a good ETH wallet.
XMR: 8BzgGQbbBUybgYw2dEC5EhazQcKGyG6UL6A9bueuDT5Mjhuwo3H7Lg2jEkEEJcrNR7W2MtCKfoRkEBxi3JjztwHj1VwMV2u
XLM: GBKN2D7ZRBPQDW7GEQCT23ID6PVNZ43A224ULBZSP6G4JBNDEKY42J6C
```