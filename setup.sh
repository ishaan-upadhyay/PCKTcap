sudo apt-get install libpcap-dev g++ make gnupg curl

# If MongoDB is not installed - check using which mongod
if [ -z "$(which mongod)" ]; then
    echo "MongoDB is not installed. Installing MongoDB..."
    curl -fsSL https://www.mongodb.org/static/pgp/server-8.0.asc |
        sudo gpg -o /usr/share/keyrings/mongodb-server-8.0.gpg \
            --dearmor

    . /etc/os-release

    if [[ "$VERSION_ID" == "22.04" ]]; then
        echo "deb [ arch=amd64,arm64 signed-by=/usr/share/keyrings/mongodb-server-8.0.gpg ] https://repo.mongodb.org/apt/ubuntu jammy/mongodb-org/8.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-8.0.list
    elif [[ "$VERSION_ID" == "20.04" ]]; then
        echo "deb [ arch=amd64,arm64 signed-by=/usr/share/keyrings/mongodb-server-8.0.gpg ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/8.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-8.0.list
    else
        echo "Version not supported"
    fi

    sudo apt-get update
    sudo apt-get install -y mongodb-org

    # Install C++ driver for MongoDB
    curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r4.0.0/mongo-cxx-driver-r4.0.0.tar.gz
    tar -xzf mongo-cxx-driver-r4.0.0.tar.gz
    cd mongo-cxx-driver-r4.0.0/build

    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_STANDARD=17 \
        -DCMAKE_INSTALL_PREFIX=/usr/local

    cmake --build .
    sudo cmake --build . --target install

    cd ../..
    rm -rf mongo-cxx-driver-r4.0.0
    rm mongo-cxx-driver-r4.0.0.tar.gz
else
    echo "MongoDB is already installed."
fi
