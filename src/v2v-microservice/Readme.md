# V2V

This folder contains the v2v microservice to be run directly on the car. 

**Steps:**

1. Using DOCKER:
On the car's terminal (BeagleBone) add the following command adding your car's ip to it:

```
docker run -ti --net=host laiz/v2v /usr/bin/V2VService --ip="YOUR_CAR'S_IP"
```

2. From the repository:
On your computer (Cross-compiling) add the following commands by changing the capital letters for your own information or names:

```
cd src/v2v-microservice
docker build -t NAME . -f Dockerfile.manual
docker tag NAME YOUR_DOCKER_HUB_REPO/NAME
docker push YOUR_DOCKER_HUB_REPO/NAME
```

After that, you will be able to perform the following on your car's terminal:

```
docker run -ti --net=host YOUR_DOCKER_HUB_REPO/NAME /usr/bin/V2VService --ip="YOUR_CAR'S_IP" --limit=18 --skeep=5  --angle=1  --delay=160  --speed=0.22

The aformentionned command line arguments are used due to hardware reliability.

--ip: is the ip of the leader's car 
--limit: (equal to 1.8 seconds) which is the time required for the follower's car to reach the postion of the leader the moment of the first occurence of a turning to the left or to the right.
--skeep: is the number of pairs(angle,pedal) that the follower needs to bypass in order to reduce an extra turning
--angle: is used to reduce the offset of the follower car.
--delay: equal to 20 seconds which is the time set for flushing the queue responsible for storing timestamps from the leader's car.
--speed:used to hardcode the speed of the follower in case of a incompability in performance between the leader and the follower, which is close to the maximum speed sent by the PS4 controller

```
