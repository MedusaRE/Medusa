# Branch Names
<!---
================================================================================
THIS FILE IS A WORK IN PROGRESS
================================================================================
  --->
In general, `git` branches should be named as follows:

```
master                 ~ master
  child                ~ child.master
  other-child          ~ other-child.child.master
    grandchild         ~ grandchild.other-achild.child.master
      great-grandchild ~ great-grandchild.other-child.child.master
  etc.
```

The reasoning for this is it allows you to easily tell the history of a branch.

## File License
This file is licensed under the terms of the CC BY-SA 4.0 license.
