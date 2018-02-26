# docker run --rm -ti -v $PWD:/opt/sources alpine:3.7 /bin/sh
FROM alpine:3.7 as builder
MAINTAINER Christian Berger christian.berger@gu.se
RUN apk update && \
    apk --no-cache add \
        ca-certificates \
        cmake \
        g++ \
        make && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted
ADD . /opt/sources
WORKDIR /opt/sources
RUN cd /opt/sources && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release .. && \
    make &&  cp testComm /tmp

# Deploy.
FROM alpine:3.7
MAINTAINER Christian Berger christian.berger@gu.se
RUN apk update && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted && \
    mkdir /opt
WORKDIR /opt
COPY --from=builder /tmp/testComm .
CMD ["/opt/testComm"]
