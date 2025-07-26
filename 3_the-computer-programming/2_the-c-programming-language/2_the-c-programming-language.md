
# The C Programming Language

```c
#include <stdio.h>

int main() {
    printf("Hello, World!");

    return 0;
}
```

C는 본디 Unix 운영체제와 함께 태어난 언어다. 그래서 C를 좀 더 제대로 쓰려면 Unix-like 운영체제에서 쓰는 것이 좀 더 정신건강에 편하다.

MS Windows의 경우 C를 제대로 지원해주지 않는다.

그리고 GUI 방식의 프로그래밍에 자꾸 익숙해지는 것도 문제가 있다고 본다.

Linux 유저라면 gcc를 설치해라. 그리고 Windows 유저라면 MSYS2라는 것을 설치해라. WSL이란 것도 있긴 한데, WSL은 아무래도 Windows 파일 시스템과 직접 소통하기에는 별로 좋지는 않다.

MSYS2를 설치하면 MINGW64, UCRT64 등 다양한 버전이 보일 것이다. 내가 추천하는 것은 MINGW64다. 구글 검색을 할 경우 자주 나오는 것도 MINGW64고, Git Bash를 실행해 보면 기본적으로 실행하고 있는 것도 MINGW64다.

시스템 환경 변수에서 `C:\msys64\mingw64\bin`을 Path에 추가하길 바란다. 그러면 gcc 같은 것을 설치했을 때 커맨드로 사용할 수 있게 된다. 다만 MINGW64로 설치한 것만 쓸 수 있다.

MSYS2는 pacman이라는 패키지 매니저를 사용한다. Arch Linux가 사용하는 패키지 매니저와 같은 패키지 매니저다. 그리고 말 나온 김에 말하자면 리눅스 배포판도 아치 리눅스를 추천한다.

pacman도 편하게 쓰려면 환경 변수의 Path에 다음을 추가해라:

- `C:\msys64\usr\bin`

MSYS2든 아치 리눅스든, pacman이 설치된 후에는 `pacman -Syu` 같은 커맨드나, `pacman -Syyu` 같은 커맨드를 한번 돌려놓기를 바란다. 패키지를 업데이트하는 커맨드다.

사실 그렇게까지 필수적인 커맨드는 아니지만, 간혹 지나치게 오래된 것이 있으면 가끔 문제가 생길 수도 있다.

아치 리눅스의 경우 pacman에 sudo가 필요할 수 있다. 루트 계정이라면 sudo가 필요 없다.

또, 최근에는 WSL에 archlinux도 추가가 됐다. WSL을 설치하면 기본적으로 우분투가 깔리려고 할 텐데, 우분투와 아치 리눅스 둘 다 쓰길 바란다. 어차피 서버 배포 같은 걸 해야 할 때 우분투 같은 걸 써야 할 수도 있다. WSL은 쓸 일 자체가 잘 없다. 그러니 그냥 우분투를 기본으로 놓고 쓰기를 바란다. WSL보다는 Git Bash를 사용하는 것을 추천한다. 여전히 Unix-like 기반의 커맨드들을 사용할 수 있다. 특히 MSYS2 패키지에 pacman까지 Git Bash에서 바로 사용하면 거의 Unix, 특히 아치 리눅스와 같은 경험이 난다.

MSYS2에 있는 GCC의 패키지명은 다음과 같다:

- `mingw-w64-x86_64-gcc`

그리고 이를 설치하는 커맨드는 다음과 같다:

```sh
pacman -S mingw-w64-x86_64-gcc
```

이는 C뿐만 아니라 C++도 컴파일할 수 있게 해준다. C의 커맨드는 `gcc`, C++의 커맨드는 `g++`이다.

Clang이라는 것도 있기는 하다. Clang의 경우 C는 `clang`, C++는 `clang++`이다. GCC가 GNU 쪽에서 만든 컴파일러라면, Clang은 애플 쪽에서 만든 컴파일러다.

```sh
pacman -S mingw-w64-x86_64-clang
```

