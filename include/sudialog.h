#ifndef SUDIALOG_H
#define SUDIALOG_H

#include <QFile>
#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QProcess>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>



namespace Ui { class SUDialog; }

class SUDialog : public QDialog {
    Q_OBJECT

public:
    static QString supassword;
    static QString work_dir;
    explicit SUDialog(QWidget *parent = 0);
    ~SUDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SUDialog *ui;
    static QImage              icon;
    static QGraphicsScene      *scene;
    static QGraphicsPixmapItem *item;
};

#endif // SUDIALOG_H
