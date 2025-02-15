Pascal-Like Compiler in C

📌 Project Overview

This project is a compiler for a Pascal-like language, implemented in C. It was developed as part of a class project .The compiler performs the following tasks within a single C program:

Lexical Analysis

Syntax Analysis

Semantic Analysis

Code Translation

🚀 Features

Tokenization of Pascal-like code.

Parsing and syntax validation.

Semantic checks for variable declarations, type checking, and scope validation.

Translation of Pascal-like code to an intermediate or target language.

Error handling with meaningful messages.

🛠️ Installation & Usage

Prerequisites

Ensure you have a C compiler installed, such as GCC.

Compilation

gcc -o compiler compiler.c -lm

Running the Compiler

./compiler pascalikecoded

Example Input (Pascal-like Code)

program Example;
begin
    writeln('Hello, World!');
end.

Example Output

Parsing successful!
Generating translated code...
Output stored in codeInterm.

📂 Project Structure

├── compiler.c
├── pascalikecoded
├── codeInterm
├── README.md

📌 Future Improvements

Support for more Pascal constructs.

Optimization in generated code.

Better error reporting with precise locations.

GUI or web interface for easier usage.

📜 License

This project is for educational purposes. Feel free to use or modify it.

✨ Acknowledgments

Special thanks to my professor and classmates for their guidance and feedback throughout the project.

