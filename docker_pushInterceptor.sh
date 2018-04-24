#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag interceptor "$DOCKER_USERNAME"/interceptor
docker push "$DOCKER_USERNAME"/interceptor
