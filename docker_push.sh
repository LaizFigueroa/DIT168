#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag dit168 "$DOCKER_USERNAME"/dit168:Auto
docker push "$DOCKER_USERNAME"/dit168
