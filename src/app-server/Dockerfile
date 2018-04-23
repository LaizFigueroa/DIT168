FROM pipill/armhf-alpine:edge as builder
RUN [ "cross-build-start" ]
RUN cat /etc/apk/repositories && \
    echo http://dl-4.alpinelinux.org/alpine/v3.7/main > /etc/apk/repositories && \
    echo http://dl-4.alpinelinux.org/alpine/v3.7/community >> /etc/apk/repositories
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
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/tmp .. && \
    make && make install
RUN [ "cross-build-end" ]

# Deploy.
FROM pipill/armhf-alpine:edge
RUN [ "cross-build-start" ]
WORKDIR /usr/bin
COPY --from=builder /tmp/bin/ .
CMD ["/usr/bin/app-server"]