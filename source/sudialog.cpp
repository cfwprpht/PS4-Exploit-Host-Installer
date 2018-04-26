#include "../include/sudialog.h"
#include "ui_sudialog.h"

QString             SUDialog::supassword;
QString             SUDialog::work_dir;
QImage              SUDialog::icon;
QGraphicsScene      *SUDialog::scene;
QGraphicsPixmapItem *SUDialog::item;

SUDialog::SUDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SUDialog) {
    ui->setupUi(this);
    this->setFixedSize(460, 148);
    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem();

    QImage img(":/icons/keys.png");
    icon = img.scaled(72, 72, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).convertToFormat(QImage::Format_ARGB32);
    item->setPixmap(QPixmap::fromImage(icon));
    scene->addItem(item);
    ui->pictureBox->setScene(scene);
    ui->pictureBox->show();
}

SUDialog::~SUDialog() {
    delete ui;
    delete item;
    delete scene;
}

void SUDialog::on_buttonBox_accepted() {
    // Test su password for correctness.
    QFile testsu("sutest.sh");
    if (testsu.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&testsu);
        out << "#!/bin/sh\n";
        out << "echo " + ui->textBox->text() + " | sudo -S echo 'blabla'";
        testsu.close();
    } else {
        QMessageBox::critical(this, "Error", "\nCouldn't create test script.");
        return;
    }

    if (QFile::exists("sutest.sh")) {
        if (QProcess::execute("chmod", QStringList() << "+x" << "sutest.sh") != 0) {
            QMessageBox::critical(this, "Error", "\nCouldn't set test script to executable.");
            QFile::remove("sutest.sh");
            return;
        }

        if (QProcess::execute("/bin/sh", QStringList() << "sutest.sh") != 0) {
            QMessageBox::critical(this, "Error", "\nSomething went wrong\n\nThe test script returned a error.");
            QFile::remove("sutest.sh");
            return;
        }

        QFile::remove("sutest.sh");
        supassword = ui->textBox->text();
    } else QMessageBox::critical(this, "Error", "\nCan't find test script but should exist.");
}
