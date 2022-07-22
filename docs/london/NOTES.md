# Notes

Sadly, from what I can tell, GTK(mm) does not provide a way to add a signal to
run code when text is added to a TextBuffer *that specifies where/what text was
added*. You can run a callback/signal when text has been added to the
TextBuffer, but it will not inform your code of where/what text added.

## File License
This file is licensed under the terms of the CC BY-SA 4.0 license.