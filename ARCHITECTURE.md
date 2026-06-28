# PROJECT ARCHITECTURE / DESIGN INSTRUCTION
## PROJECT DESIGN
MiniLang follows a modular architecture in which each component is responsible for a specific stage of command processing. The architecture is designed to ensure maintainability, scalability, and ease of future enhancements.
***
**Architecture Overview**
 ```
                   +----------------------+
                   |      User Input      |
                   +----------+-----------+
                              |
                              v
                   +----------------------+
                   |  Lexer (Tokenizer)   |
                   +----------+-----------+
                              |
                              v
                   +----------------------+
                   |        Parser        |
                   +----------+-----------+
                              |
                              v
                   +----------------------+
                   |   Command Queue      |
                   +----------+-----------+
                              |
                              v
                   +----------------------+
                   | Interpreter / Engine |
                   +----------+-----------+
                              |
                +-------------+-------------+
                |                           |
                v                           v
      +-------------------+      +-------------------+
      | Variable Manager  |      | Error Handling    |
      +-------------------+      +-------------------+
                |
                v
      +-------------------+
      |  Console Output   |
      +-------------------+
```
***
**Module Description**  
- **User Interface**  
The command-line interface acts as the interaction layer between the user and the interpreter. It accepts commands entered by the user and forwards them for processing.  
- **Lexer (Tokenizer)**  
The Lexer reads the input command and divides it into meaningful tokens such as keywords, identifiers, operators, literals, and symbols. These tokens are then passed to the parser for syntax validation.  
- **Parser**  
The Parser verifies whether the generated tokens follow the predefined grammar of MiniLang. If the syntax is valid, it identifies the corresponding command and prepares it for execution.  
- **Command Queue**  
Validated commands are stored temporarily in a command queue. This allows commands to be organized and executed sequentially, improving execution flow and modularity.  
- **Interpreter / Execution Engine**  
The interpreter serves as the core component of MiniLang. It executes commands by invoking the required operations such as variable creation, updating, deletion, arithmetic computation, comparison, and string manipulation.  
- **Variable Management Module**  
This module maintains a symbol table containing all user-defined variables along with their data types and current values. It ensures efficient retrieval, modification, and deletion of variables during execution.  
- **Error Handling Module**  
The error handling module detects lexical, syntactic, and runtime errors such as invalid commands, undefined variables, incorrect data types, and arithmetic exceptions. It generates informative error messages to assist users in correcting their input.  
***
## Design Principles
The MiniLang interpreter is designed using Object-Oriented Programming principles to improve modularity and maintainability.  
- **Abstraction** is used to hide implementation details behind well-defined interfaces.
- **Inheritance** enables specialized command classes to reuse common functionality.
- **Polymorphism** allows different command objects to be executed through a common interface.
- **Encapsulation** protects internal data structures and ensures controlled access to interpreter components.  
This modular architecture simplifies maintenance, promotes code reusability, and provides a strong foundation for future enhancements such as loops, functions, arrays, Abstract Syntax Trees (AST), and file-based program execution.
***