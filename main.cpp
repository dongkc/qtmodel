#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "SqlQueryModel.h"

static bool create_connection()
{
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("database.db");

  if (!db.open()) {
      QMessageBox::critical(0, qApp->tr("Cannot open database"),
          qApp->tr("Unable to establish a database connection.\n"
                   "This example needs SQLite support. Please read "
                   "the Qt SQL driver documentation for information how "
                   "to build it.\n\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      return false;
  }

#if 0
  QSqlQuery query;
  query.exec("create table person (id int primary key, "
             "firstname varchar(20), lastname varchar(20))");
  query.exec("insert into person values(1, 'dong', 'kechang')");
  query.exec("insert into person values(2, 'wan', 'li')");
  query.exec("insert into person values(3, 'wan', 'li')");
#endif

  return true;
}

void initializeModel(QSqlTableModel *model)
{
    model->setTable("person");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    qDebug() << "-----------------";
    QTableView *v = new QTableView;
    v->setModel(model);
    v->show();

//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QQmlApplicationEngine engine;

  if (!create_connection())
      return 1;
  SqlQueryModel *model1 = new SqlQueryModel(0);
  model1->setQuery("SELECT * FROM person");

//  QSqlTableModel model;
//  initializeModel(&model);
  engine.rootContext()->setContextProperty("mymodel", model1);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}

