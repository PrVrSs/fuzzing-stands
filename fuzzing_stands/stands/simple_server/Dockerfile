FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
    gcc \
    libc6-dev \
    make

RUN mkdir /code
WORKDIR /code
COPY . /code/

RUN make vulnserver

EXPOSE 5001
CMD ["./vulnserver"]
