We will use a Docker image for a buffer overflow experiment 
(If you have not used Docker before, it would be a good chance to get used to it). 
Docker offers a platform to deliver varying software 
in `containers`. 

A container is an isolated process running on the host, 
communicating with another container via a well-defined channel. 

It differs from VM (virtual machine) in that Docker does not 
consume much hardware resources (e.g., no guest OS), 
enabling one to efficiently run services efficiently.



### Docker Installation

For Windows WSL-Ubuntu,
there are a series of phases to install Docker for WSL appropriately.
For more information (i.e., confirming pre-requisites), you may want to visit:
https://altis.com.au/installing-docker-on-ubuntu-bash-for-windows/
```
$ sudo apt-get install apt-transport-https ca-certificates curl software-properties-common
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
$ sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu (lsb_release -cs) stable"
$ sudo apt update
$ sudo apt-get install docker-ce
$ sudo usermod -aG docker [user_id]
```
Note that TCP endpoint is turned off by default at the latest version of Docker.
To activate it, right-click the Docker icon in your taskbar and choose Settings, 
check the box of `Expose daemon on tcp://localhost:2375 without TLS`.

Or if you have difficulty in installing Docker in the Windows WSL environment, 
it might be simple to install it in Ubuntu. 
The command of *usermod* allows one to run docker without *sudo*.
```
$ curl -fsSL https://get.docker.com/ | sudo sh
$ sudo usermod -aG docker [user_id]
```


### Build the image

With the given `Dockerfile` in the current directory, build your own image. 
This will take a while.
```
$ docker build -t esw4010 .  
[+] Building 740.6s (10/10) FINISHED
 => [internal] load build definition from Dockerfile                                                                                                                                   0.1s
 => => transferring dockerfile: 574B                                                                                                                                                   0.0s
 => [internal] load .dockerignore                                                                                                                                                      0.1s
 => => transferring context: 2B                                                                                                                                                        0.0s
 => [internal] load metadata for docker.io/32bit/ubuntu:16.04                                                                                                                          3.1s
 => [1/6] FROM docker.io/32bit/ubuntu:16.04@sha256:eeb557f736be17c5a8706176746e0e94c49853ca32d840e4ad06819f22415ddc                                                                   29.0s
 => => resolve docker.io/32bit/ubuntu:16.04@sha256:eeb557f736be17c5a8706176746e0e94c49853ca32d840e4ad06819f22415ddc                                                                    0.0s
 => => sha256:eeb557f736be17c5a8706176746e0e94c49853ca32d840e4ad06819f22415ddc 529B / 529B                                                                                             0.0s
 => => sha256:cc30c7e0cb5a0248f1fb964d2bf6d63c9fe1e2a1db5b1661234fb3f7c7442b4e 885B / 885B                                                                                             0.0s
 => => sha256:50f85dcd8f291118876eb4c9c6cc9efbbe1d0114c2cc0befb1642510386c22fc 113.98MB / 113.98MB                                                                                    18.8s
 => => extracting sha256:50f85dcd8f291118876eb4c9c6cc9efbbe1d0114c2cc0befb1642510386c22fc                                                                                              9.9s
 => [2/6] RUN apt-get -y update && apt-get install -y git texinfo byacc flex bison automake autoconf build-essential libtool cmake gawk  696.1s
 => [3/6] RUN pip install pyelftools                                                                                                                                                   3.7s
 => [4/6] RUN git clone https://github.com/longld/peda.git ~/peda                                                                                                                      1.2s
 => [5/6] RUN echo "source ~/peda/peda.py" >> ~/.gdbinit                                                                                                                               0.4s
 => [6/6] RUN echo "[ES4010] docker ready!"                                                                                                                                            0.5s
 => exporting to image                                                                                                                                                                 6.3s
 => => exporting layers                                                                                                                                                                6.3s
 => => writing image sha256:be7f573f3f38f7e23a0cdaecc9a45abc5e6f4e7d2194222615eb3f52a0018033                                                                                           0.0s
 => => naming to docker.io/library/esw4010                                                                                                                                             0.0s
```

Now you can see your own `esw4010` docker image. The image ID looks different in your machine.
```
$ docker images
REPOSITORY               TAG       IMAGE ID       CREATED         SIZE
esw4010                  latest    be7f573f3f38   8 minutes ago   1GB
```
You can find general command line references for Docker here:
https://docs.docker.com/engine/reference/commandline/docker/

Once complete, run your container for the first time.
Here `-it` option represents `interactive` mode using `/bin/bash`, 
and `--rm` option will remove all jobs you've done when exiting the container.
```
$ docker run --rm -it esw4010 /bin/bash
```


### Writing your own exploit with a buffer overflow

Recall `vul.c` in class. The small program contains a vulnerability (i.e., buffer overflow).
In this setting, we assume that both stack canary and NX do not exist just like back in 90's.

```
// gcc -fno-stack-protector -z execstack -no-pie -o vul vul.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vul(char* name) {
        char buf[64] = {};
        strcpy(buf, name);
}

int main(int argc, char* argv[]) {
        if (argc < 2) {
                printf ("Usage: %s [Your name]\n", argv[0]);
                exit(-1);
        }

        vul(argv[1]);
        return 0;
}
```

Your task is to write an exploit (named `exp.py`) in python 
to leverage the above vulnerability to *obtain a shellcode*.
Choose any working shellcode for `x86`: http://shell-storm.org/shellcode/
Note that the shellcode in class was for `x86_64` thus you should use another for `x86`!


### Submission

* Your exploit: `exp.py`
* Briefly explain how your exploit works inside your exploit code as comments
* Answers for a few questions in homework assignment #2

