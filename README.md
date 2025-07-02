# 🚀 BanglaScript Compiler (C++ & Web UI)

A complete compiler for the **BanglaScript** programming language, featuring all major compiler phases and a modern web interface for interactive use and demonstration.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Folder Structure](#folder-structure)
- [Setup & Installation](#setup--installation)
- [How to Run](#how-to-run)
- [Demo Code](#demo-code)
- [Screenshots](#screenshots)
- [Credits](#credits)

---

## Overview

**BanglaScript Compiler** is a university project that demonstrates all phases of compilation for a custom language inspired by Bengali-English keywords. It includes a C++ backend for compilation and a Node.js/Tailwind web UI for interactive use.

---

## Features

- **Full Compiler Pipeline:** Lexical analysis, parsing, semantic analysis, symbol table, and code generation.
- **Modern Web UI:** Beautiful, responsive interface with Tailwind CSS.
- **Phase-by-Phase Output:** See tokens, AST, symbol table, semantic results, and generated code.
- **Demo Code Buttons:** Instantly load and test 8+ BanglaScript examples.
- **Dark/Light Mode:** Toggle for comfortable viewing.
- **Copy/Download Output:** Easily share or save results.
- **Error Highlighting:** Clear, readable error messages.

---

## Tech Stack

- **C++17:** Compiler backend (all phases)
- **Node.js + Express:** Web server to run the compiler
- **HTML + Tailwind CSS:** Modern, responsive frontend
- **JavaScript:** Frontend interactivity

---

## Folder Structure

```
Compiler peoject rivision/
├── banglascript_compiler.exe   # Compiled C++ compiler
├── main.cpp, lexer.cpp, ...    # C++ source files
├── index.html                  # Web UI (root)
├── script.js                   # Web UI JS (root)
├── server.js                   # Node.js backend
├── package.json                # Node.js dependencies
├── README.md                   # This file
└── ...
```

---

## Setup & Installation

### 1. **Compile the C++ Compiler**
Make sure you have a C++17 compiler (e.g., g++):
```sh
g++ -std=c++17 -o banglascript_compiler main.cpp lexer.cpp parser.cpp symbol_table.cpp semantic.cpp codegen.cpp
```

### 2. **Install Node.js Dependencies**
Make sure you have Node.js installed.  
In your project folder:
```sh
npm install express
```

---

## How to Run

### **Web UI**
1. **Start the server:**
   ```sh
   node server.js
   # or
   npm start
   ```
2. **Open your browser:**
   [http://localhost:3000](http://localhost:3000)
3. **Enter BanglaScript code, use demo buttons, and see output!**

### **Command Line (CLI)**
1. Run the compiler directly:
   ```sh
   .\banglascript_compiler.exe
   ```
2. Enter code (end with `#` on a new line) and see all phases in the terminal.

---

## Demo Code

Try these in the web UI or CLI:

**Variables:**
```banglascript
dhori a = 5;
dhori b = 10;
dekhao(a);
dekhao(b);
```

**Arithmetic:**
```banglascript
dhori x = 7;
dhori y = 3;
dhori sum = x + y;
dhori mul = x * y;
dekhao(sum);
dekhao(mul);
```

**Assignment:**
```banglascript
dhori n = 1;
n = n + 9;
dekhao(n);
```

**If (jodi):**
```banglascript
dhori age = 18;
jodi (age >= 18) {
  dekhao("Adult");
}
```

**Loop (jotokkhon):**
```banglascript
dhori i = 1;
jotokkhon (i <= 3) {
  dekhao(i);
  i = i + 1;
}
```

**String:**
```banglascript
dhori name = "BanglaScript";
dekhao(name);
```

**Error Example:**
```banglascript
x = 5;
dekhao(x); // Error: x not declared
```

---

## Screenshots

> Add screenshots of your web UI and output here for your report or submission!

---

## Credits

- **Project by:** [Your Name], [Your University]
- **Supervisor:** [Instructor Name]
- **Inspired by:** BanglaScript, C/C++ compilers, and modern web design.

---

**🎓 Perfect for University Compiler Design Course!** 