FROM python:3.8.11

WORKDIR /usr/src/api

COPY requirements.txt .

#FIXME:remove vim
# RUN apt-get update & apt-get install vim

RUN pip install --no-cache-dir -r requirements.txt

COPY . .
