#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag v2v "$DOCKER_USERNAME"/v2v
docker push "$DOCKER_USERNAME"/v2v

docker tag app "$DOCKER_USERNAME"/app
docker push "$DOCKER_USERNAME"/app

docker tag interceptor "$DOCKER_USERNAME"/interceptor
docker push "$DOCKER_USERNAME"/interceptor
