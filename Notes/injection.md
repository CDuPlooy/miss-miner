# Injection Notes

* After inserting the shellcode AV does not seem to worry about it.
  At this point the execution flow has not been altered. This will be done by hand for now.
* The injectShellcode function will be made to return a structure which contains the offset of the
  injected code as well as whether or not injection was successful.
