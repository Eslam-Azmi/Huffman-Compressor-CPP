# Huffman-Compressor-CPP
A C++ CLI tool for file compression using Huffman Coding. Features frequency analysis and bit-level data optimization.

- [x] **Sprint 1: Frequency Analysis** — Reads text files and calculates character distribution.
- [x] **Sprint 2: Huffman Tree Construction** — Built a greedy-algorithm tree using Min-Heaps.
- [x] **Sprint 3: Encoding & Compression** — **[In Progress]**
    - [x] Recursive bit-code generation (DFS traversal).
    - [x] Bit-packing and binary file output.
    - [x] Custom Binary Header implementation (Portability).
- [x] **Sprint 4: Decompression Logic** — Rebuilding the original file.

## 🚀 Current Milestone: Project Complete (Stage 4)
The engine is now a full-cycle Huffman compressor and decompressor. It can compress any text file into a packed `.huff` format and reconstruct it bit-for-bit. By implementing a **Node ID stabilizer**, the tool ensures 100% data integrity, solving the common issue of inconsistent tree reconstruction during decompression.

## 📊 Technical Highlights
* **Binary I/O:** Utilizes `ios::binary` and `ofstream::put` for raw byte manipulation, ensuring cross-platform compatibility and preventing character translation issues.
* **Deterministic Tree Construction:** Employs a unique ID-tracking system during tree building. This ensures the Huffman tree is reconstructed identically in both modes, even when multiple characters share the same frequency.
* **Efficient Bit-Packing:** Groups bit-strings into `unsigned char` bytes to achieve true physical compression. It accurately ignores trailing padding by storing and checking a `totalBits` counter.
* **Portable Headers:** Stores metadata (character maps and frequency counts) within the `.huff` file, allowing it to be decompressed without needing the original source file.

---.

## 🛠️ How to Run

### 1. Build the Tool
```bash
g++ main.cpp -o huffman_tool