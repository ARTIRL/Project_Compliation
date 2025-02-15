
# Lexical, Semantic, Syntaxic Parser & Translator for Pascal-like Code

## Description

This project is a **Lexical, Semantic, Syntaxic Parser** and **Code Translator** for Pascal-like programming languages. It is written in **C** and designed to process code written in a syntax similar to Pascal, parse it, perform semantic checks, generate an intermediate code representation, and produce a detailed output of the parsing process.

The program translates the provided Pascal-like code into an intermediary representation, allowing you to see the steps of lexical analysis, semantic analysis, and syntax parsing.

## Features

- **Lexical Analysis**: Tokenizes the input code, breaking it down into basic language elements (keywords, operators, identifiers, etc.).
- **Semantic Analysis**: Checks for logical errors or inconsistencies in the code.
- **Syntax Analysis**: Verifies the structure of the code according to the defined grammar of the Pascal-like language.
- **Intermediate Code Generation**: Produces an intermediate representation (`codeInterm`) from the input code.
- **Comprehensive Output**: Provides a full output of parsing, including the lexical, semantic, and syntax analysis stages.

## Requirements

- **C Compiler** (e.g., GCC)
- **Pascal-like Source Code** (filename: `pascallikecoded`)

## Installation

1. Clone this repository or download the source code files.
   
   ```bash
   git clone https://github.com/ARTIRL/Project_Compliation
   ```

2. Make sure you have a working C compiler (e.g., GCC) installed on your system.

3. Compile the program using the C compiler.

   ```bash
   gcc -o parser parser.c
   ```

## Usage

To run the parser and get the detailed output, follow these steps:

1. Ensure you have a **Pascal-like source file** named `pascallikecoded` in the same directory as the program.

2. Run the compiled program with the following command:

   ```bash
   ./parser pascallikecoded
   ```

3. The program will generate the following:

   - **Parsing Output**: A step-by-step breakdown of the lexical, semantic, and syntax analysis.
   - **Intermediate Code**: The program will create an intermediate code file (`codeInterm`), which represents the internal structure of the code.

## Example

### Input (pascallikecoded)

```pascal
program Hello;
begin
   writeln('Hello, World!');
end.
```

### Output

The program will print out details of the following:

- Lexical analysis (tokens detected)
- Syntax parsing (grammar validation)
- Semantic analysis (error checking)
- Intermediate code in `codeInterm`

## Contributing

Feel free to fork the repository, open issues, or submit pull requests. If you would like to improve or expand the functionality of the parser or add support for more languages, please submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
