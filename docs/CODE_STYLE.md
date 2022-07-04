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