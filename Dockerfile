FROM ubuntu:xenial

RUN apt-get -y update
RUN apt-get -y install g++ cmake libglew-dev xorg-dev libglfw3-dev mercurial git

COPY . ionEngine/
