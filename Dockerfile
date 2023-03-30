FROM ubuntu:jammy

RUN apt update

RUN apt install -y gdb cmake make git build-essential