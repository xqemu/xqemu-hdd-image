FROM ubuntu:18.04
RUN apt-get update && apt-get upgrade -y
ENV PACKAGES sudo unzip genisoimage
RUN apt-get -y install $PACKAGES
RUN dpkg -l $PACKAGES | sort > /packages.txt
ENV FEATURES clang pyyaml
RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo
USER docker
CMD /bin/bash
