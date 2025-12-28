# 🚀 SIMD Optimization

> *Harnessing the power of SSE intrinsics for blazing-fast computations* ⚡

---

## 📋 Project Overview

This project is a comprehensive exploration of **SIMD (Single Instruction, Multiple Data)** programming using Intel SSE intrinsics and x86-64 assembly. It demonstrates how low-level optimizations can dramatically improve performance for common computational tasks.

The project consists of **four distinct parts**, each showcasing different aspects of SIMD programming and optimization techniques.

---

## 🔧 Part 1: Assembly Decoder

**File:** `decode.c` (decoded from assembly)

### 🎯 Objective
Reverse-engineer an assembly function and implement it in C.

### 📝 Implementation
```c
long decode_c_version(long x, long y, long z);
```

This function performs a series of arithmetic operations:
- Subtracts `z` from `y`
- Multiplies the result by `x`
- Applies a conditional operation based on parity (even/odd check)
- Performs XOR operation to produce the final result

### 💡 Key Concepts
Understanding how high-level C operations translate to assembly instructions:
- Arithmetic operations
- Conditional expressions
- Bitwise operations (XOR)
- Arithmetic shifts

---

## 🧮 Part 2: Complex Formula Computation

**Files:** `formula1.c`, `formulas.h`

### 🎯 Objective
Implement a mathematically intensive formula using **SSE intrinsics** for parallel processing.

### 📐 The Formula
```
result = √(1 + ∛(Σ√xᵢ) / Π(xᵢ² + 1))
```

### ⚡ Optimization Strategy
- **SSE1** intrinsics for square root operations (`_mm_sqrt_ps`)
- **SSE3** intrinsics for horizontal add operations (`_mm_hadd_ps`)
- Process **4 floats simultaneously** using 128-bit XMM registers
- Handle remaining elements that don't fit in complete SIMD chunks

### 🎪 Helper Functions

#### `sumFloats(__m128 a)`
Horizontally sums 4 floats in a register using `_mm_hadd_ps`:
```c
float sumFloats(const __m128 a) {
    const __m128 middleStep = _mm_hadd_ps(a, a);
    const __m128 resultRegister = _mm_hadd_ps(middleStep, middleStep);
    return _mm_cvtss_f32(resultRegister);
}
```

#### `mulFloats(__m128 a)`
Computes the product of 4 floats using clever shuffle operations:
```c
float mulFloats(const __m128 a) {
    const __m128 secondStep = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));
    const __m128 thirdStep = _mm_mul_ps(a, secondStep);
    const __m128 fourthStep = _mm_shuffle_ps(thirdStep, thirdStep, _MM_SHUFFLE(3, 0, 1, 2));
    const __m128 result = _mm_mul_ps(thirdStep, fourthStep);
    return _mm_cvtss_f32(result);
}
```

### 🌟 Performance Benefits
By processing 4 floats at once, this implementation achieves approximately **4x speedup** compared to scalar code! 🏃‍♂️💨

### 🔄 Algorithm Flow
1. Load 4 floats into XMM register
2. Compute square roots using `_mm_sqrt_ps`
3. Accumulate sum of square roots
4. Compute squares using `_mm_mul_ps`
5. Add 1 to each squared value
6. Accumulate product
7. Apply final formula with cube root and square root

---

## 📏 Part 3: Hamming Distance Calculator

**File:** `hamming_distance.c`

### 🎯 Objective
Calculate the Hamming distance between two 256-character strings using **SSE2 and SSE4.1** intrinsics.

### 🔍 What is Hamming Distance?
The number of positions at which corresponding characters differ between two strings.

### ⚙️ Implementation Details
- **SSE2** for byte-wise comparison (`_mm_cmpeq_epi8`)
- **SSE4.1** for extracting results (`_mm_extract_epi16`)
- Processes **16 bytes per iteration** (16 iterations total for 256 bytes)
- Uses `_mm_sad_epu8` for efficient counting of matches

### 🎨 Algorithm Flow
1. Load 16 bytes from each string into XMM registers using `_mm_loadu_si128`
2. Compare bytes using `_mm_cmpeq_epi8` (returns 0xFF for match, 0x00 for mismatch)
3. Sum matches using `_mm_sad_epu8` (Sum of Absolute Differences)
4. Extract results from lower and upper 64 bits using `_mm_extract_epi16`
5. Normalize by dividing by 0xFF
6. Calculate differences (16 - matches) and accumulate

