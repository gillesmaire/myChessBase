#include "formuniversmypreferences.h"
#include "ui_formuniversmypreferences.h"
#include <QScreen>
#include <QSettings>

FormUniversMyPreferences::FormUniversMyPreferences(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormUniversMyPreferences)
{
    QSettings s;
    ui->setupUi(this);
    model = new QSqlQueryModel(this);
    ui->ECOview->setModel(model);
    ui->ECOview->setSortingEnabled(true);
    ui->ECOview->setModel(model); 
    ui->comboBoxChoice->setCurrentIndex(s.value("ECOTableDefautValue").toInt());
    s.setValue("ECOTableDefautValue",ui->comboBoxChoice->currentIndex());
    QString query="SELECT eco,ecoplus,opening,variation,moves from ECO" ;
    model->setQuery(query);
     QFont f;
    double dpi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
    double oneChar=dpi*f.pointSize()/72;
    ui->ECOview->setSortingEnabled(true);
    ui->ECOview->setColumnWidth(0,2*oneChar);
    ui->ECOview->setColumnWidth(1,2*oneChar);
    ui->ECOview->setColumnWidth(2,20*oneChar);
    ui->ECOview->setColumnWidth(3,10*oneChar);
    ui->ECOview->setColumnWidth(4,8*oneChar);
    ui->ECOview->setSortingEnabled(true) ;
    ui->ECOview->setAlternatingRowColors(true);
    model->setHeaderData(5, Qt::Horizontal, tr("Nb moves"));
    model->setHeaderData(6, Qt::Horizontal, tr("Preferred"));
    connect (ui->pushButtonGo,SIGNAL(clicked(bool)),this,SLOT(LaunchNewRequest(bool)));
    connect (ui->lineEditChoice,&QLineEdit::returnPressed,this,&FormUniversMyPreferences::LaunchRequest);
    connect(ui->ECOview, &MyTableView::currentChangedSignal,this,&FormUniversMyPreferences::ShowEcoPlus);
    QObject::connect(ui->ECOview->selectionModel(), &QItemSelectionModel::currentChanged,
                      ui->ECOview, [this](const QModelIndex &current, const QModelIndex &) {
                          if (current.isValid()) {
                              ui->ECOview->scrollTo(current); // Défile jusqu'à l'élément sélectionné
                         }
                     });


}

void FormUniversMyPreferences::LaunchRequest()
{
    LaunchNewRequest( true );

}
void FormUniversMyPreferences::LaunchNewRequest( bool )
{
  QString where;
     if (! ui->lineEditChoice->text().isEmpty()){
     qDebug()<<ui->comboBoxChoice->currentIndex();
        switch ( ui->comboBoxChoice->currentIndex() ){
        case 0 :    where=QString("WHERE ECO = '%1'").arg(ui->lineEditChoice->text()); 
                    break ;
        case 1 :    {QString eco=ui->lineEditChoice->text().first(3);
                    QString plus=ui->lineEditChoice->text().last(2);              
                    where=QString("WHERE ECO = '%1' AND ECOPLUS ='%2'").arg(eco).arg(plus); }
                    break;
        case 2 :    where=QString("WHERE opening LIKE '%%1%' OR variation LIKE '%%1%'").arg(ui->lineEditChoice->text());
                    break;
        case 3 :    where=QString("WHERE opening LIKE '%%1%'").arg(ui->lineEditChoice->text());
                    break;
        case 4 :    where=QString("WHERE variation LIKE '%%1%'").arg(ui->lineEditChoice->text());
                    break;
        case 5 :    where=QString("WHERE moves LIKE '%1%' ").arg(ui->lineEditChoice->text());
                    break;
        }
     }
     QString query="SELECT eco,ecoplus,opening,variation,moves from ECO "+where ;
     model->setQuery(query);
     QSettings s;
     s.setValue("ECOTableDefautValue",ui->comboBoxChoice->currentIndex());
   
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
