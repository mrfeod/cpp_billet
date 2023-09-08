#!/usr/bin/env sh

sudo apt update
sudo apt install -y wget

wget http://security.ubuntu.com/ubuntu/pool/main/i/icu/libicu55_55.1-7_amd64.deb
sudo apt install -y ./libicu55_55.1-7_amd64.deb
rm ./libicu55_55.1-7_amd64.deb
