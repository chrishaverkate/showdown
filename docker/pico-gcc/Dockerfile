# CLion remote docker environment (How to build docker container, run and stop it)
#
# Build and run (inside docker folder):
#   docker build -t clion/remote-cpp-env:0.5 -f Dockerfile .
#   docker run -d --cap-add sys_ptrace -p127.0.0.1:2222:22 --name clion_remote_env clion/remote-cpp-env:0.5
#   ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:2222"
#
# stop:
#   docker stop clion_remote_env
#
# ssh credentials (test user):
#   ssh user@localhost -p 2222
#   password: password

FROM ubuntu:22.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN useradd -s /bin/bash -m user \
  && yes password | passwd user

# Customize for tools needed
RUN apt-get update \
	&& apt-get install -y ssh \
	build-essential \
	gcc-arm-none-eabi \
	gcc \
	g++ \
	gdb \
	clang \
	cmake \
	rsync \
	tar \
	python3 \
	git \
	nano \
	htop \
	doxygen \
  && apt-get clean

# sshd configuration
RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
    echo 'UsePAM yes'; \
  ) > /etc/ssh/sshd_config_test_clion \
  && mkdir /run/sshd

