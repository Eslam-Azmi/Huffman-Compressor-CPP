# Huffman-Compressor-CPP
A C++ CLI tool for file compression using Huffman Coding. Features frequency analysis and bit-level data optimization.

- [x] **Sprint 1: Frequency Analysis** — Reads text files and calculates character distribution.
- [x] **Sprint 2: Huffman Tree Construction** — Built a greedy-algorithm tree using Min-Heaps.
- [x] **Sprint 3: Encoding & Compression** — **[In Progress]**
    - [x] Recursive bit-code generation (DFS traversal).
    - [x] Bit-packing and binary file output.
    - [x] Custom Binary Header implementation (Portability).
- [ ] **Sprint 4: Decompression Logic** — Rebuilding the original file.

## 🚀 Current Milestone: Stage 3 Complete
The engine is now a fully functional binary compressor. It converts source text into a packed `.huff` file. By implementing a structured header (storing character maps and bit counts), the file is now self-contained and ready for the decompression stage.

## 📊 Technical Highlights
* **Binary I/O:** Utilizes `ios::binary` and `ofstream::put` for raw byte manipulation.
* **Efficient Bit-Packing:** Groups bit-strings into `unsigned char` bytes to achieve true physical compression.
* **Deterministic Headers:** Stores a metadata map to ensure the Huffman tree can be reconstructed during decompression.

## 🛠️ How to Run (Current Version)
1. **Compile:** `g++ main.cpp -o compressor`
2. **Run:** `./compressor`
3. **Process:** Enter the filename (e.g., `test.txt`). The program will generate `compressed.huff` in the current directory.