FROM debian:latest

ARG USER
ARG USER_ID
ARG GROUP_ID
RUN addgroup --gid $GROUP_ID $USER
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID $USER

WORKDIR /usr/src/cucumber-cpp

RUN apt-get update && \
    apt-get -y install cmake build-essential \
                       libboost-test-dev \
                       git \
                       libboost-program-options-dev \
                       libboost-system-dev \
                       nlohmann-json3-dev \
                       ruby \
                       ruby-dev

RUN git clone https://github.com/cucumber/cucumber-cpp.git . && \
    git checkout 01d24e8b4f07f4abb2c13a21311431f792d4bccd

RUN gem install bundler && \
    bundle install

RUN cmake -E make_directory build && \
    cmake -E chdir build cmake -DCUKE_ENABLE_EXAMPLES=on -DCMAKE_INSTALL_PREFIX=${prefix} .. && \
    cmake --build build && \
    cmake --build build --target test && \
    cmake --build build --target install


# Platformio setup
# see: https://docs.platformio.org/en/latest/core/installation/methods/pypi.html
# see: https://docs.platformio.org/en/latest/core/installation/udev-rules.html => why is my docker container a "broken system"?
RUN apt-get -y install python3-pip curl && \
    python3 -m pip install -U platformio --break-system-packages && \
    curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | tee /lib/udev/rules.d/99-platformio-udev.rules

# switch to non-root user
USER $USER

# Platformio packages with correct user
RUN pio pkg install -g \
    -p platformio/espressif8266@4.2.1 \
    -t platformio/framework-arduinoespressif8266@3.30102.0 \
    -t platformio/tool-mkspiffs@1.200.0 \
    -t platformio/tool-mklittlefs@1.203.210628 \
    -t platformio/tool-scons@4.40502.0
