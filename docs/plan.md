Step-by-Step Plan
1. Define the Grammar: Define the grammar of the language you want to parse. This could be a subset of JavaScript, a custom scripting language, or any other language.
  * for loop:
    ```
    for node in graph {
      doSomething(node);
    }
    ```
2. Lexical Analysis: Write a lexer to tokenize the input script. Tokens are the basic building blocks like keywords, identifiers, operators, etc.
3. Syntax Analysis: Write a parser to generate an Abstract Syntax Tree (AST) from the tokens. The AST represents the hierarchical structure of the source code.
4. Execution Engine: Implement an execution engine that traverses the graph and executes the script. This step will directly turn the code into machine code.

---
Please check: https://chatgpt.com/c/04f5c9ba-f21e-428b-baff-64afddfd085a
