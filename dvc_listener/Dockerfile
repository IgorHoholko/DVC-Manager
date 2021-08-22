ARG GCC_VERSION=8.5.0
FROM gcc:$GCC_VERSION

WORKDIR /usr/src/dvc_listener

COPY . .

RUN apt-get update && apt-get install -y apt-transport-https

RUN apt-get install -y libcpprest-dev

ARG CMAKE_VERSION=3.21.1
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/cmake-install.sh

RUN apt-get install libboost-all-dev

ENV PATH="/usr/bin/cmake/bin:${PATH}"

CMD tail -f /dev/null