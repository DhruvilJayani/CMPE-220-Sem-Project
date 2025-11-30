# Software CPU – CMPE 220 Semester Project

This project implements a **software CPU simulator in C** with a custom 16-bit instruction set, assembler, and execution environment.

---
## Demo Video

[![Demo Video](https://img.youtube.com/vi/a9EEQqkkipE/0.jpg)](https://www.youtube.com/watch?v=a9EEQqkkipE)
---
## 👥 Team Members
- **Adityaraj Kaushik**  
- **Dhruvil Jayani**  
- **Shantanu Joshi**  
- **Varsha Chamakura**

---

## 🧩 Project Overview
The simulator models a complete CPU including:
- 16-bit instruction encoding and execution  
- Fetch–Decode–Execute cycle  
- Registers, ALU, Control Unit, and Memory subsystem  
- Memory-mapped I/O (Timer & UART)  
- Assembler and Encoder for custom assembly programs  
- Segmented memory model: **Text / Data / Heap / Stack**

Programs included:
- `hello.asm` – Hello World output  
- `fibonacci.asm` – Fibonacci Sequence  
- `timer_demo.asm` – Timer cycle demonstration  
- `factorial.asm` – Recursive Factorial  

---

## ⚙️ Architecture

### CPU Schematic
![CPU Architecture Diagram](docs/cpu_schematic.png)  
*Figure 1 – CPU Architecture showing Control Unit, ALU, Memory, Bus, Compiler, Encoder, and I/O System.*

### Key Modules
| Module | Purpose |
|---------|----------|
| **cpu.c / cpu.h** | CPU core – fetch/decode/execute loop |
| **control_unit.c / control_unit.h** | Instruction decoding & branch control |
| **alu.c / alu.h** | Arithmetic Logic Unit (ADD, SUB, MUL, CMP, AND, OR, XOR, etc.) |
| **memory.c / memory.h** | RAM simulation, read/write operations |
| **bus.c / bus.h** | Data transfer between CPU, Memory, and I/O |
| **io.c / io.h** | Memory-mapped I/O – UART and Timer |
| **compiler.c / compiler.h** | Assembler front-end for assembly source |
| **encoder.c / encoder.h** | Instruction encoder for binary opcodes |
| **program_layout.c / program_layout.h** | Memory segment definitions |
| **Makefile** | Build and clean targets |

---

## 🧮 Instruction Set Architecture (ISA)
Full ISA documentation → [`docs/ISA.md`](docs/ISA.md)

**Highlights**
- 16-bit instruction width  
- 8 General-Purpose Registers (R0–R7)  
- Flags: Zero (Z), Negative (N), Carry (C), Overflow (O), Halt (H)  
- Addressing Modes: Register / Immediate / Memory-Mapped I/O  
- Core Instructions: `HALT`, `MOV`, `LD`, `SW`, `ADD`, `SUB`, `MUL`, `CMP`, `J`, `BLE`, `JR`, `PUSH`, `POP`

---

## 🗺️ Memory Map
Full details → [`docs/MEMORY_MAP.md`](docs/MEMORY_MAP.md)

| Region | Address Range | Description |
|---------|---------------|-------------|
| **Text** | 0x0000–0x1FFF | Program instructions |
| **Data** | 0x2000–0x3FFF | Static data |
| **Heap** | 0x4000–0x4FFF | Dynamic storage |
| **Stack** | 0xF000–0xFFFF | Runtime stack |
| **I/O** | 0x8000–0x8002 | UART & Timer Registers |

---

## 🔄 Programs and Responsibilities
| Program | Author | Description |
|----------|---------|-------------|
| **Fibonacci Sequence** | **Adityaraj Kaushik** | Demonstrates arithmetic, branching, looping, and serves as the main demo program |
| **Timer Example** | **Dhruvil Jayani** | Shows Fetch–Compute–Store cycles and memory-mapped I/O |
| **Hello World** | **Shantanu Joshi** | Tests I/O operations and basic instruction flow |
| **Factorial (Recursive)** | **Varsha Chamakura** | Demonstrates recursion and stack operations |

---

## 🧠 How It Works
1. **Assembly Phase** – Assembler (`compiler.c`) parses `.asm` files.  
2. **Encoding Phase** – Encoder (`encoder.c`) converts to 16-bit machine code (`.txt`).  
3. **Load Phase** – CPU initializes memory segments and loads program.  
4. **Execute Phase** – Fetch–Decode–Execute loop runs until `HALT`.  
5. **I/O Handling** – Memory-mapped Timer and UART simulate device interaction.

---

## 🧰 Building and Running

### Prerequisites
- GCC or Clang  
- `make` utility  
- Linux / macOS / WSL environment

### To Run
```bash
make clean
make
./cpu_sim timer_demo
./cpu_sim fibonacci
./cpu_sim hello
