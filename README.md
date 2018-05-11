# wav2midi

[![CircleCI](https://circleci.com/gh/mrk21/wav2midi.svg?style=svg)](https://circleci.com/gh/mrk21/wav2midi)

wav2midi is in order to convert sound wave to scale.

## Dependencies

### Middlewares/Tools

* C++ Compiler (C++17)
    * AppleClang: `N/A`
    * Clang: `>= 5.0.0`
    * GCC: `>= 7.0.0`
* CMake: `>= 3.10.0`
* gnuplot
* ffmpeg

### Development tools

* direnv
* docker: `>=  17.x.x`
* docker-compose: `>= 1.20.0`
* clang-tidy: `>= 5.0.0`

### Libraries

* [Boost (BSL-1.0)](https://www.boost.org/): `>= 1.6.5`
* [libsndfile (LGPL-2.1)](https://github.com/erikd/libsndfile): `>= 1.0.0`
* [bandit (MIT)](https://github.com/banditcpp/bandit): `>= 2.0.0`

## Setup

### Install CMake

`CMake` is C/C++ build system generator. You can see installation detail to [Installing | CMake](https://cmake.org/install/). Also if you used macOS, then you can install by `homebrew`:

```bash
$ brew install cmake
```

### Install Boost

`Boost` is C++ pre-standard library. You can see installation detail to [Boost Getting Started on Unix Variants - 1.67.0](https://www.boost.org/doc/libs/1_67_0/more/getting_started/unix-variants.html). Also if you used macOS, then you can install by `homebrew`:

```bash
$ brew install boost
```

### Install libsndfile

`libsndfile` is a C library for reading and writing sound files containing sampled audio data. You can see instalation detail to [libsndfile](https://github.com/erikd/libsndfile). Also if you used macOS, then you can install by `homebrew`:

```
$ brew install libsndfile
```

### Install bandit

`bandit` is C++11 testing framework like RSpec. Its installation works are nothing, because it is executed automatically on build.

### Initialize project

```bash
$ mkdir gen
$ cd gen
$ cmake -DCMAKE_CXX_COMPILER=clang++ -DBUILD_TEST=ON ..
```

## Build

```bash
$ cd gen
$ make
```

## Run

### Input from file

```bash
$ cd gen
$ ./src/main /path/to/sound.wav
```

### Input from microphone(line in)

If you will input from microphone or line in, specify `/dev/stdin` and use `ffmpeg`.
If you used macOS, enter the command like listed below:

```sh
$ cd gen
$ ffmpeg -f avfoundation -i "none:0" -f wav pipe:1 | ./src/main
```

**Refer to:**

* [FFmpeg Devices Documentation](https://www.ffmpeg.org/ffmpeg-devices.html#avfoundation)

## Test

```bash
./test.sh [test_target]
```

## Other

This project coding styles follow C++ Standard Libraries and Boost C++ Libraries basically.

**Refer to:**

* [Boost Library Requirements and Guidelines](https://www.boost.org/development/requirements.html)

## More documentation

* [wav2midi 方針・設計 | mrk21 Kibela](https://mrk21.kibe.la/shared/entries/3931bfea-0f31-4aa1-9e72-b7cd6f010697)
