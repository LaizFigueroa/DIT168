#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag webview_ubuntu "$DOCKER_USERNAME"/webview_ubuntu
docker push "$DOCKER_USERNAME"/webview_ubuntu
