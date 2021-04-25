# rust-jit

![actions-badge](https://github.com/oneturkmen/rust-jit/workflows/rust-jit-ci/badge.svg)

An attempt to dynamically compile a subset of Rust.

:warning: Status: **frozen** until further notice (as of April 2021).

## Usage

Build the build system first (sounds funny):

```bash
cd src && cmake .
```

Then, run the build system (make):
```bash
make .
```

Finally, run the binary located in the `/bin` folder:

```bash
./src/bin/rustjit
```

This will open up an interpreter. Try typing the following line `let x = 2 + 2;` and you should see the following output (debug):

```
> let x = 2 + 5;
         Let | let | 1 | 
  Identifier | x | 1 | 
       Equal | = | 1 | 
      Number | 2 | 1 | 
        Plus | + | 1 | 
      Number | 5 | 1 | 
   Semicolon | ; | 1 | 
# of stmts: 1
visitVarDeclStmt()
Accepting expression in evaluate()
In BinExpr::accept(Object *)
Accepting expression in evaluate()
In Literal::accept(Object *)
visitLiteral()
Accepting expression in evaluate()
In Literal::accept(Object *)
visitLiteral()
```

## Features

Currently, supports only a subset of Rust - basic grammar, such as logic with primitives, variable assignment, reference and mutability checks. I would love to get into implementation of more complex concepts, such as generics, smart pointers, and lifetimes at some point.

