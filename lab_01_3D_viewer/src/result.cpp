#include "result.h"

static result_t showColoredCriticalMessage(QMainWindow *parent, const QString &title, const QString &text)
{
    result_t ec = OK_CODE;

    QMessageBox msgBox(parent);
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStyleSheet("QLabel{color: black;} QPushButton{color: black;}");
    msgBox.exec();

    return ec;
}

result_t show_error(result_t ec, QMainWindow *parent)
{
    switch (ec)
    {
        case OK_CODE:
            break;

        case MEMORY_ERROR_CODE:
            showColoredCriticalMessage(
                parent, 
                ErrorMessage::MEMORY_ERROR_TITLE, 
                ErrorMessage::MEMORY_ERROR_TEXT
            );            
            break;

        case FILE_ERROR_CODE:
            showColoredCriticalMessage(
                parent, 
                ErrorMessage::FILE_ERROR_TITLE, 
                ErrorMessage::FILE_ERROR_TEXT
            ); 
            break;

        case FORMAT_ERROR_CODE:
            showColoredCriticalMessage(
                parent, 
                ErrorMessage::FORMAT_ERROR_TITLE, 
                ErrorMessage::FORMAT_ERROR_TEXT
            ); 
            break;

        case NULLPTR_ERROR_CODE:
            showColoredCriticalMessage(
                parent, 
                ErrorMessage::NULLPTR_ERROR_TITLE, 
                ErrorMessage::NULLPTR_ERROR_TEXT
            ); 
            break;

        case RANGE_ERROR_CODE:
            showColoredCriticalMessage(
                parent, 
                ErrorMessage::RANGE_ERROR_TITLE, 
                ErrorMessage::RANGE_ERROR_TEXT
            ); 
            break;

        case EMPTY_ERROR_CODE:
            showColoredCriticalMessage(
                parent, 
                ErrorMessage::EMPTY_ERROR_TITLE, 
                ErrorMessage::EMPTY_ERROR_TEXT
            ); 
            break;

        case UNKNOWN_ERROR_CODE:
            showColoredCriticalMessage(
                parent, 
                ErrorMessage::UNKNOWN_ERROR_TITLE, 
                ErrorMessage::UNKNOWN_ERROR_TEXT
            ); 
            break;
    }

    return OK_CODE;
}