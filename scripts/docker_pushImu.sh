#!/bin/bash
docker login -u "$DOCKER_USERNAME" -p "$DOCKER_PASSWORD"
docker tag imu_receiver "$DOCKER_USERNAME"/imu_receiver
docker push "$DOCKER_USERNAME"/imu_receiver
