#!/bin/bash

# You must run this script without sudo. To run docker without sudo do the following:
# sudo groupadd docker
# sudo gpasswd -a $USER docker

while getopts c:f:C flag
do
	case "${flag}" in
		c) cmake_params=${OPTARG};;
		f) feature=${OPTARG};;
		C) colored=t;;
	esac
done

# make sure the TAG is unique by using PWD
TAG=$(echo ${PWD:1} | tr '[:upper:]' '[:lower:]' | tr -d '[:space:]')
VOLUME_DIR=/usr/firmware

pio_command='pio run -d ../.. -t upload'

cmake_command='
	set -e
	cmake '${VOLUME_DIR}'
	cmake --build . '${cmake_params}

cuke_execute='
	feature_path=$(find -P ../.. -name ${feature}.feature)
	./${executable} >/dev/null &
	cucumber -S --publish-quiet "${feature_path}"'


if [[ -z "${feature}" ]]
then
	cuke_command='
	for executable in steps/*; do
		echo executable: ${executable}
		feature=${executable:6:-7}
		'${cuke_execute}'
	done'
else
	cuke_command='
	feature='${feature}'
	executable=steps/${feature}__steps
	'${cuke_execute}
fi


echo "building container, please wait (the first time this may take several minutes) ..."
docker build -t $TAG \
	--build-arg  USER=$USER \
	--build-arg  USER_ID=$(id -u) \
	--build-arg  GROUP_ID=$(id -g) \
	. #>/dev/null

BUILD_DIR=tmp/cucumber_build
mkdir -p ${BUILD_DIR}
docker run \
	--privileged \
	--rm \
	--name cucumber_$(date +%s) \
	--volume "${PWD}":${VOLUME_DIR} \
	--workdir "${VOLUME_DIR}/${BUILD_DIR}" \
	-i${colored} $TAG \
	bash -c "${pio_command} ${cmake_command} ${cuke_command}"
