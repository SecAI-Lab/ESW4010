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

Now you see your own `esw4010` docker image. The image ID looks different in your machine.
```
$ docker images
REPOSITORY               TAG       IMAGE ID       CREATED         SIZE
esw4010                  latest    be7f573f3f38   8 minutes ago   1GB
```

Once complete, run your container for the first time.
Here `-it` option represents `interactive` mode using `/bin/bash`. 
You should be able to see the container id (e.g., 9622fd5a60f8) when running the container.
By typing `exit` or with a `CTRL+D` key, you can exit the container.
However, all changes made will be gone because an `--rm` option 
will remove all jobs you've done upon exiting the container.
```
$ docker run --rm -it esw4010 /bin/bash
root@9622fd5a60f8:/# exit
```

More practically, let us run our docker image without the `--rm` option.
Now you will see a new container id (e.g., d8a574ada8a3).
```
$ docker run -it esw4010 /bin/bash
root@d8a574ada8a3:/# cd ~
root@d8a574ada8a3:~# ls -l
total 4
drwxr-xr-x 4 root root 4096 Mar 30 00:58 peda
```

If you want to keep running your container when getting out of the shell,
press `CTRL + p + q` in order (one by one). You can check that the docker image is 
still running with `docker ps`.
```
$ docker ps
CONTAINER ID   IMAGE     COMMAND       CREATED          STATUS          PORTS     NAMES
d8a574ada8a3   esw4010   "/bin/bash"   13 minutes ago   Up 13 minutes             relaxed_greider
```

If you want to go back to the container, use `docker exec` as follow. 
Your changes will be valid as long as the container is running.
```
$ docker exec -it d8a574ada8a3 bash
root@d8a574ada8a3:/# cd ~
root@d8a574ada8a3:~# vi vul.c
root@d8a574ada8a3:~# gcc -fno-stack-protector -z execstack -no-pie -o vul vul.c
root@d8a574ada8a3:~# ls -l
total 16
drwxr-xr-x 4 root root 4096 Mar 30 00:58 peda
-rwxr-xr-x 1 root root 7444 Apr  6 13:20 vul
-rw-r--r-- 1 root root  340 Apr  6 13:19 vul.c
root@d8a574ada8a3:~# file vul
vul: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=2c5d66b5298692febd2f5a9a5ec2449862f40195, not stripped
```

You can find general command line references for Docker here:
https://docs.docker.com/engine/reference/commandline/docker/



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
* You may write up what you have done in detail
* Answers for a few questions in homework assignment #2

