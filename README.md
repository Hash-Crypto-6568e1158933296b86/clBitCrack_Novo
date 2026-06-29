# clBitCrack_Novo

# Added clBitCrack_Bot to the release.
# Install GOLANG.

<img width="893" height="883" alt="clBitCrack_bot" src="https://github.com/user-attachments/assets/fda4b000-c93c-4dc3-9a78-b46b51dea645" />

```bash
chmod +x 71.sh
./71.sh
```

# Fixed a critical bug that occurred when running clbitcrack on AMD graphics cards.

# A GPU-accelerated Bitcoin private key search tool with support for both **CUDA** (NVIDIA) and **OpenCL** (AMD/Intel) devices.

---

## Table of Contents

- [Building](#building)
- [Usage](#usage)
- [Options](#options)
- [Examples](#examples)
- [Choosing Parameters](#choosing-the-right-parameters-for-your-device)
- [Supporting this project](#supporting-this-project)

---

## Building

### Compile on Linux

**OpenCL (AMD):**
```bash
make BUILD_OPENCL=1
```

**CUDA (NVIDIA):**
```bash
make BUILD_CUDA=1
```

**Both:**
```bash
make BUILD_CUDA=1 BUILD_OPENCL=1
```

> **Note:** The project can be cloned and built from any directory, including paths with spaces.

**Dependencies:**
- OpenCL: Mesa or vendor OpenCL runtime (`ocl-icd-opencl-dev`)
- CUDA: CUDA Toolkit 10.1+

---

### Compile on Windows (MSYS2 + MinGW-w64)

1. Install [MSYS2](https://www.msys2.org/) and open the **MSYS2 MinGW 64-bit** terminal.

2. Install build tools and OpenCL:

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc \
          mingw-w64-x86_64-make \
          mingw-w64-x86_64-opencl-icd \
          mingw-w64-x86_64-opencl-headers

/user/src/clBitCrack_Novo
cd clBitCrack_Novo
make clean
make BUILD_OPENCL=1          # ou  BUILD_CUDA=1  se tiver nvcc
The binaries will appear in bin/ (clBitCrack.exe, addrgen.exe, …).          
```

3. Clone the repository into a path **without spaces** (e.g. `C:\src\clbitcrack`).

4. Build:

```bash
git clone https://github.com/Hash-Crypto-6568e1158933296b86/clBitCrack_Novo.git
/home/src/clBitCrack_Novo
cd clBitCrack_Novo
make BUILD_OPENCL=1
```

Binaries will appear in `bin/` (`clBitCrack.exe`, `addrgen.exe`, ...).

---

## Usage

```
./clBitCrack [OPTIONS] [TARGETS]
```

Where `[TARGETS]` are one or more Bitcoin addresses.

---

## Options

| Option | Description |
|--------|-------------|
| `-i, --in FILE` | Read target addresses from FILE, one per line. Use `-` for stdin |
| `-o, --out FILE` | Append found private keys to FILE, one per line |
| `-d, --device N` | Use GPU device with ID N (default: 0) |
| `-b, --blocks N` | Number of GPU blocks |
| `-t, --threads N` | Threads per block (must be a multiple of 32) |
| `-p, --points N` | Keys processed per thread per iteration |
| `--keyspace RANGE` | Keyspace range to search (see format below) |
| `-c, --compressed` | Search compressed addresses (default) |
| `-u, --uncompressed` | Search uncompressed addresses |
| `--compression MODE` | `compressed`, `uncompressed`, or `both` |
| `--stride N` | Increment keys by N instead of 1 |
| `--share M/N` | Split keyspace into N shares, process share M |
| `--continue FILE` | Save and resume progress from FILE |
| `--list-devices` | List available GPU devices |

### Keyspace format

| Format | Meaning |
|--------|---------|
| `START:END` | Search from START to END |
| `START:+COUNT` | Search COUNT keys starting at START |
| `:END` | Search from key 1 to END |
| `:+COUNT` | Search COUNT keys starting from key 1 |

---

## Examples

### List available devices
```bash
./clBitCrack --list-devices
```

### Single address, automatic parameters
```bash
./clBitCrack 1FshYsUh3mqgsG29XpZ23eLjWV8Ur3VwH
```

### Multiple addresses from a file, specific keyspace
```bash
./clBitCrack -i input.txt -b 64 -t 64 -p 64 \
  --keyspace 80000000:ffffffff \
  -o found.txt --compressed
```

### Small keyspace (puzzle testing)
```bash
./clBitCrack -i input0.txt -b 128 -t 128 -p 128 \
  --keyspace 80000:fffff \
  -o found.txt --compressed
```

### Large keyspace with save/resume (e.g. Puzzle 69)
### The target address is copied into input.txt.
```bash
./clBitCrack --continue puzzle69 -i input69.txt -b 256 -t 256 -p 256 \
  --keyspace 101d83275000000000:1fffffffffffffffff \
  -o found.txt --compressed
```

> Progress is saved to `puzzle69` automatically. If interrupted, re-run the same command to resume from where it stopped.

### Verified output example (AMD Radeon RX 470, OpenCL)

```
./clBitCrack --continue puzzle69 -b 256 -t 256 -p 256 --keyspace 101d83275000000000:1fffffffffffffffff --compressed 19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG
========================================================|
==================== CLBITCRACK+BOT ====================|
========================================================|
[2026-06-29.00:29:17] [Info] Compression: compressed
[2026-06-29.00:29:17] [Info] Starting at: 0000000000000000000000000000000000000000000000101D83275FB2BC0000
[2026-06-29.00:29:17] [Info] Ending at:   00000000000000000000000000000000000000000000001FFFFFFFFFFFFFFFFF
[2026-06-29.00:29:17] [Info] Counting by: 0000000000000000000000000000000000000000000000000000000000000001
[2026-06-29.00:29:17] [Info] Compiling OpenCL kernels...
[2026-06-29.00:29:17] [Info] Initializing AMD Radeon RX 470 Series (radeonsi, polaris10, ACO, DRM 3.64, 6.17.0-35-generic)
[2026-06-29.00:29:17] [Info] Generating 262,144 starting points (10.0MB)
[2026-06-29.00:29:18] [Info] 10.0%
[2026-06-29.00:29:18] [Info] 20.0%
[2026-06-29.00:29:18] [Info] 30.0%
[2026-06-29.00:29:18] [Info] 40.0%
[2026-06-29.00:29:18] [Info] 50.0%
[2026-06-29.00:29:18] [Info] 60.0%
[2026-06-29.00:29:18] [Info] 70.0%
[2026-06-29.00:29:18] [Info] 80.0%
[2026-06-29.00:29:18] [Info] 90.0%
[2026-06-29.00:29:18] [Info] 100.0%
[2026-06-29.00:29:18] [Info] Done
[2026-06-29.00:29:18] [Info] Loading addresses from 'input69.txt'
[2026-06-29.00:29:18] [Info] 1 addresses loaded (0.0MB)

[2026-06-29.00:29:18] [Info] Address:     19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG
[2026-06-29.00:29:18] [Info] Private key: 0000000000000000000000000000000000000000000000101D83275FB2BC7E0C
[2026-06-29.00:29:18] [Info] Compressed:  yes
[2026-06-29.00:29:18] [Info] Public key:  024BABADCCC6CFD5F0E5E7FD2A50AA7D677CE0AA16FDCE26A0D0882EED03E7BA53
[2026-06-29.00:29:18] [Info] No targets remaining
```

---

## Choosing the Right Parameters for Your Device

GPUs divide work into **blocks → threads → keys per thread**.

| Parameter | Flag | Recommendation |
|-----------|------|----------------|
| Blocks | `-b` | Multiple of the number of GPU compute units. Start with `128` or `256` |
| Threads | `-t` | Must be a multiple of 32. Typical values: `128`, `256` |
| Keys per thread | `-p` | Higher = more keys per launch, better throughput. Start with `128` or `256` |

> **Tip:** For AMD GCN cards (RX 470/480/570/580), `-b 256 -t 256 -p 256` is a good starting point. Increase `-p` to improve MKey/s if the GPU is not fully saturated.

---

## Supporting this project

If you find this project useful and would like to support it, consider making a donation:

**BTC:** `bc1q6c2lux7muk5nagcqzy299s5gz0h7cksx9nqaq5`

**SOL:** `DvvjyQT71wEw14n5SEbzKjQx2NJ9CWSw5Z3c2xyF7GPt`
