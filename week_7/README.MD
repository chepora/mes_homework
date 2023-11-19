# Week 7 Assignment

This week we each answer two interview questions.

## Interview Questions

The two questions

- What is a reentrant function?
- What kind of loop is better: Count up from zero or count down to zero? Why?

### What is a reentrant function?

A reentrant function keeps score where it is at every moment while it is executed ans never changes its code dependet on context. This is essential for being threadsafe.
If the execution of a function is interrupted by a task change a non-reentrant function might loose its context.

Let us look at two funtions from `string.h`: [`strtok` and `strtok_s`](https://devdocs.io/c/string/byte/strtok)

The first is `strtok`, which parses a string into a sequence of token **wihtout** saving its internal state.
```c
char *strtok( char *restrict str, const char *restrict delim );
```
This function is non-reentrant and not threadsafe.

Therefore since C11 there is `strtok_s`, which keeps track how many chars there are left to check and saves its internal state to `saveptr`
```c
char *strtok_s(char *restrict str, rsize_t *restrict strmax,
     const char *restrict delim, char **restrict saveptr);
```
This function is reentrant and can be threadsafe.

### What kind of loop is better: Count up from zero or count down to zero? Why?

One can argue that on assembler level a comparison to zero cost less than a comparison to an number bigger zero.
But, when most of us write code, we do not write on assembler level. We will be using a compiler which has gotten better and better at optimizing our code.
I would therefore argue, that the kind of loop which is easier to read and which makes its connection clear, is the better loop.


