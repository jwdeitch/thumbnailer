FROM ubuntu:17.04

RUN apt upgrade && apt update
RUN apt install  \
	cmake \
  	build-essential \
  	wget \
  	libavcodec-dev \
  	libpng++-dev \
  	libavformat-dev \
  	libavutil-dev \
  	libjpeg-dev \
  	libavfilter-dev \
  	curl \
  	libcurl4-gnutls-dev \
  	zlib1g-dev -y

CMD ["tail", "-f", "/dev/stdout"]


