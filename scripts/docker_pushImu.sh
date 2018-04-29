#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag imu "$DOCKER_USERNAME"/imu
docker push "$DOCKER_USERNAME"/imu
