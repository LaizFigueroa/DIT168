#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag v2v_ubuntu "$DOCKER_USERNAME"/v2v_ubuntu
docker push "$DOCKER_USERNAME"/v2v_ubuntu
