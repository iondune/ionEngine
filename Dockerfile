FROM ubuntu:xenial

RUN \
	apt-get update -y && \
	apt-get install g++ cmake libglew-dev xorg-dev libglfw3-dev mercurial git -y

COPY . ionEngine/

CMD \
	cd ionEngine && \
	./UpdateDependencies.bash && \
	cmake . && \
	make && \
	./bin/TestUnits
