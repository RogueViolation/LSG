FROM ubuntu:24.04

RUN dpkg --add-architecture i386 \
    && sed -i 's/Components: main/Components: main universe/' /etc/apt/sources.list.d/ubuntu.sources \
    && apt-get update \
    && apt-get upgrade -y \
    && apt-get install -y lib32stdc++6 libatomic1 libssl3 libssl3:i386 libatomic1:i386 gettext moreutils python3 pip \
    && rm -rf /var/lib/apt/lists/*

RUN pip install mysql-connector-python --break-system-packages

RUN rm -rf /etc/localtime && ln -s /usr/share/zoneinfo/Europe/Vilnius /etc/localtime

WORKDIR /omp
COPY /bin /omp/
COPY /npcmodes /omp/npcmodes
RUN chmod 777 /omp/omp-server /omp/samp-npc /omp/run.sh
COPY /filterscripts/onlinercon.amx /filterscripts/gCamera.amx /filterscripts/winter.amx /omp/filterscripts/
COPY /gamemodes/LSG.amx /omp/gamemodes/

ENTRYPOINT [ "sh", "run.sh" ]