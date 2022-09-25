# Commit Messages

The format for commit messages should roughly look like this:
`(component): (short description of the commit)`.

Don't make super big monster commits. (I'm (spv) guilty of that, lol. )

For example, if you fixed a bug in the Medusa frontend, an appropriate commit
message could be:
`frontend: fix buffer overflow in medusa_window constructor`

An inappropriate message could be:
`fix buffer overflow shit in frontend`

While it is discouraged to modify multiple components with one commit, sometimes
that's necessary. If you change an API, you may need to update usage of said API
in the same commit, which may span many components. If so, you can write
something like this:
`(component1),(component2),etc: (short description of the commit)`.

As a proper example:
`ms/frontend,ms/berlin,ms/london,ms/paris: fix typo in comment`

If you changed an API, use this format:
`(API);(component1),(component2),etc: (short description of the commit)`.

For example:
`ms/libmedusa;ms/frontend,docs: use long instead of int for mem addr arg`

Ideally, if you modified something like an API (say, libmedusa), put that
component as the first item in the list, followed by a semi-colon.

## Abbreviations
```
ms    - medusa_software
msj   - MedusaStyleJava
```

So, you could write your commit message as:
`ms/frontend: fix buffer overflow in medusa_window constructor`

## File License
This file is licensed under the terms of the CC BY-SA 4.0 license.
