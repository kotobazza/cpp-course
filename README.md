# CICD для CPP

+ Задачи
    + Использование GTest вместо libboost
    + Как использовать ClangFormat в VSCode?




+ Окружение
    + кодировки
    + форматирования (чаще всего используется CLangFormat)
        + Нужно посмотреть, как сделать оформление кода в VSCode на оснвое CLangFormat
    + Документация 
        + Писать документацию к классам и функциям (в частности инструмент doxygen)
    + Code style (struct VS class, exceptions)
        + Здесь выделено отдельно - форматирование и кодстайл. Кодстайл относится к используемым принципам языка
        + Как пример
            + Не надо использовать приватное наследование, вместо него использовать композицию классов
    + Сборка проектов
        + Печаль с переносом кода и процессов сборки туда-сюда
        + Для платформонезависимости - использование *CMake*
            + src содержит "вроде бы" неплохой дефолтный компонентер

+ Так, ну, проблемы с наличием у меня Boost - совсем другое дело, опустим



+ release.yml
    + Во-первых, благодаря GPT переписал использование ubuntu->смешанное использование ubuntu+fedora (ubuntu будет дальше использоваться для GithubActions, но внутренний кусок CMake для запуска проекта у меня должен собирать пакет для RPM)
        + Использует `boost-devel` на моей машине (ставлю пока сам) - на ubuntu остается libboost-test
        + Для сборки проекта дополнительно указывается ключ `-DCMAKE_GENERATOR`
            + Основная опция - RPM (для моей работы)
            + В остальном будет собирать для deb
            + Опция убрана из release.yml
        + Этот ключ проверяется в CMakeLists
        + ? Почему libboost?
            + Показывают, как ставить зависимости, другие фреймворки тестирования удобнее ставить другими средствами
                + ?? Как поставить GTest?

    + Во-вторых, объяснение самого файла
        + Для тригерра пуша в ветки master и feature выполняется основная задача сборки и тестирования (объединенная задача со всеми компонентами)
        + Основные задачи по тестированию и формированию пакета делает сама CMake
            + test - запускает тесты (`boost-test`)
            + package - собирает пакет нужным образом для дистрибутива (у меня пока стоит RPM в Fedora-cmake, но если что я могу объединить их в одно целое)

    + В третьих - токены
        + Для запуска контейнеров также нужны токены Github, у меня действующий токен - `repos`, его имя и нужно указывать в `GITHUB_TOKEN` в настройках репозитория
            + Вообще здесь появляется определенная сложность использования этих самых токенов
            + Токены вносятся в Secrets внутри настроек самого репозитория


+ CMakeLists
    + `CMAKE_BINARY_DIR` - директория, откуда был запущен CMake. Если ее подключить к проекту, то CMake сможет тяпать собираемые в директории `build` библиотеки и подключать их к проекту
    + С помощью CMake можно выставлять `#define`
        + `set_target_properties(target PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK ...)`
            + эквивалентно `#define BOOST_TEST_DYN_LINK`
                + Само включение нужно чтобы позволить `boost_test` искать динамические либки
    + Сборка пакетов
        + Для сборки пакетов в CMake используется `CPack`. В последних строчках он как раз подключается, и использует выше поставленные переменные для выполнения своей работы над `helloworld-cli`
        + Далее можно использоввать `--target package` при сборке с помощью CMake (как раз происходит в release.yml)
    + Тестирование
        + `enable_testing()`
        + Некоторый бинарник регистрируется в качестве цели сборки для тестирования. Затем можно использовать `--target test` для проведения тестирования средствами CMake + Boost
    + Версионирование
        + Кроме применения текста из CMakeLists, также значения переменных можно передавать с помощью комнадной строки при запуске. 
        + Дефолтно этот бинарник использует `PATCH_VERSION=1`, но в `release.yml` уже передается другая версия - которая получается из синтаксиса акшенов самого Github 
+ Использование `.in` файла
    + Позволяет CMake дополнительно взаимодействовать с C++
        + Делается с помощью `configure_file`
    + Вставляет `#define` с использованием переменных, созданных самим CMake
        + `#cmakedefine`
    + incomplete - фактически расширение может быть любым, CMake на эти расшрения без разницы