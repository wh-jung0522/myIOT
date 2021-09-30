# IOTProject

## Firewall Problem

    systemctl stop firewalld

or
    
    sudo ufw allow PORT1 ## for PictureServer
    sudo ufw allow PORT2 ## for WebServer


## Complie

    cd PictureServer
    bash compile.sh

## Execute Picture Server

    ./Server

## Execute Web Server (Debug mode) 

    cd ..
    cd WebServer
    php -f ./index.php -S 0.0.0.0:PORT2

## Android Application

.zip file -> extract, android studio build