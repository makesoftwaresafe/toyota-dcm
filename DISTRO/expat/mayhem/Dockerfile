FROM ubuntu:20.04 as builder

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y unzip patch cmake gcc g++ libc6-dbg
RUN mkdir /expat-src
COPY . /expat-src
WORKDIR /expat-src
RUN patch -p1 < 0001-initial-.gitignore.patch
RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/expat -DCMAKE_BUILD_TYPE=Debug .. && \
    make -j $(grep -c processor /proc/cpuinfo) && \
    make install && \
    cd ../ && \
    rm -rf build

FROM ubuntu:20.04
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libc6-dbg && \
    rm -rf /var/lib/apt/lists/*
COPY --from=builder /expat /expat
COPY --from=builder /expat-src /expat-src
ENV LD_LIBRARY_PATH=/expat/lib
ADD mayhem/xml.dict /
ADD mayhem/xml_UTF_16.dict /
ADD mayhem/xml_UTF_16BE.dict /
ADD mayhem/xml_UTF_16LE.dict /
RUN cat xml.dict xml_UTF_16.dict xml_UTF_16BE.dict xml_UTF_16LE.dict > xml_full.dict