기본적인 동작을 하는 데에는 그 어떤 것도 그다지 큰 차이는 없다. 다만 슬슬 최신 기능을 쓰려고 할 때부터 차이가 제대로 갈리기 시작한다.

또, Visual Studio를 쓰려고 하지 않는 경우 CMake가 거의 필수적이다. 이건 Windows 버전을 설치할 수도 있고, MSYS2 버전을 설치할 수도 있다.

어느 것을 사용해도 그렇게 큰 차이는 없겠지만, 이제부터는 가능한 한 그냥 MSYS2를 사용하기를 바란다. 그 편이 좀 더 생각하기에 편할 테니까. 그리고 리눅스, 특히 아치 리눅스의 방식도 그런 쪽에 더 가깝기도 하고.

```sh
pacman -S mingw-w64-x86_64-cmake
```

필요하면 Make 및 Ninja란 것들을 설치할 수도 있다. 이들 역시 자주 쓰이는 빌드 시스템이다.

```sh
pacman -S mingw-w64-x86_64-make mingw-w64-x86_64-ninja
```

이제부터 C 코딩을 할 수 있다.

터미널 셸에서 `nano` 같은 에디터만 써도 어찌 코딩은 진행할 수 있지만, 정 GUI 에디터가 필요하다면 그냥 VS Code를 써라.

파일 구성은 다음과 같이 하기를 바란다.

- `bin/`
	- `_.c`
- `inc/`
	- `_.h`
- `src/`
	- `_.c`
- `CMakeLists.txt`
- `cmake.sh`

언더바를 쓰는 이유는, 저것을 기본으로 쓰겠다는 의미다. Rust에서 착안한 방식이다.

저렇게 하면 기본 외의 추가적인 것들은 전부 언더바 밑으로 잡히기 때문에 나쁘지 않다.

이제 `CMakeLists.txt`의 파일 내용을 구성할 것이다.

일단 알아둘 것은, Unix의 경우 파일이 빌드 폴더 안에서 단순히 `main` 이렇게 생기는 것에 반해, Windows의 경우 다음과 같이 나뉘게 된다는 것이다:

- `Debug/main.exe`
- `Release/main.exe`
- `x64/Debug/main.exe`
- `x64/Release/main.exe`

Windows의 경우 exe가 붙어 있긴 한데, 저 부분을 생략해도 해당 파일을 실행시킬 수 있다.

그래서 한 폴더로 밀어넣기만 하면 동일한 커맨드, 동일한 스크립트로 바이너리 파일을 실행시킬 수 있다.

따라서, 바이너리 파일들이 전부 `output/main`과 같은 형태가 되도록 만들 것이다.

나머지는 CMake의 프로젝트에 자체적으로 필요한 것들이다.

`CMakeLists.txt`의 내용은 다음과 같다.

```cmake
# CMake의 최소 버전을 4.0으로 설정
cmake_minimum_required(VERSION 4.0)

# 프로젝트명은 cmake로 지정
project(cmake)

# 결과물 파일의 생성 위치를 일관되게 설정

## 런타임 바이너리 파일
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

## 정적 라이브러리
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

## 동적 라이브러리
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

# 프로젝트 헤더 파일 위치
include_directories(inc)

# 바이너리용 소스파일 스캔
file(GLOB_RECURSE bin_files bin/*)

# 라이브러리용 소스파일 스캔
file(GLOB_RECURSE src_files src/*)

# 라이브러리 생성
add_library(lib ${src_files})

# 바이너리 각각에 연결
foreach(bin_file ${bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_link_libraries(${bin_name} lib)
endforeach()
```

이제 이 `CMakeLists.txt` 파일을 `cmake.sh`로 실행시킬 것이다.

`cmake.sh`의 내용은 다음과 같다.

```sh
cmake -S . -B .cmake/target &&
cmake --build .cmake/target &&
if [ $# -eq 0 ]; then
    .cmake/output/_
else
    .cmake/output/$1
fi
```

이 파일은 다음과 같이 활용할 수 있다.

```sh
# 기본 바이너리 파일을 실행하는 경우
sh cmake.sh

# 특수 바이너리 파일을 실행하는 경우
sh cmake.sh hello
```

