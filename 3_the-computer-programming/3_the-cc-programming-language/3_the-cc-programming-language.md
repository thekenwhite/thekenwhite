
# The C++ Programming Language

우선 고전적인 C++ 프로젝트에 구조에 대해서는 거의 손댈 것이 없다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.cc`
- `inc/`
	- `_.h`
- `lib/`
	- `.gitignore`
- `src/`
	- `_.cc`
- `CMakeLists.txt`
- `clean.sh`
- `cmake.sh`
- `setup.sh`

CMake C 프로젝트에서 파일 확장자만 `.cc`로 바꿔줘도 정상적으로 작동한다.

다만 C++ 스타일에 맞춰서 일부 내용은 바꾸도록 하겠다.

일단은 역시 주로 int/1/0 이것을 bool/true/false 이 형태로 바꾸는 게 주 작업이 될 것 같다.

그리고 `printf`를 사용하던 출력도 `std::cout`과 `std::endl`로 바꿀 것이다.

`bin/_.cc`의 경우 다음과 같다.

```cpp
#include "_.h"

int main() {
    bool alive = startup();

    while (alive) {
        alive = running();
    }
    
    return shutdown();
}
```

`inc/_.h`의 경우 다음과 같다.

```cpp
#pragma once

bool startup();
bool running();
int shutdown();
```

`src/_.cc`의 경우 다음과 같다.

```cpp
#include <iostream>

#include "_.h"

bool alive;

int countdown;

int exit_code;

bool startup() {
    std::cout << "Starting up..." << std::endl;
    alive = true;
    countdown = 3;
    return true;
}

bool running() {
    std::cout << "Countdown: " << countdown << "..." << std::endl;
    
    countdown -= 1;
    
    if (countdown > 0) {
        alive = true;
    } else {
        alive = false;
    }

    return alive;
}

int shutdown() {
    exit_code = 0;
    std::cout << "Shutting down with: " << exit_code << std::endl;
    return exit_code;
}
```

다음 커맨드를 실행한다.

```sh
sh cmake.sh
```

출력 결과는 다음과 같다.

```
Starting up...
Countdown: 3...
Countdown: 2...
Countdown: 1...
Shutting down with: 0
```

이것만으로도 대부분의 코딩은 역시 C와 동일하게 가능하다.

다만 여기서 주력으로 설명할 부분은 C++의 모듈이라는 기능이다.

C++에 한해서, C 프로젝트와는 다르게 `mod`라는 폴더를 만들 것이다.

기본적으로 역할은 `src` 폴더와 비슷하나, 모듈 방식을 쓰는 걸로 한정한다는 특징이 있다.

사실 `src` 폴더에서 모듈 기능이 작동하게 해도 되기는 하지만, 둘이 스타일이 상당히 다르기 때문에 구분용으로 src와 mod를 분리한다.

특히 src 폴더의 경우 inc 폴더와 매칭을 이루려고 하는 것에 반해, mod 폴더의 경우 헤더 파일을 최대한 쓰려 하지 않는다는 점이 다르다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.cc`
	- `mod.cc`
- `inc/`
	- `_.h`
- `lib/`
	- `.gitignore`
- `mod/`
	- `_.cc`
- `src/`
	- `_.cc`
- `CMakeLists.txt`
- `clean.sh`
- `cmake.sh`
- `setup.sh`

`CMakeLists.txt`에 대해서 먼저 알아볼 거다.

방식은 이렇다. `mod` 파일만 또 따로 스캔을 해서 `src` 폴더처럼 또 하나의 라이브러리로 만든다. 그런데, C++ 모듈을 사용할 수 있게끔 세팅을 한다는 것이 차이점이다.

```cmake
cmake_minimum_required(VERSION 4.0)

project(cmake)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

include_directories(inc)

file(GLOB_RECURSE bin_files bin/*)

file(GLOB_RECURSE src_files src/*)

file(GLOB_RECURSE mod_files mod/*)

add_library(src_lib ${src_files})

add_library(mod_lib)

target_sources(mod_lib
    PUBLIC FILE_SET CXX_MODULES
    FILES ${mod_files}
)

foreach(bin_file ${bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_link_libraries(${bin_name} src_lib)
    target_link_libraries(${bin_name} mod_lib)
endforeach()
```

