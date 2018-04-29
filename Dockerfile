# wav2midi container
# @see Quickstart: Compose and Rails | Docker Documentation https://docs.docker.com/compose/rails/
# @see Docker で apt-get install するときに TERM 系のエラーが出る | まくまく Docker ノート http://maku77.github.io/docker/term-error.html
FROM ubuntu:18.04
ENV LANG C.UTF-8
ENV DEBIAN_FRONTEND noninteractive

# base packages
RUN apt-get update -qq && \
    apt-get install -y build-essential tree vim less && \
    apt-get install -y --no-install-recommends apt-utils

# - CMake 3.10
# - Clang 5.0
# @see clang - Install libc++ on ubuntu - Stack Overflow https://stackoverflow.com/questions/39332406/install-libc-on-ubuntu
# @see c++ - Clang doesn't see basic headers - Stack Overflow https://stackoverflow.com/questions/26333823/clang-doesnt-see-basic-headers
RUN apt-get install -y \
  cmake \
  llvm-5.0 \
  clang-5.0 \
  libclang-common-5.0-dev \
  libclang-5.0-dev \
  libclang1-5.0 \
  libclang1-5.0-dbg \
  libllvm5.0 \
  libllvm5.0-dbg \
  llvm-5.0-dev \
  llvm-5.0-runtime \
  libc++1 \
  libc++-dev \
  libc++abi-dev \
  && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-5.0 100 \
  && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-5.0 100

ENV APP_HOME /app

# NOTE: A login shell overrides the PATH environment variable set by docker,
# so I set same value as the environment variable to .profile.
# By means of this, PATH environment variable is same value on non login shell and login shell.
ENV PATH $APP_HOME/bin:$PATH
RUN echo "export PATH=$PATH" >> /root/.profile

RUN mkdir -p $APP_HOME
WORKDIR $APP_HOME
