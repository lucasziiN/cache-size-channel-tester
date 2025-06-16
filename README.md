# LLC Timing-Based Side-Channel Attack – COMPX304 Assignment 4

A low-level side-channel timing attack written in C to **infer the size of the Last Level Cache (LLC)** on a Linux system. This project simulates methods similar to those exploited in Spectre and Meltdown vulnerabilities.

Developed as part of COMPX304 – Advanced Networking & Cyber Security at the University of Waikato (2025).

---

## 🔍 Objective

To determine the size of the system's LLC by:
- Allocating a large array
- Probing memory with controlled patterns
- Measuring access latency to detect cache hits vs misses
- Inferring the cache boundary based on timing trends

---

## 🛠 Technology Stack

- **Language**: C (low-level access, pointer-based memory probing)
- **OS**: Linux (tested on Ubuntu/Debian systems)
- **Tools Used**: `clock_gettime()`, `lscpu`, `gcc`, `make`

---

## 📂 Project Structure
llc-probe-timing-attack/
├── main.c # Core program logic
├── results/ # Output CSVs with timing data
├── scripts/ # Bash scripts to compile and run
├── README.md
└── Makefile

--- 

## 📊 Experimental Design
- Uses stride-based probing over a large array
- Repeated accesses to measure average read latency
- Measures how latency increases when array exceeds cache size
- Verifies results against lscpu reported LLC

---

## 🧠 Key Concepts
- Cache Lines: Assumed to be 64 bytes (or 128 on M1)
- LLC: L3 cache on Intel/AMD CPUs, largest shared cache
- Side Channels: Information leakage through timing rather than software flaws

## 📄 Report Summary
- The report discusses:
    - Cache behavior and CPU architecture
    - Design of the timing probe
    - Experimental setup and control parameters
    - Accuracy and discrepancies with lscpu values

---

## 👨‍🎓 Author
Lucas Oda
Bachelor of Science (Computer Science)
University of Waikato – COMPX304 (2025)



