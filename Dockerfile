# Multi-platform base image with Java, Python3, C++ compiler
FROM --platform=$BUILDPLATFORM eclipse-temurin:17-jdk-jammy

# Install system dependencies
RUN apt-get update && apt-get install -y \
    git \
    python3 \
    python3-pip \
    python3-dev \
    g++ \
    gcc \
    make \
    cmake \
    build-essential \
    curl \
    bash \
    ant \
    && rm -rf /var/lib/apt/lists/*

# Install Python modules
RUN pip3 install --no-cache-dir \
    matplotlib \
    pandas \
    numpy

# Set working directory
WORKDIR /workspace

# Copy entrypoint script
COPY entrypoint.sh /entrypoint.sh
COPY . /workspace/
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]