그리고 `mod/_.cc`는 다음과 같이 구성한다.

```cpp
module;

#include <iostream>

export module mod;

export void run() {
    std::cout << "Hello, World!" << std::endl;
}
```

마지막으로 `bin/mod.cc`는 다음과 같이 구성한다.

```cpp
import mod;

int main() {
    mod:run();
    return 0;
}
```

다음 커맨드를 실행한다.

```sh
sh cmake.sh mod
```

그럼 다음과 같은 결과를 얻을 수 있다.

```
Hello, World!
```

다만 이는 전통적인 C++ 방식과는 상당히 달라서, 폴더 구조에 대해 좀 더 추가적으로 설명이 필요할 것 같다.

우선 C++ 모듈에서 계층형 구조를 만드는 방법이 두 가지가 있다.

- 콜론(`:`)을 쓰는 실제 모듈 파티션 (계층 형태를 계속 이어갈 순 없다.)
	- `export module mod:submod;`
- 점(`.`)을 쓰는 형식적인 모듈 계층 (계층 형태를 계속 이어갈 수 있다.)
	- `export module mod.submod;`

이때 점을 쓰는 것은 이름으로만 계층적인 모듈 형태로 보일 뿐이다.

실제로는 그 모듈 자체가 점까지 포함해 전부 다 모듈 이름인 것처럼 취급해야 한다.

예를 들어, 모듈 파티션은 다음과 같이 실제로 계층형으로 코드를 작성할 수도 있다.

```cpp
export module mod;

import :submod;
```

그러나 이런 형태를 계속 이어갈 수는 없다. 예를 들어 `submod` 아래에 또 `subsubmod`가 존재할 수는 없다.

점을 사용하는 가짜 계층은 다음과 같이 사용해야 한다.

```cpp
export module mod;

import mod.submod;
```

말이 계층이지, 사실상 점까지 포함해 `mod.submod` 자체가 그 모듈의 이름인 것처럼 사용하고 있는 것을 볼 수 있다. 정말로 그냥 형식적인 계층인 것에 불과하다.

따라서 일단은 형식적인 계층 형태로 이어가다가, 정 필요하다 싶을 때 모듈 파티션 기능을 사용하는 것이 좋을 것이다.

그리고 헤더가 헤더를 포함하는 것이 가능하듯이, 모듈이 모듈을 다시 내보내는 것도 가능하다.

```cpp
export module mod;

export import othermod;
```

이렇게 하면 `mod`라는 모듈을 불러오기만 해도 자동으로 `othermod`라는 모듈까지 가져오는 효과를 낸다.

이런 모듈 방식에는 장점이 있다.

원래 헤더 같았으면 계속해서 define 된 것들이 이어지면서 사용자의 코드를 방해하는 감이 좀 없잖아 있다.

그러나 이렇게 하면 헤더의 내용을 전부 다 포함하는 것이 아니라, 필요한 내용만 받는 것이 가능하다.

그리고 함수 선언, 함수 구현, 이런 식으로 나눠서 귀찮아지게 되는 일도 없다.

위에서 모듈의 함수를 부를 때 `mod:run();`이라고 쓰기는 했는데, 사실 무슨 모듈인지 명시하지 않아도 된다. `run();`만 쳐도 돌아가기는 한다.

그래서 여기서 좀 더 모듈스럽게 쓰는 방법이 있는데, 바로 `namespace`를 쓰는 것이다.

```cpp
export module mod.submod;

namespace mod::submod {

	void function() {
		// ...
	}

} // namespace mod::submod
```

이러면 다음과 같은 사용이 가능해진다.

```cpp
export module mod;

import mod.submod;

export namespace mod {

	void run() {
		submod::function();
	}

} // namespace mod
```

모듈의 함수를 편하게 쓰고 싶으면 다음과 같이 쓰면 된다.

```cpp
export module mod;

import mod.submod;

export namespace mod {

	using namespace submod;

	void run() {
		function();
	}

} // namespace mod
```

이는 `namespace` 기능 자체가 이미 형식적으로는 계층형 구조를 설계할 수 있게 도와주기 때문이다.

좀 번거롭긴 하겠지만, 어쨌든 이렇게 하면 좀 더 안정적인 모듈 설계가 가능하다.