이 과정을 거치면 `.cmake/target`에 빌드 파일, `.cmake/output`에 결과물 파일들이 생성될 것이다.

이들을 Git에 포함시키지 않기 위해 `.cmake/.gitignore`를 만들 것이다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.c`
- `inc/`
	- `_.h`
- `src/`
	- `_.c`
- `CMakeLists.txt`
- `cmake.sh`

`.cmake/.gitignore`의 내용은 다음과 같이 쓴다.

```
/output
/target
```

이제 프로젝트에 필요한 코드들을 적어보겠다.

유저용 백지 상태를 만드는 데 필요한 파일과 예제용 Hello World 코드에 필요한 파일들을 분리하도록 하겠다.

우선 백지 상태를 만드는 방법부터 알아보겠다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.c`
- `inc/`
	- `_.h`
- `src/`
	- `_.c`
- `CMakeLists.txt`
- `cmake.sh`

`bin/_.c` 파일을 다음과 같이 구성한다.

```c
#include "_.h"

int main() {
    int alive = startup();

    while (alive > 0) {
        alive = running();
    }
    
    return shutdown();
}
```

`inc/_.h` 파일을 다음과 같이 구성한다.

```c
#pragma once

int startup();
int running();
int shutdown();
```

`src/_.c` 파일을 다음과 같이 구성한다.

```c
#include <stdio.h>

#include "_.h"

int alive;

int countdown;

int exit_code;

int startup() {
    printf("Starting up...\n");
    alive = 1;
    countdown = 3;
    return 1;
}

int running() {
    printf("Countdown: %d...\n", countdown);
    
    countdown -= 1;
    
    if (countdown > 0) {
        alive = 1;
    } else {
        alive = 0;
    }

    return alive;
}

int shutdown() {
    exit_code = 0;
    printf("Shutting down with: %d\n", exit_code);
    return exit_code;
}
```

이제 인자 없이 `sh cmake.sh` 커맨드를 실행해 보면 다음과 같은 결과를 얻을 수 있다.

```
Starting up...
Countdown: 3...
Countdown: 2...
Countdown: 1...
Shutting down with: 0
```

프로젝트 위치를 옮기고 하다 보면 `sh cmake.sh`를 돌렸을 때 오류가 날 수도 있다. 그럴 때 `sh clean.sh` 같은 커맨드로 캐시 파일을 지울 수 있으면 편하다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.c`
- `inc/`
	- `_.h`
- `src/`
	- `_.c`
- `CMakeLists.txt`
- `clean.sh`
- `cmake.sh`

`clean.sh`의 파일 내용을 다음과 같이 만들어라.

```sh
rm -rf .cmake/output .cmake/target
```

이걸로 백지 상태의 프로젝트 템플릿을 어느 정도 만들었다.

이걸로도 이미 Hello World 급의 역할은 이미 수행하고 있긴 하지만, 파일을 여러 개 두는 경우의 예제를 보여주기 위해 hello 파일들도 만들도록 하겠다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.c`
	- `hello.c`
- `inc/`
	- `_.h`
	- `hello.h`
- `src/`
	- `_.c`
	- `hello.c`
- `CMakeLists.txt`
- `clean.sh`
- `cmake.sh`

`bin/hello.c`의 경우 다음과 같이 작성한다.

```c
#include "hello.h"

int main() {
    hello();
    return 0;
}
```

`inc/hello.h`의 경우 다음과 같이 작성한다.

```c
#pragma once

void hello();
```

`src/hello.c`의 경우 다음과 같이 작성한다.

```c
#include <stdio.h>

#include "hello.h"

void hello() {
    printf("Hello, World!\n");
}
```

이제 이번에는 hello 인자를 넣어서 cmake.sh를 실행한다.

인자의 이름은 `bin` 폴더 안에 있는 바이너리용 소스코드의 이름에 따라서 바뀐다.

즉, 기존 것이 기본적으로 `bin/_.c`를 실행시키는 커맨드였다면, 이는 `bin/hello.c`를 실행시키는 커맨드다.

