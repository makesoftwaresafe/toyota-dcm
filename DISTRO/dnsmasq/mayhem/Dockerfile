# Use stages to keep our final image lightweight.
FROM ubuntu:20.04 as builder

# Install build dependencies.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y unzip patch make gcc libdbus-1-dev gdb cmake g++

# Copy the dnsmasq source into the container
RUN mkdir /dnsmasq
COPY . /dnsmasq
WORKDIR /dnsmasq
# Apply patches in the Toyota code.
RUN patch -p1 < 0001-Added-.gitignore.patch
RUN patch -p1 < 0002-OTP-Port-of-Wifimgr-Platform-Infrastructure.patch
RUN patch -p1 < 0003-Change-in-dbus-configuration-for-Multiple-APNs-relat.patch
RUN patch -p1 < 0004-Modified-the-makefile-to-push-dnsmasq.conf-to-etc-db.patch
# Build the uninstrumented version.
RUN make CFLAGS='-Wall -W -g' -j$(grep -c ^processor /proc/cpuinfo) && \
    make install PREFIX=/dnsmasq-uninst && \
    make clean
# Build the ASAN version.
RUN make CFLAGS='-Wall -W -g -fsanitize=address -static-libasan' LDFLAGS='-fsanitize=address -static-libasan' -j$(grep -c ^processor /proc/cpuinfo) && \
    make install PREFIX=/dnsmasq-asan && \
    make clean
# Build the harness.
WORKDIR /dnsmasq/mayhem/harness
RUN rm -rf build && \
    mkdir build && \
    cd build/ && \
    cmake .. && \
    make -j$(grep -c ^processor /proc/cpuinfo)

# Now let's build the container we'll actually use for analysis.
FROM ubuntu:20.04

# Install runtime packages
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libdbus-1-3 libc6-dbg && \
    rm -rf /var/lib/apt/lists/*

# Copy in everything we need to run dnsmasq.
COPY --from=builder /dnsmasq-uninst /dnsmasq-uninst
COPY --from=builder /dnsmasq-asan /dnsmasq-asan
COPY --from=builder /dnsmasq /dnsmasq
COPY --from=builder /dnsmasq/mayhem/harness/build/libharness.so /
COPY --from=builder /dnsmasq/mayhem/leases /tmp/leases
