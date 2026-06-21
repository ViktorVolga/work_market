FROM ubuntu:latest as work_market_image
RUN apt update
RUN apt upgrade -y
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y make
RUN apt-get install -y cmake
RUN mkdir /devel/
RUN mkdir /devel/work_market/
RUN apt-get install -y libcurl4-openssl-dev
RUN apt-get install -y gdb

#adding spdlog
RUN apt-get install git -y 
RUN git clone https://github.com/gabime/spdlog.git /home/libs/spdlog/
RUN cmake -S /home/libs/spdlog/ -B /home/libs/spdlog/build/ 
RUN make /home/libs/spdlog/build/  
RUN mkdir /home/logs/

#getting wget
RUN apt-get install -y wget

#getting bzip
RUN apt-get install -y bzip2

RUN apt-get install -y build-essential python3-dev autotools-dev libicu-dev libbz2-dev

#boost
#RUN echo "new"
#RUN mkdir -p /home/libs/boost
#RUN wget --continue --directory-prefix=/home/libs/boost/ https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.bz2
#RUN tar --directory=/home/libs/boost/ --checkpoint=1000 --bzip2 -xf /home/libs/boost/boost_1_82_0.tar.bz2
#RUN cd /home/libs/boost/boost_1_82_0/
#RUN /home/libs/boost/boost_1_82_0/bootstrap.sh \
#&& ./b2 \
#&& ./b2 install

RUN apt-get install -y libboost-all-dev

RUN apt-get install -y pkg-config
RUN apt-get install -y dpkg-dev

RUN apt-get install -y libmysqlcppconn-dev

RUN apt-get install -y libgtest-dev

RUN pip install mysql

RUN pip install mysql-connector 
RUN pip install --upgrade mysql-connector-python

#if not enoght cloning from git-hub

#for compilation image:  docker build . -f dockerfile.txt -t work_market_image

#docker run --name work_market -it -v "$(pwd)":/devel/work_market /bin/bash

#docker exec -it work_market bash

#pass root