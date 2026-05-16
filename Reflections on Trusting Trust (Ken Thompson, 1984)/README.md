## Introduction
This project is a toy implementation of [Ken Thompson's paper "Reflections on Trusting Trust" [1]](https://doi.org/10.1145/358198.358210).

`quine.c` is a simple self-reproducing program. It illustrates the self-reproduction idea that `infected_compiler.c` later uses. The source string contains a `%s` placeholder that prints the string itself. To avoid the escaping of quotes, newlines and other special characters inside the string, `%c` placeholders populated with their ASCII integer values (e.g., `34` for `"` and `10` for a newline) are used. I learned how to write such programs from [this blog [2]](https://firexfly.com/quines/).
`check_password.c` is a toy program that we will backdoor as a stand-in for the UNIX `login` command, as in the paper.
`clean_compiler.c` is a wrapper around `gcc`. We will alter it rather than modifying `gcc` internals.
`infected_compiler.c` is the malicious compiler. It can:
- backdoor `check_password.c` by adding `ken` as a valid password
- modify `clean_compiler.c` by replacing the clean source code with its own malicious logic (self-replication)
- act as a normal wrapper around `gcc` for any other files

_Note: To avoid writing intermediate malicious source files to disk, this implementation pipes the generated altered source code into `gcc` via standard input._

## Reproducing the results
First, let us confirm that the clean `check_password` binary does not accept `ken` as a valid password:
```
$ gcc check_password.c -o check_password
$ ./check_password
Enter password: ken
Access denied!
```

Now, compile `infected_compiler.c` and use its binary to compile `clean_compiler.c`:
```
$ gcc infected_compiler.c -o infected_compiler
$ ./infected_compiler clean_compiler.c clean_compiler
```

Let us confirm that the `clean_compiler` binary is now compromised by compiling `check_password.c` with it and checking if the resulting binary accepts `ken` as a valid password:
```
$ ./clean_compiler check_password.c infected_check_password
$ ./infected_check_password
Enter password: ken
Access granted!
```

## Conclusion
You can delete `infected_compiler.c`. If you audit `clean_compiler.c` and `check_password.c`, you will find no malicious code. Yet, the `clean_compiler` binary is compromised and will reproduce the backdoor whenever it recompiles those files. This shows the limits of source-level verification when the build toolchain itself is part of the attack.

## References
1. Ken Thompson, "Reflections on Trusting Trust", Communications of the ACM, 27(8), 761–763, 1984.  
DOI: [10.1145/358198.358210](https://doi.org/10.1145/358198.358210)
2. firexfly, "Writing programs that write themselves".
Link: [firexfly.com/quines/](https://firexfly.com/quines/)