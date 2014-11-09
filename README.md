# Shared Objects

This is a very simple demo to show how an application can use shared objects.

## Build flags
### Compilation Flags
* **-Wall**: This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.
* **-Werror**: Make all warnings into errors.
* **-fPIC**: If supported for the target machine, emit position-independent code, suitable for dynamic linking and avoiding any limit on the size of the global offset table. This flag is not necessary for x86_64 or i386 machines.

### Shared Object Flags
* **-shared**: Produce a shared object which can then be linked with other objects to form an executable.
* **-fvisibility=hidden**: Set the default ELF image symbol visibility to hidden.
* **-fvisibility-inlines-hidden**: This switch declares that the user does not attempt to compare pointers to inline functions or methods where the addresses of the two functions are taken in different shared objects. It is not really required for this program but is good to know about in general.
* **-s**: Remove all symbol table and relocation information from the executable.

### Linkage Flags
* **-ldl**: Search the dl library (dynamic linking loader library) when linking.

