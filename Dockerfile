FROM ubuntu:xenial

RUN apt-get -y update
RUN apt-get -y install g++ cmake libglew-dev xorg-dev libglfw3-dev mercurial git

CMD hg clone https://bitbucket.org/iondune/ionEngine
CMD cd ionEngine
