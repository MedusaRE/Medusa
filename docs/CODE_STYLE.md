# Code Style
Medusa is written mostly in C++, and this document will outline some suggestions
on how to style the code you write.

First of all, put braces on the same line as what the braces are for.

Write:
```c++
void example(int a) {
    printf("Hello, world!\n");
}
```
Instead of:
```c++
void example(int a)
{
    printf("Hello, world!\n");
}
```

Put spaces after parenthesis (like function definitions) and builtin `if`-type keywords.

Write:
```c++
void example(int a) {
    if (a == 0) {
        printf("abc\n");
    }
}
```
Instead of:
```c++
void example(int a){
    if(a == 0){
        printf ("abc\n");
    }
}
```

Use hard-tabs (\t), not soft-tabs. Set tab-stops at 4. An exception is made for
documentation files, where soft-tabs (spaces) are to be used. The reason for
this is that most web-based Git clients (GitHub, GitLab, etc) default tab-stops
at 8, and sometimes do not have the ability to change said default. In a case
like this, it's preferable to make the documentation display correctly in those
circumstances. I'm (spv) more accepting of hard-tabs in actual source code, as
not much editing is done within web-based Git clients, and you *can* change the
tab stops usually. Since the *default* is 8, and not everyone changes it, making
the documentation look correct matters more to me than source code in that case.

Use snake_case for variables, class members, and such. Use PascalCase for class
names.

Write:
```c++
class ExampleClass {
    ...
    int this_is_a_variable;
    ...
};
```

Instead of:
```c++
class example_class {
    ...
    int thisIsAVariable;
    ...
}
```

Indent access specifiers like `public`, `protected`, and `private` 1 tab-stop
past `class`.

Write:
```c++
namespace example {
    class ExampleClass {
        public:
            int variable;
        private:
            int a_second_variable;
    };
}
```

Instead of this, :
```c++
namespace example {
    class ExampleClass {
    public:
        ...
    };
}
```

Or this:
```c++
namespace example {
    class ExampleClass {
public:
        ...
    }
}
```

For comments, line up the `*`'s of `/*` and `*/`.

Write this:
```
/*
 ...
 */
```

Instead of this:
```
/*
 ...
*/
```

As well, start each line of a multi-line comment with `[space]*`.

Write this:
```
/*
 *
 */
```

Instead of this:
```
/*

 */
```

<!--
Finally with comments, keep lines under 80 chars whenever possible, and after
each `*` to start a line, place 2 spaces.

Write this:
```
/*
 *  Hello, world! I see you're reading this document. Oh no this line is going
 *  to wrap! Oh ok, we're fine. Goodbye!
 */
```

Instead of this:
```
/*
 * Hello, world! I see you're reading this document. Oh no this line is going to
 * wrap! Oh ok, we're fine. Goodbye!
 */
 ```

(i'd like to do it this way, but sadly clang-format doesn't support this from
what i can tell)

-->

Generally, C++ code would look something like this:
```c++
#include <cstdint>
#include <cstdlib>
#include <cstdio>

int main(int   argc,
         char *argv[]) {
    char     *buf = malloc(0x4000);
    int       ival;
    uint32_t  val;

    printf("%p %d 0x%08x\n",
           buf,
           ival,
           val);
    
    if (val == 0) {
        whatever(val);
    } else if (val == 1) {
        whatever2(val);
    } else if (val == 2) {
        whatever3(val);
    } else {
        whatever4(val);
    }

    libmedusa::ARMv7Machine armv7_machine;
    libmedusa::reg_t        reg;

    reg.reg_description = "pc";
    reg.reg_name = "pc";
    reg.reg_id = 0xf;
    reg.reg_value = 0x1;        // |1 means THUMB on ARMv7

    armv7_machine.set_register(reg);

    return 0;
}
```

## File License
This file is licensed under the terms of the CC BY-SA 4.0 license.