#pragma once
// ConsoleUtf8.hpp: автоматически включает вывод UTF-8 в консоли (чинит "┬▒" вместо "±").
// Достаточно написать #include "ConsoleUtf8.hpp" в main.cpp, вызывать ничего не нужно.
// Windows: переключает кодовую страницу ВЫВОДА консоли на UTF-8 и возвращает старую при выходе.
// Linux/macOS: ничего делать не нужно, терминалы уже работают в UTF-8.
// Требует C++17 (inline-переменная внизу файла).

#ifdef _WIN32                      // только Windows (MinGW, MSVC)
  #ifndef NOMINMAX
    #define NOMINMAX               // чтобы макросы min/max из windows.h не ломали Au и std
  #endif
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN    // меньше лишнего из windows.h
  #endif
  #include <windows.h>             // SetConsoleOutputCP, GetConsoleOutputCP (идёт вместе с компилятором)
#endif

namespace console_utf8 {

#ifdef _WIN32
struct Guard {
    UINT oldOut;                                // кодовая страница вывода до запуска (0 = консоли нет)
    Guard() : oldOut(GetConsoleOutputCP()) {
        if (oldOut != 0) SetConsoleOutputCP(CP_UTF8);   // вывод в UTF-8 (чинит "±"); ввод не трогаем
    }
    ~Guard() {
        if (oldOut != 0) SetConsoleOutputCP(oldOut);    // вернуть как было, чтобы не портить окно cmd
    }
};
#else
struct Guard {};                                // Linux/macOS: ничего не делаем
#endif

inline Guard guard;                             // создаётся до main() и удаляется после выхода (C++17)

} // namespace console_utf8