```sh
sh cmake.sh hello
```

이는 구체적으로는 `.cmake/output/hello`를 실행시키고 있는 커맨드다.

그러면 다음과 같이 결과가 나올 것이다.

```
Hello, World!
```

추가적으로 프로젝트가 라이브러리를 가지게 하고 싶을 수 있다.

그럴 때에는 다음과 같이 `lib` 폴더를 만들면 된다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.c`
	- `hello.c`
- `inc/`
	- `_.h`
	- `hello.h`
- `lib/`
	- `<library_1>`
		- `(inc)`
		- `(lib)`
	- `<library_2>`
		- `(inc)`
		- `(lib)`
	- `.gitignore`
- `src/`
	- `_.c`
	- `hello.c`
- `CMakeLists.txt`
- `clean.sh`
- `cmake.sh`
- `setup.sh`

`lib` 폴더 안에 라이브러리용 프로젝트들을 넣고, 헤더파일은 inc에서, 라이브러리 파일은 lib에서 가져오면 될 것이다. 프로젝트마다 헤더파일이나 라이브러리 파일을 가져오는 구조는 다를 수 있다. 그리고 이렇게 라이브러리를 가져오려면 CMakeLists.txt를 필요에 맞게 수정하는 요령도 필요하다.

또, `lib/.gitignore` 같은 경우 지나치게 큰 프로젝트를 포함하고 싶지 않을 때 사용할 수 있다.

- `lib/`
	- `library_1`
	- `library_2`
	- `some_small_library`
	- `too_big_library`

이럴 때 `lib/.gitignore`를 다음과 같이 설정할 수 있다.

```
/library_1
/library_2
/too_big_library
```

이렇게 하면 `some_small_library`를 제외하고 나머지는 전부 무시한다.

그리고 프로젝트를 이제 막 설치했을 때, 다음과 같이 `setup.sh`를 사용하게 할 수 있다.

```sh
cd lib
git clone https://github.com/someone/library_1
git clone https://github.com/someone2/library_2
git clone https://gitlab.com/gitlabuser/too_big_library
cd ..
```

이쯤에서 프로젝트 구조를 다시 한번 정리하겠다.

- `.cmake/`
	- (`output/`)
	- (`target/`)
	- `.gitignore`
- `bin/`
	- `_.c`
	- `hello.c`
- `inc/`
	- `_.h`
	- `hello.h`
- `lib/`
	- `.gitignore`
- `src/`
	- `_.c`
	- `hello.c`
- `CMakeLists.txt`
- `clean.sh`
- `cmake.sh`
- `setup.sh`

이렇게 하면 대개 어느 상황에든 대응할 수 있는 CMake C 프로젝트 템플릿이 완성된다.

현재 리포에서는 `.projects/c` 폴더에서 확인할 수 있다.

장담하건대 이렇게 하는 것이 Visual Studio 프로젝트보다 훨씬 낫다.

그리고 이렇게 하면 Linux에서도 돌릴 수 있게 된다.

C 프로그래밍에 대한 얘기는 여기서 마치도록 하겠다.

C 프로그래밍이 더 궁금하다면 저 프로젝트 기반으로 bin, inc, src 파일들을 추가해 가며 한번 인터넷에 있는 예제를 따라해 보기를 바란다. 필요하면 lib 폴더에 프로젝트들도 추가하고.

그런데 라이브러리는 가능한 한 시스템에 깔기를 바란다.

프로젝트마다 일일이 까는 건, 사실 그렇게 권장되지는 않는 구조다.

그리고 메인 바이너리 파일에는 유의미한 CLI 툴을 만드는 것을 목표로 해 보기를 바란다.

running 함수를 첫 메인메뉴처럼 사용하면 나쁘지 않을 것이다.

그런데 사실 C++의 일부 특성 때문에, 차라리 부분적으로는 C++을 쓰는 게 나을 수도 있겠다는 생각도 든다.

대표적인 게 bool, true, false 대신에 int, 1, 0을 쓰는 점들 때문에 그렇다.

다음 글에서는 C++에 대해서 알아보도록 하겠다.
