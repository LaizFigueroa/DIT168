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
docker run -ti --net=host YOUR_DOCKER_HUB_REPO/NAME /usr/bin/V2VService --ip="YOUR_CAR'S_IP"
```
