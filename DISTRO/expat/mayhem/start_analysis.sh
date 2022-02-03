#!/bin/bash -e

pushd ../
image=$(mayhem docker-registry)/makesoftwaresafe/toyota-dcm/expat:latest
docker build -t $image -f mayhem/Dockerfile .
docker push $image
popd
mayhem validate .
mayhem run .
