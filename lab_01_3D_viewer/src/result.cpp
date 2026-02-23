#include "../inc/result.h"

result_t show_error(result_t ec, QMainWindow *parent)
{
    switch (ec)
    {
        case OK_CODE:
            break;

        case MEMORY_ERROR_CODE:
            QMessageBox::critical(parent, ErrorMessage::MEMORY_ERROR_TITLE, ErrorMessage::MEMORY_ERROR_TEXT);
            break;

        case FILE_ERROR_CODE:
            QMessageBox::critical(parent, ErrorMessage::FILE_ERROR_TITLE, ErrorMessage::FILE_ERROR_TEXT);
            break;

        case FORMAT_ERROR_CODE:
            QMessageBox::critical(parent, ErrorMessage::FORMAT_ERROR_TITLE, ErrorMessage::FORMAT_ERROR_TEXT);
            break;

        case NULLPTR_ERROR_CODE:
            QMessageBox::critical(parent, ErrorMessage::NULLPTR_ERROR_TITLE, ErrorMessage::NULLPTR_ERROR_TEXT);
            break;

        case RANGE_ERROR_CODE:
            QMessageBox::critical(parent, ErrorMessage::RANGE_ERROR_TITLE, ErrorMessage::RANGE_ERROR_TEXT);
            break;

        case EMPTY_ERROR_CODE:
            QMessageBox::critical(parent, ErrorMessage::EMPTY_ERROR_TITLE, ErrorMessage::EMPTY_ERROR_TEXT);
            break;

        case UNKNOWN_ERROR_CODE:
            QMessageBox::critical(parent, ErrorMessage::UNKNOWN_ERROR_TITLE, ErrorMessage::UNKNOWN_ERROR_TEXT);
            break;
    }

    return OK_CODE;
}