러스트도 이런 느낌과 비슷하다. 다만 당연히 좀 더 정돈된 느낌이다.

말 나온 김에 좀 더 러스트 같이 쓰는 방법을 얘기하자면, `int` 같은 자료형을 `i32`로 바꾸면 된다.

`mod/type.cc`를 다음과 같이 구성한다고 가정해 본다.

```cpp
module;

#include <cstdint>
#include <string>
#include <array>
#include <vector>

export module type;

export using i8    = std::int8_t;
export using i16   = std::int16_t;
export using i32   = std::int32_t;
export using i64   = std::int64_t;
export using isize = std::intptr_t;

export using u8    = std::uint8_t;
export using u16   = std::uint16_t;
export using u32   = std::uint32_t;
export using u64   = std::uint64_t;
export using usize = std::uintptr_t;

export using f32 = float;
export using f64 = double;

export using ch  = char;
export using wch = wchar_t;

export using ch16 = char16_t;
export using ch32 = char32_t;

export using str  = std::string;
export using wstr = std::wstring;  

export using strv  = std::string_view;
export using wstrv = std::wstring_view;

export using str16 = std::u16string;
export using str32 = std::u32string;

export using str16v = std::u16string_view;
export using str32v = std::u32string_view;

export template<typename T, size_t N>
using arr = std::array<T, N>;

export template<typename T>
using vec = std::vector<T>;
```

위 모듈을 쓰는 예시는 다음과 같다.

```cpp
#include <iostream>

import type;

void run() {
    static const i32 size = 3;

    arr<strv, size> words;
    strv space = " ";

    words[0] = "Hello,";
    words[1] = space;
    words[2] = "World!";

    for (auto& s : words) {
        std::cout << s;
    }

    std::cout << std::endl;
}
```

결과물은 다음과 같다.

```
Hello, World!
```

프로젝트 구조를 다시 정리해 보겠다.

- `.cmake/`
	- `.gitignore`
- `bin/`
	- `_.cc`
- `inc/`
	- `_.h`
- `lib/`
	- `.gitignore`
- `mod/`
	- `_.cc`
- `src/`
	- `_.cc`
- `CMakeLists.txt`
- `clean.sh`
- `cmake.sh`
- `setup.sh`

어떤가? 이전에 C 프로젝트 구조를 유용하게 쓸 수 있었던 것처럼, 이번에도 C++의 기능을 편리하게 이용할 수 있는 구조가 형성되었다.

원래 러스트 같은 경우 모듈을 그냥 만들어도 외부에서 쓰려면 라이브러리 이름까지 붙여야 한다.

그러니까 라이브러리 이름이 `lib`면, `lib::mod`와 같이 모듈 이름을 불러와야 한다.

하지만 C++은 그런 기능이 없다. 그것까지 흉내내려면 최상위 모듈 이름을 하나 정해놓고, 그 이름을 모든 모듈의 앞에 굳이 붙여야 한다.

그런데 자동으로 알아서 그렇게 되는 것도 아니라면, 굳이 그래야 하는 이유가 있나 싶다.

그래서 C++의 경우 그렇게 하지 말고, 그냥 다음과 같이 바이너리 파일에선 바로 쓰길 바란다.

```cpp
import _;

int main() {
    run();
    return 0;
}
```

그리고 `mod/_.cc` 파일은 이렇게 설정해두는 것이다.

```cpp
module;

#include <iostream>

export module _;

import type;

export {
    void run();
    void hello();
}

void run() {
    hello();
}

void hello() {
    strv hello = "Hello, World!";
    std::cout << hello << std::endl;
}
```

이 상태에서 모듈 파일을 추가로 만들 일이 있을 때, 그때 모듈 구조와 네임스페이스 구조를 거기서부터 시작하는 것을 추천한다. 굳이 라이브러리 전체를 하나의 모듈이나 하나의 네임스페이스로 묶으려고 하지 말고 말이다.

해당 프로젝트 구조가 필요하면 이 리포지토리의 `.projects/cc` 폴더를 알아보길 바란다.

그런데 사실, 이런 것들은 전부 다 C나 C++를 억지로 쓸 만하게 만들려는 시도에 가깝다고 본다.

내가 추천하는 것은 그냥 Rust를 익히는 것이다.

다음 글에서는 Rust에 대해서 알아보도록 하겠다.