### 📊 Efficiency
Compares **16 characters in parallel**, dramatically reducing loop overhead! 📈

### 🔧 Helper Functions
- `local_min(int a, int b)` - Returns minimum of two integers
- `local_abs(int a)` - Returns absolute value of an integer

---

## 📐 Part 4: Optimized `strlen` Implementation

**File:** `strlen_sse42.s`

### 🎯 Objective
Implement a high-performance string length function using **SSE4.2** assembly instructions.

### 🛠️ Key Instruction
Uses `pcmpistri` (Packed Compare Implicit Length Strings, Return Index) - a powerful SSE4.2 instruction designed specifically for string operations!

### 🔄 Algorithm
1. Zero out registers (`%eax`, `%ecx`, `%esi`) and initialize XMM0 as null terminator
2. Load 16 bytes of string into `%xmm1` register
3. Use `pcmpistri $0x08, %xmm0, %xmm1` to find first null terminator
   - Control byte `$0x08`: Equal each, unsigned bytes
   - Result stored in `%ecx` register
4. Add processed characters to counter in `%esi`
5. If `%ecx == 16`, no null terminator found in this chunk:
   - Advance string pointer by 16 bytes
   - Repeat from step 2
6. Otherwise, null terminator found - exit loop
7. Return total character count in `%eax`

### 💪 Why Assembly?
Direct assembly implementation allows:
- Maximum control over register usage
- Direct access to specialized SSE4.2 string instructions
- Zero function call overhead
- Minimal instruction count

### ⚡ Performance Advantage
Processes **16 bytes per iteration** instead of 1, achieving up to **16x speedup** for long strings! 🚄

---

## 🛠️ Technical Stack

### Languages & Technologies
- **C** - High-level implementation with intrinsics
- **x86-64 Assembly** - Direct hardware control
- **Intel SSE Intrinsics** - SIMD operations

### Instruction Set Extensions
- **SSE1** - Basic SIMD floating-point operations
- **SSE2** - Integer SIMD operations  
- **SSE3** - Horizontal operations
- **SSE4.1** - Enhanced extraction/insertion
- **SSE4.2** - String processing instructions

---

## 📚 Key Takeaways

### 🎓 What You'll Learn
- ✅ SIMD programming concepts and patterns
- ✅ Intel SSE intrinsics and their applications
- ✅ Assembly language for x86-64 architecture
- ✅ Performance optimization techniques
- ✅ Data-parallel algorithm design
- ✅ Low-level system programming

### 💎 Best Practices Demonstrated
- Efficient loop unrolling
- Register reuse strategies
- Handling remainder elements in SIMD code
- Horizontal reduction operations
- String processing with specialized instructions

---

## 🔬 Performance Comparison

| Operation | Scalar | SIMD | Speedup |
|-----------|--------|------|---------|
| Formula Computation | 1x | ~4x | 🚀 4x faster |
| Hamming Distance | 1x | ~16x | 🚀 16x faster |
| String Length | 1x | ~16x | 🚀 16x faster |

*Note: Actual speedup depends on CPU architecture, compiler optimizations, and data characteristics*

---

## 🎯 Compilation

### Compile Individual Parts
```bash
# Part 1
gcc -o decode decode.c

# Part 2
gcc -msse -msse3 -o formula1 formula1.c -lm

# Part 3
gcc -msse2 -msse4.1 -o hamming hamming_distance.c

# Part 4
as -o strlen_sse42.o strlen_sse42.s
```

### Required Flags
- `-msse`, `-msse2`, `-msse3`, `-msse4.1` - Enable respective SSE instruction sets
- `-lm` - Link math library (for `sqrtf`, `cbrtf`)

---

## 🎨 Project Structure

```
.
├── decode.c              # Part 1: Assembly decoder
├── formula1.c            # Part 2: Complex formula computation
├── formulas.h            # Part 2: Header file
├── hamming_distance.c    # Part 3: Hamming distance calculator
├── strlen_sse42.s        # Part 4: Optimized strlen
└── README.md             # This file
```

---

## 🌟 Credits

This project demonstrates advanced optimization techniques for computational efficiency, showcasing the power of SIMD programming and low-level system optimization.

---

## 📜 License

Educational project - Free to use and modify

---

**Made with ⚡ and lots of XMM registers** 🎮
