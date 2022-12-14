![Medusa logo](/res/img/medusa_logo_lus_rounded.png)

# Medusa
![Badge](/res/badges/commit_count.svg)
![Badge](/res/badges/loc.svg)
![Badge](/res/badges/license.svg)
![Badge](/res/badges/build.svg)
![Badge](/res/badges/commit.svg)
![Badge](/res/badges/branches.svg)
## What is Medusa?
Medusa (previously called xp<sup>DBG</sup>) is a project to create a cross
platform, free, and general purpose tool for software and hardware research,
such as reverse engineering, analysis, emulation, development, debugging, and
other similar tasks.

All current software research tools have their own problems: Medusa is meant to
solve these issues.

Medusa is mainly written in C/[C++](https://www.isocpp.org), with some
development tools (i.e. not the software an end user will interact with, but
tools a Medusa developer may) written in [Python](https://python.org),
[JavaScript](http://www.ecma-international.org/publications-and-standards/standards/ecma-262/),
and shell scripts.

For example:
- Cutter: not very featureful, essentially a radare2 GUI, doesn't have
  debugger and/or emulation support to my knowledge, and more.
- Ghidra: personal favorite currently, still doesn't have emulation support
  or code editing, and is written in Java (besides the decompiler), which is
  one of my least favorite languages.
- IDA (Pro): expensive, non-free, does not have emulation support,
  or code editing.
- Radare2: does not have code editing, a GUI, or the level of emulation support
  which I intend to include in Medusa.
- Binary Ninja: I honestly do not have a lot of experience with Binary Ninja,
  but to my knowledge, it is not free/open-source software, it isn't a full IDE
  (like Medusa is intended to be), and doesn't have emulation support (like
  Medusa is intended to).

This list disregards the fact that, to my knowledge, none of those tools have
support for the sort-of hardware research I'd like to support in Medusa.

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
- Support for many executable formats (Mach-O, ELF, PE, MZ, JAR, etc. )
- A disassembler to aid in reverse engineering
- Decompiler support (for example, [Ghidra](https://www.ghidra-sre.org)'s
  decompiler)
- and more!

If you would like to view a version of this document in another form, type
`curl medusa-re.org` into your terminal, and press Enter/Return.

## Learning
If you've just learned of the Medusa Project and would like to begin working on
/ with it, I can suggest a few resources.
- Visit [the Medusa Project website](https://www.medusa-re.org).
- Read [the book](https://www.medusa-re.org/book_wip.pdf). (WIP)
- Read [the documentation](https://docs.medusa-re.org).

## Installation
### Requirements
The exact commands necessary to install the requirements for Medusa will differ
based on the OS you are running, but in general, you will need to install:
- [`unicorn`](https://github.com/unicorn-engine/unicorn) (submodule available)
- [`capstone`](https://github.com/capstone-engine/capstone) (submodule available)
- [`keystone`](https://github.com/keystone-engine/keystone) (submodule available)
- [`doxygen`](https://doxygen.nl)
- [`GtkSourceView`](https://gitlab.gnome.org/GNOME/gtksourceview) (submodule available)
- [`GtkSourceViewMM`](https://gitlab.gnome.org/GNOME/gtksourceviewmm) (submodule available)
- [`gtkmm3`](https://www.gtkmm.org)
- [`gtk3`](https://www.gtk.org)
- [`glade`](https://glade.gnome.org)
- [`GIMP`](https://www.gimp.org)
- [`LaTeX`](https://www.latex-project.org)
- [`python3`](https://www.ptrgon.org)
- [`Pillow`](https://python-pillow.org)
- [`Node`](https://www.nodejs.org)
- [`npm`](https://www.npmjs.com)
- [`badgen`](https://www.npmjs.com/package/badgen)
- [`GNU Make`](https://www.gnu.org/software/make/)
- [`clang`](https://clang.llvm.org/) / [`LLVM`](https://llvm.org/)
- [`CMake`](https://www.cmake.org)
- [`cloc`](https://github.com/AlDanial/cloc)
- [`gtest`](https://github.com/google/googletest)

If you are running Arch Linux, or an Arch-based distro, such as Manjaro, you can
install all of the dependencies for Medusa by running `tools/deps_arch.sh` as
`root`.

If you are running Debian, or a Debian-based distro, such as Ubuntu, Pop!_OS, or
Kali, you can install all of the dependencies for Medusa by running
`tools/deps_debian.sh` as root.

### Compilation
To compile all Medusa components, `cd` into the Medusa folder (the parent folder
of this `README.md`), and type `make`. Assuming that all requirements are
installed, all components should be built, including:
- [`barcelona`](/medusa_software/barcelona)
- [`berlin`](/medusa_software/berlin)
- [`frontend`](/medusa_software/frontend)
- [`libmedusa`](/medusa_software/libmedusa)
- [`libxparse`](/medusa_software/libxparse)
- [`london`](/medusa_software/london)
- [`paris`](/medusa_software/paris)
- [`rome`](/medusa_software/rome)
- etc.

### Installing to your machine
As Medusa is not a finished project yet, there is not a way to fully install it
yet. The way that will probably be done is that after running `make`, you would
run `sudo make install`. Windows will likely have different steps, but I (spv)
am running GNU/Linux on my personal machine, not Windows, so I have not put much
work into Windows support yet. (at least for the `frontend`, other components
should be fine. )

## License
Currently, all of the source code written for the Medusa Project is licensed
under Version 2 of the GNU General Public License (GPLv2), without the "any
later version" clause.
Other resources are released under CC BY-SA 4.0.

Files should contain a disclaimer indicating their license. If not, (excluding
submodules) go through the chain of parent folders until you find the first
parent folder with a `LICENSE` file: that is the license of the file in
question.

## Folder Structure
```
/:                        - the root of the project, the parent folder of this
                            file
    docs                  - documentation for the Medusa Project
    medusa_software:      - source code for the Medusa Project
        barcelona         - a subproject of the Medusa Project to create a TUI
                            (Terminal User Interface)-based IDE (Integrated
                            Development Environment).
        berlin            - a subcomponent of the Medusa Project to create a
                            free (libre) GTK hex editor, eventually to be
                            incorporated into the full Medusa software
                            package/suite.
        frontend          - the default frontend for the Medusa Project
        libmedusa         - a library for controlling emulated and real-silicon
                            machines programmatically maintained by the Medusa
                            Project
        libxparse         - an executable parser maintained by the Medusa
                            Project
        london            - a subproject of the Medusa Project to create a
                            native, free (libre) Integrated Development
                            Environment (IDE)
        medusa_submodules - Git submodules for components maintained by the
                            Medusa Project (not currently in this repo, but in
                            case some components are moved outside of this
                            repository, this is where the submodules for said
                            components will reside)
        paris             - a subcomponent of the Medusa Project to develop the
                            client/server architecture that is intended to be
                            used in the project.
        rome              - a subcomponent of the Medusa Project to write a
                            modern C++ TUI framework based on ncurses.
        submodules        - Git submodules not maintained by the Medusa Project
        vienna            - a subcomponent/subproject of the Medusa Project to
                            develop a free (libre) decompiler for both native
                            code, and bytecode.
        work              - work in progress components / sideprojects for the
                            Medusa Project, such as a text editor
    res:                  - resources, such as GIMP project files, images, and
                            the like
        badges            - SVG files of badges
        defaults          - contains default/template files, such as Makefiles
        img:              - images
            src           - "source" files of images, (like XCFs for GIMP)
    tools:                - tools for the development of & general work on the
                            Medusa Project
        badges            - badge generation code
    wiki                  - git submodule for the Medusa Project Wiki
    www                   - source code for Medusa Project websites
```

## FAQ
### How do you pronounce Medusa?
![/məˈdusə/](/res/audio/medusa.ogg)

### How should I report an issue/bug I find?
File an issue on [the GitLab repository](https://git.medusa-re.org/Medusa).

### How can I contact the team?
The "team" just consists of me (spv) for now, so you can email me @
[spv@spv.sh](mailto:spv@spv.sh).

See [CONTACT.md](/CONTACT.md) for more details.

## Community
If you would like to join the Matrix room for Medusa, join
[#general:medusa-re.org](https://matrix.to/#/#general:medusa-re.org).

## Documentation
There is a variety of doxygen-based documentation for Medusa libraries and API's
available at [docs.medusa-re.org](https://docs.medusa-re.org), and a wiki is
available for the Medusa Project at
[wiki.medusa-re.org](https://wiki.medusa-re.org).

## Credits
```
spv               - project founding
Capstone Team     - Capstone
Unicorn Team      - Unicorn
Keystone Team     - Keystone
LIEF Project      - LIEF
QEMU              - QEMU
The GNOME Project - GTK
The GNOME Project - GTKMM? (i'm not sure if this is the case, please correct me
                            if The GNOME Project is not the principal
                            developer!)

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
- [The American Civil Liberties Union](https://www.aclu.org)
- [The Electronic Frontier Foundation](https://www.eff.org)
- More will be added to this list as I find charities I would like to
  support.

If, for some reason, you would still like to donate to me, here are some
cryptocurrency wallets you could donate to.

```
BTC: bc1qjg6jck6c08lqrxdgjnuj5m8c3v0zdrfh7rvjt5
ETH: 0x628dc9B9deBE999477c39F3054246Bd3A3372458
XMR: 8BzgGQbbBUybgYw2dEC5EhazQcKGyG6UL6A9bueuDT5Mjhuwo3H7Lg2jEkEEJcrNR7W2MtCKfoRkEBxi3JjztwHj1VwMV2u
XLM: GBKN2D7ZRBPQDW7GEQCT23ID6PVNZ43A224ULBZSP6G4JBNDEKY42J6C
```

## File License
This file is licensed under the terms of the CC BY-SA 4.0 license.