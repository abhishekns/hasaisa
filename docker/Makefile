
DIRNAME=$(shell basename ${PWD})
NAME=${DIRNAME}-builder
VER=jammy

VOLUME = ${PWD}:/${DIRNAME}

DOCKER = docker run --rm -it -v ${VOLUME} --workdir /${DIRNAME} ${NAME}:${VER} /bin/bash -c

images:
	docker build -t ${NAME}:${VER} .

compile:
	${DOCKER} "mkdir -p build; cd build; cmake ..; make"

test:
	${DOCKER} "cd build; ./tests/tests"


clean:
	${DOCKER} "cd build && make clean"

bash:
	${DOCKER} /bin/bash
