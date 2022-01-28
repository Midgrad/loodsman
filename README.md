[![Build and test](https://github.com/Midgrad/loodsman/actions/workflows/build_test.yml/badge.svg)](https://github.com/Midgrad/loodsman/actions/workflows/build_test.yml)
[![Static analysis](https://github.com/Midgrad/loodsman/actions/workflows/static_analysis.yml/badge.svg)](https://github.com/Midgrad/loodsman/actions/workflows/static_analysis.yml)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=Midgrad_loodsman&metric=alert_status)](https://sonarcloud.io/summary/overall?id=Midgrad_loodsman)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=Midgrad_loodsman&metric=coverage)](https://sonarcloud.io/summary/overall?id=Midgrad_loodsman)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=Midgrad_loodsman&metric=code_smells)](https://sonarcloud.io/summary/overall?id=Midgrad_loodsman)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=Midgrad_loodsman&metric=bugs)](https://sonarcloud.io/summary/overall?id=Midgrad_loodsman)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=Midgrad_loodsman&metric=duplicated_lines_density)](https://sonarcloud.io/summary/overall?id=Midgrad_loodsman)

# loodsman

Cross-platform udp,tcp and serial connection library

# Build

Tested on Ubuntu 20.04, Windows server 2016 and macOS 11. Although this lib support cross-platfom build, it's
recommended to use GNU/Linux for development in order to avoid time loss on issues such
as [this](https://github.com/conan-io/conan/issues/8402).

If using conan:

- install python3
- `pip3 install conan`
- `conan profile new default --detect`
- Apply conan profile modification if necessary
    - On Linux: conan profile update settings.compiler.libcxx=libstdc++11 default
    - On Windows: conan profile update settings.compiler.runtime=MD default
- Choose your build type and append `-s build_type=Release` or `-s build_type=Debug` to the next conan install command
    - `cd conan` & `conan install . --install-folder=../deps`

Alternatively on Linux and macOS You can just install all deps manually using apt or homebrew or build everything from
source and place it in deps folder.

- `mkdir build` & `cd build`
- `cmake ..` or `cmake .. -DLOODSMAN_TESTS_ENABLED=ON`
- `cmake --build`