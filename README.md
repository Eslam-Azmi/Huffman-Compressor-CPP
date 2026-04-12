# Huffman-Compressor-CPP
A C++ CLI tool for file compression using Huffman Coding. Features frequency analysis and bit-level data optimization.

- [x] **Sprint 1: Frequency Analysis** — Reads text files and calculates character distribution.
- [x] **Sprint 2: Huffman Tree Construction** — Built a greedy-algorithm tree using Min-Heaps.
- [ ] **Sprint 3: Encoding & Compression** — **[In Progress]**
    - [x] Recursive bit-code generation (DFS traversal).
    - [ ] Bit-packing and binary file output.
- [ ] **Sprint 4: Decompression Logic** — Rebuilding the original file.

## 🚀 Current Milestone: Stage 3 Complete
The compressor now features a fully functional **Huffman Engine**. It can take any source text, analyze character weight, and generate a prefix-free binary dictionary. This marks the completion of the core logical "brain" of the compression process.

## 🛠️ How to Run (Current Version)
1. **Compile:** `g++ main.cpp -o compressor`
2. **Run:** `./compressor`
3. **Input:** Enter the filename (e.g., `count.txt`) to view the character distribution and the generated Huffman codes.