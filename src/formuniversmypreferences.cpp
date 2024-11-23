#include "formuniversmypreferences.h"
#include "ui_formuniversmypreferences.h"

FormUniversMyPreferences::FormUniversMyPreferences(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormUniversMyPreferences)
{
    ui->setupUi(this);
     model = new QSqlTableModel(this);
     model->setTable("ECO");
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->removeColumns(4,2);
     model->select();
     model->insertColumns(6,1);
     
     model->setHeaderData(5, Qt::Horizontal, tr("Nb moves"));
     model->setHeaderData(6, Qt::Horizontal, tr("Prefered"));
     //model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,20);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,170);
    ui->tableView->setColumnWidth(3,8);
    ui->tableView->setColumnWidth(5,10);
    ui->tableView->setSortingEnabled(true) ;
    ui->tableView->setAlternatingRowColors(true);
    //connect(ui->tableView, &QTableView::clicked,this,&FormUniversMyPreferences::ShowEcoPlus);
    connect(ui->tableView, &MyTableView::currentChangedSignal,this,&FormUniversMyPreferences::ShowEcoPlus);
    QObject::connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged,
                     ui->tableView, [this](const QModelIndex &current, const QModelIndex &) {
                         if (current.isValid()) {
                             ui->tableView->scrollTo(current); // Défile jusqu'à l'élément sélectionné
                         }
                     });
}


FormUniversMyPreferences::~FormUniversMyPreferences()
{
    delete ui;
}

void FormUniversMyPreferences::ShowEcoPlus(QModelIndex index)
{
     QString eco =index.sibling(index.row(),0).data().toString();
     QString opening=index.sibling(index.row(),1).data().toString();
     QString variation=index.sibling(index.row(),2).data().toString();
     QString ecoplus=index.sibling(index.row(),3).data().toString();
     QString moves=index.sibling(index.row(),4).data().toString();
     emit Informations(eco,opening,variation,ecoplus,moves);
}
