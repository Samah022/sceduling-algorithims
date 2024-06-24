# Operating System Scheduling Algorithms 🖥️

## Description 🔖

This project focuses on implementing various scheduling algorithms in operating systems. The repository contains C code implementations of key scheduling algorithms used in operating systems. These algorithms are critical for efficiently managing processes in computer systems, ensuring fair resource allocation and optimal performance.

## Algorithms Implemented 🛠️

The implemented algorithms include:
- **FCFS (First-Come, First-Served)**
- **RR (Round Robin)**
- **MLQ (Multi-Level Queue)**
  - Two-level MLQ with RR and FCFS
  - Three-level MLQ with RR1, RR2, and FCFS

## Files 📑

- **main.c**: Contains the main program which executes and tests the scheduling algorithms.
- **output.txt**: Output file where the results of scheduling algorithms are saved.
- **test1.txt**: Input file containing process details and quantum times.

## Usage 💡

To use this project, you can either enter process details interactively or use a file input method (`test1.txt`). The output of the scheduling algorithms is saved in `output.txt`.

## Compilation ⚙️

To compile the program, use any standard C compiler. For example, with GCC on Unix/Linux systems:

```bash
gcc main.c -o scheduler
```

## Contributors ✍️

- Abeer Jelani
- Salwa Shama
- Samah Shama
- Shatha Faraj
- Leen Khalil
