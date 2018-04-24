#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag app "$DOCKER_USERNAME"/app
docker push "$DOCKER_USERNAME"/app

