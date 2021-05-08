#include "contract_gui.h"
#include "Test.h"
#include "contract_gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
int main(int argc, char *argv[])
{
    //{Test t;
    //t.testAll(); }
    QApplication a(argc, argv);
    Repository repo;
    Service serv{ repo };
    GUI gui(serv);
    gui.show();
    serv.ImportFile();
    serv.ExportFile();
    return a.exec();
}
