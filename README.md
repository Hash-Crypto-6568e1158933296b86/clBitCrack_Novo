# clBitCrack_Novo

Fixed a critical bug that occurred when running clbitcrack on AMD graphics cards.

A GPU-accelerated Bitcoin private key search tool with support for both **CUDA** (NVIDIA) and **OpenCL** (AMD/Intel) devices.

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
[2026-06-26.04:19:04] [Info] Compression: compressed
[2026-06-26.04:19:04] [Info] Starting at: 0000000000000000000000000000000000000000000000101D83275000000000
[2026-06-26.04:19:04] [Info] Ending at:   00000000000000000000000000000000000000000000001FFFFFFFFFFFFFFFFF
[2026-06-26.04:19:04] [Info] Counting by: 0000000000000000000000000000000000000000000000000000000000000001
[2026-06-26.04:19:04] [Info] Compiling OpenCL kernels...
[2026-06-26.04:19:04] [Info] Initializing AMD Radeon RX 470 Series (radeonsi, polaris10, ACO, DRM 3.64, 6.17.0-35-generic)
[2026-06-26.04:19:07] [Info] Generating 16,777,216 starting points (640.0MB)
[2026-06-26.04:19:10] [Info] 10.0%
[2026-06-26.04:19:11] [Info] 20.0%
[2026-06-26.04:19:12] [Info] 30.0%
[2026-06-26.04:19:12] [Info] 40.0%
[2026-06-26.04:19:13] [Info] 50.0%
[2026-06-26.04:19:14] [Info] 60.0%
[2026-06-26.04:19:14] [Info] 70.0%
[2026-06-26.04:19:15] [Info] 80.0%
[2026-06-26.04:19:16] [Info] 90.0%
[2026-06-26.04:19:16] [Info] 100.0%
[2026-06-26.04:19:16] [Info] Done
[2026-06-26.04:19:16] [Info] Loading addresses from 'input69.txt'
[2026-06-26.04:19:16] [Info] 1 addresses loaded (0.0MB)
AMD Radeon RX 47 1536 / 8192MB | 1 target 121.70 MKey/s (5,637,144,576 total) [00:00:43][2026-06-26.04:20:04] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 119.18 MKey/s (12,901,679,104 total) [00:01:44][2026-06-26.04:21:04] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 117.26 MKey/s (20,099,104,768 total) [00:02:45][2026-06-26.04:22:05] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 116.57 MKey/s (27,296,530,432 total) [00:03:46][2026-06-26.04:23:07] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 115.77 MKey/s (34,275,852,288 total) [00:04:46][2026-06-26.04:24:07] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 115.09 MKey/s (41,255,174,144 total) [00:05:47][2026-06-26.04:25:08] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 114.79 MKey/s (48,234,496,000 total) [00:06:48][2026-06-26.04:26:08] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 114.43 MKey/s (55,213,817,856 total) [00:07:49][2026-06-26.04:27:09] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 114.37 MKey/s (62,193,139,712 total) [00:08:50][2026-06-26.04:28:10] [Info] Checkpoint
AMD Radeon RX 47 1536 / 8192MB | 1 target 113.89 MKey/s (67,209,527,296 total) [00:09:34][2026-06-26.04:28:54] [Info] Address:     19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG
                             Private key: 0000000000000000000000000000000000000000000000101D83275FB2BC7E0C
                             Compressed:  yes
                             Public key:  
                             024BABADCCC6CFD5F0E5E7FD2A50AA7D677CE0AA16FDCE26A0D0882EED03E7BA53
                             
[2026-06-26.04:28:54] [Info] No targets remaining
AMD Radeon RX 47 1536 / 8192MB | 1 target 114.49 MKey/s (67,427,631,104 total) [00:09:36]
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
