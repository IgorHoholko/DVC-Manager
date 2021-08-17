FROM python:3.8.11

WORKDIR /usr/src/dvc_manager

COPY requirements.txt .

RUN apt-get update & apt-get install vim

RUN pip install --no-cache-dir -r requirements.txt

COPY . .