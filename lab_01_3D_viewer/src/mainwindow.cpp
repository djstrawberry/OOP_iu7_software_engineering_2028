#include "../inc/mainwindow.h"
#include "../build/ui/ui_mainwindow.h"

MainWindow::MainWindow(model_t& model, QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
, model(model)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    connect(ui->loadFileAction, &QAction::triggered, this, &MainWindow::ActionLoadFile_triggered);
    connect(ui->scalePushButton, &QPushButton::clicked, this, &MainWindow::ScalePushButton_clicked);
    connect(ui->rotatePushButton, &QPushButton::clicked, this, &MainWindow::RotatePushButton_clicked);
    connect(ui->transferPushButton, &QPushButton::clicked, this, &MainWindow::TransferPushButton_clicked);
}

MainWindow::~MainWindow()
{
    free_model(this->model);
    delete ui;
}

result_t MainWindow::draw()
{
    result_t ec = OK_CODE;

    request_t request;
    QGraphicsScene *scene;
    double width, height;

    auto scene_params = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, scene_params.width(), scene_params.height());
    scene = ui->graphicsView->scene();
    width = scene->width();
    height = scene->height();

    request.type = DRAW_MODEL;
    request.scene = { scene, width, height };

    ec = process_request(request, this->model);

    return ec;
}

result_t MainWindow::ActionLoadFile_triggered()
{
    result_t ec = OK_CODE;

    request_t request;
    request.type = LOAD_MODEL;

    QString filepath = QFileDialog::getOpenFileName(this, "Выбор файла с описанием модели", "./", "*.txt");
    QByteArray utf8_filepath = filepath.toUtf8();
    request.filename = utf8_filepath.constData();

    ec = process_request(request, this->model);

    if (ec == OK_CODE)
        draw();
    else
        show_error(ec, this);

    return ec;
}

result_t MainWindow::ScalePushButton_clicked()
{
    result_t ec = OK_CODE;

    request_t request;
    request.type = SCALE_MODEL;

    double kx, ky, kz;

    kx = ui->kxDoubleSpinBox->value();
    ky = ui->kyDoubleSpinBox->value();
    kz = ui->kzDoubleSpinBox->value();

    request.scale_params = { kx, ky, kz };

    ec = process_request(request, this->model);
    if (ec == OK_CODE)
        draw();
    else
        show_error(ec, this);

    return ec;
}

result_t MainWindow::RotatePushButton_clicked()
{
    result_t ec = OK_CODE;

    request_t request;
    request.type = ROTATE_MODEL;

    double angle_x, angle_y, angle_z;

    angle_x = ui->angleXDoubleSpinBox->value();
    angle_y = ui->angleYDoubleSpinBox->value();
    angle_z = ui->angleZDoubleSpinBox->value();

    request.rotate_params = { angle_x, angle_y, angle_z };

    ec = process_request(request, this->model);
    if (ec == OK_CODE)
        draw();
    else
        show_error(ec, this);

    return ec;
}


result_t MainWindow::TransferPushButton_clicked()
{
    result_t ec = OK_CODE;

    request_t request;
    request.type = TRANSFER_MODEL;

    double dx, dy, dz;

    dx = ui->dxSpinBox->value();
    dy = ui->dySpinBox->value();
    dz = ui->dzSpinBox->value();

    request.transfer_params = { dx, dy, dz };

    ec = process_request(request, this->model);
    if (ec == OK_CODE)
        draw();
    else
        show_error(ec, this);

    return ec;
}