TEMPLATE = app
TARGET = Set
QT += core widgets gui

CONFIG += c++20
QMAKE_CXXFLAGS += -std=c++20

# Папки проекта
HEADERS_DIR = inc
SOURCES_DIR = src
FORMS_DIR = forms

# Пути для компиляции
INCLUDEPATH += $$HEADERS_DIR

# Файлы проекта
SOURCES += $$files($$SOURCES_DIR/*.cpp)
HEADERS += $$files($$HEADERS_DIR/*.h) \
           $$files($$HEADERS_DIR/*/*.h) 
FORMS += $$files($$FORMS_DIR/*.ui)

# Папка для сборки
DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui