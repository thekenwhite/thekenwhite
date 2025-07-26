
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

export using strv  = std::string_view;
export using wstrv = std::wstring_view;

export using str16 = std::u16string;
export using str32 = std::u32string;

export using str16v = std::u16string_view;
export using str32v = std::u32string_view;

export template<typename T, size_t N>
using arr = std::array<T, N>;

export template<typename T>
using vec = std::vector<T>;
