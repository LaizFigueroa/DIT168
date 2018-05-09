#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag webview "$DOCKER_USERNAME"/webview
docker push "$DOCKER_USERNAME"/webview
