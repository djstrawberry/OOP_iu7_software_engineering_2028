#ifndef RESULT_H
#define RESULT_H

#include <QMainWindow>
#include <QMessageBox>

typedef enum
{
    OK_CODE,
    MEMORY_ERROR_CODE,
    FILE_ERROR_CODE,
    FORMAT_ERROR_CODE,
    NULLPTR_ERROR_CODE,
    RANGE_ERROR_CODE,
    EMPTY_ERROR_CODE,
    UNKNOWN_ERROR_CODE
} result_t;

result_t show_error(result_t ec, QMainWindow *window);

namespace ErrorMessage
{
    inline const char *MEMORY_ERROR_TITLE = "Ошибка работы с памятью";
    inline const char *MEMORY_ERROR_TEXT = "Произошла ошибка при работе с памятью.";

    inline const char *FILE_ERROR_TITLE = "Ошибка работы с с файлом";
    inline const char *FILE_ERROR_TEXT = "Произошла ошибка при работе с файлом.";

    inline const char *FORMAT_ERROR_TITLE = "Ошибка формата";
    inline const char *FORMAT_ERROR_TEXT = "Произошла ошибка формата, проверьте входные данные: скорее всего, они невалидны.";

    inline const char *NULLPTR_ERROR_TITLE = "Ошибка работы с указателем";
    inline const char *NULLPTR_ERROR_TEXT = "Произошла ошибка работы с указателем.";

    inline const char *RANGE_ERROR_TITLE = "Выход за диапазон допустимых значений";
    inline const char *RANGE_ERROR_TEXT = "Произошел выход за диапазон допустимых значений.";

    inline const char *EMPTY_ERROR_TITLE = "Пустая фигура";
    inline const char *EMPTY_ERROR_TEXT = "Кажется, фигура пуста.";

    inline const char *UNKNOWN_ERROR_TITLE = "Неизвестная ошибка";
    inline const char *UNKNOWN_ERROR_TEXT = "Произошла неизвестная ошибка.";
}

#endif // RESULT_H