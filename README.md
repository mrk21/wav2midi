# wav2midi

wav2midi is in order to convert sound wave to scale.

## Dependencies

### Middlewares/Tools

* C++ Compiler
    * Clang: `>= 5.0.0`
* CMake: `>= 3.11.0`

### Libraries

* [bandit](https://github.com/banditcpp/bandit)

## Setup

### Install CMake

`CMake` is C/C++ build system generator. You can see installation detail to [Installing | CMake](https://cmake.org/install/). Also if you used macOS, then you can install by `homebrew`:

```bash
$ brew install cmake
```

### Initialize project

```bash
$ mkdir gen
$ cd gen
$ cmake -DCMAKE_CXX_COMPILER=clang++ ..
```

## Build

```bash
$ cd gen
$ make
```

## Run

```bash
$ cd gen
$ ./src/main
```

## Test

```bash
./cmake.test [test_target]
```
