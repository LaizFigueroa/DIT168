# Copyright (C) 2018 DIT168 - Group 13
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
ADD . /src/app-server
WORKDIR /src/app-server
RUN ls &&\
    cd src/app-server && \
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
CMD ["/usr/bin/Server"]
