# launcher
a simple Windows app for launching other processes

## how to
1. drop the EXE in your `C:\Users\<user>` folder.
2. create a `shortcuts.txt` next to the EXE.  Each line is of the form `<alias> <command>`.
3. you can now run shortcuts with `Windows+R`, then typing `launcher <alias>`.

## technicals
1. launcher remains running until the child process is completed.  It is intended for short-running processes.
2. if a child process returns an error, then launcher will wait for user intervention before exiting.  This preserves child process console output.
