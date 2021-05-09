#pragma once
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include <QColor>
#include <QPainter>
#include "Service.h"
class GUI :public QWidget {
	Service& serv;
	QListWidget* list = new QListWidget;
	QListWidget* list2 = new QListWidget;
	QListWidget* listContract = new QListWidget;

	QPushButton* refresh = new QPushButton("Refresh");
	QPushButton* sortAscendingByDenumire = new QPushButton("Sort ascending by Name");
	QPushButton* sortAscendingByNrOre = new QPushButton("Sort ascending by Number of Hours");
	QPushButton* sortAscendingByProfandType = new QPushButton("Sort ascending by Teacher and Type");
	QPushButton* sortDescendingByDenumire = new QPushButton("Sort descending by Name");
	QPushButton* sortDescendingByNrOre = new QPushButton("Sort descending by Number of Hours");
	QPushButton* sortDescendingByProfandType = new QPushButton("Sort descending by Teacher and Type");


	QLineEdit *denBox = new QLineEdit();
	QLineEdit *cadruDidacticBox = new QLineEdit();
	QLineEdit *tipBox = new QLineEdit();
	QLineEdit *nrOreBox = new QLineEdit();


	QPushButton* add = new QPushButton("Add a new discipline");
	QPushButton* upd = new QPushButton("Update a discipline");
	QPushButton* del = new QPushButton("Delete a discipline");
	QPushButton* find = new QPushButton("Find a discipline");

	QLineEdit* findBoxDen= new QLineEdit();
	QLineEdit* findBoxProf = new QLineEdit();

	QPushButton* filterByProf = new QPushButton("Filter by Teacher");
	QPushButton * filterByNrOre = new QPushButton("Filter by numbers of hours");

	QLineEdit* filterByProfBox = new QLineEdit();
	QLineEdit* filterByNrOreBox = new QLineEdit();

	QPushButton* undo = new QPushButton("Undo");
	QPushButton* redo = new QPushButton("Redo");

	QPushButton* addContract = new QPushButton("Add to the contract");
	QPushButton* randomContract = new QPushButton("Random contract generation");
	QPushButton* deleteContract = new QPushButton("Delete contract");
	QPushButton* exportContract = new QPushButton("Export contract");

	QLineEdit* nrContractBox = new QLineEdit();
	QLineEdit* nameFileContractBox = new QLineEdit();
	QLineEdit* DenContractBox = new QLineEdit();
	QLineEdit* ProfContractBox = new QLineEdit();
	

	QDialog* addWindow = new QDialog();
	QVBoxLayout* addWindowLayout = new QVBoxLayout();
	QFormLayout* addLayout = new QFormLayout;

	QLineEdit* denBoxAdd = new QLineEdit();
	QLineEdit* cadruDidacticBoxAdd = new QLineEdit();
	QLineEdit* tipBoxAdd = new QLineEdit();
	QLineEdit* nrOreBoxAdd = new QLineEdit();
	QPushButton* addDialogue = new QPushButton("Add");

	QDialog* updWindow = new QDialog();
	QVBoxLayout* updWindowLayout = new QVBoxLayout();
	QFormLayout* updLayout = new QFormLayout;

	QLineEdit* denBoxUpd = new QLineEdit();
	QLineEdit* cadruDidacticBoxUpd = new QLineEdit();
	QLineEdit* tipBoxUpd = new QLineEdit();
	QLineEdit* nrOreBoxUpd = new QLineEdit();
	QPushButton* updDialogue = new QPushButton("Update");


public:
	GUI(Service& serv) : serv{ serv } {
		Layout();
		Connections();
		Start();
	}
	void ShowList(std::vector<Disciplina> vector)
	{
		list->clear();
		for (auto& d : vector)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.getDenumire()) + "-" + QString::fromStdString(std::to_string(d.getNrOre()))+"-"+ QString::fromStdString(d.getCadruDidactic()) + "-" +QString::fromStdString(d.getTip()),list);
		}
	}
	void ShowListOfDiscipline(std::vector<Disciplina> vector)
	{
		list2->clear();
		for (auto& d : vector)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.getDenumire()) + "-" + QString::fromStdString(std::to_string(d.getNrOre())) + "-" + QString::fromStdString(d.getCadruDidactic()) + "-" + QString::fromStdString(d.getTip()), list2);
		}
	}
	void ShowListContract(std::vector<Disciplina> vector)
	{
		listContract->clear();
		for (auto& d : vector)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.getDenumire()) + "-" + QString::fromStdString(std::to_string(d.getNrOre())) + "-" + QString::fromStdString(d.getCadruDidactic()) + "-" + QString::fromStdString(d.getTip()), listContract);
		}
	}
	void Find(std::string denumire,std::string prof)
	{
		serv.ImportFile();
		char numar[10];
		int poz = serv.find_denumire_prof(denumire, prof);
		if (poz != -1)
		{
			denBox->setText(QString::fromUtf8(serv.getAll()[poz].getDenumire().c_str()));
			cadruDidacticBox->setText(QString::fromUtf8(serv.getAll()[poz].getCadruDidactic().c_str()));
			nrOreBox->setText(QString::fromUtf8(itoa(serv.getAll()[poz].getNrOre(),numar,10)));
			tipBox->setText(QString::fromUtf8(serv.getAll()[poz].getTip().c_str()));
		}
	}
	void Delete(std::string denumire, std::string prof)
	{
		serv.ImportFile();
		int poz = serv.find_denumire_prof(denumire, prof);
		serv.deleteDisciplina(serv.getAll()[poz]);
		serv.ExportFile();
	}
	void LoadDetails()
	{
		if (list->selectedItems().isEmpty())
		{
			denBox->setText("");
			nrOreBox->setText("");
			cadruDidacticBox->setText("");
			tipBox->setText("");
		}
		else
		{
			QListWidgetItem* item = list->selectedItems().at(0);
			char s[101];
			strcpy(s, item->text().toStdString().c_str());
			char* next_token = NULL;
			char* pcs = strtok_s(s, "-", &next_token);
			std::string denumire = pcs;
			pcs = strtok_s(NULL, "-", &next_token);
			const int nrOre = atoi(pcs);
			pcs = strtok_s(NULL, "-", &next_token);
			std::string cadruDidactic = pcs;
			pcs = strtok_s(NULL, "\n", &next_token);
			std::string tip = pcs;
			Find(denumire, cadruDidactic);
		}
	}
	void Layout() {
		QHBoxLayout* appLayout = new QHBoxLayout();
		this->setLayout(appLayout);

		QVBoxLayout* listLayout = new QVBoxLayout();
		listLayout->addWidget(list);
		listLayout->addWidget(refresh);

		QFormLayout* findLayout = new QFormLayout;
		QLabel* denLabelFind = new QLabel("Name");
		QLabel* cadruDidacticLabelFind = new QLabel("Teacher");
		findLayout->addRow(denLabelFind, findBoxDen);
		findLayout->addRow(cadruDidacticLabelFind, findBoxProf);
		findLayout->addWidget(find);

		listLayout->addLayout(findLayout);
		///////
		QVBoxLayout* listLayout2 = new QVBoxLayout();
		QVBoxLayout* listLayoutAscending = new QVBoxLayout();
		QVBoxLayout* listLayoutDescending = new QVBoxLayout();
		QHBoxLayout* listLayout3 = new QHBoxLayout();
		listLayout2->addWidget(list2);
		listLayoutAscending->addWidget(sortAscendingByDenumire);
		listLayoutDescending->addWidget(sortDescendingByDenumire);
		listLayoutAscending->addWidget(sortAscendingByProfandType);
		listLayoutDescending->addWidget(sortDescendingByProfandType);
		listLayoutAscending->addWidget(sortAscendingByNrOre);
		listLayoutDescending->addWidget(sortDescendingByNrOre);
		listLayout3->addLayout(listLayoutDescending);
		listLayout3->addLayout(listLayoutAscending);

		QHBoxLayout* filterLayoutNrOre = new QHBoxLayout();
		filterLayoutNrOre->addWidget(filterByNrOre);
		filterLayoutNrOre->addWidget(filterByNrOreBox);

		QHBoxLayout* filterLayoutProf = new QHBoxLayout();
		filterLayoutProf->addWidget(filterByProf);
		filterLayoutProf->addWidget(filterByProfBox);


		listLayout2->addLayout(filterLayoutProf);
		listLayout2->addLayout(filterLayoutNrOre);
		listLayout2->addLayout(listLayout3);
		appLayout->addLayout(listLayout2);
		///////
		appLayout->addLayout(listLayout);

		QVBoxLayout* actions = new QVBoxLayout();
		appLayout->addLayout(actions);

		QFormLayout* detailLayout = new QFormLayout;
		actions->addLayout(detailLayout);
		QLabel* denLabel = new QLabel("Name");
		QLabel* cadruDidacticLabel = new QLabel("Teacher");
		QLabel* tipLabel = new QLabel("Type");
		QLabel* nrOreLabel = new QLabel("Number of hours");
		detailLayout->addRow(denLabel, denBox);
		detailLayout->addRow(cadruDidacticLabel, cadruDidacticBox);
		detailLayout->addRow(tipLabel, tipBox);
		detailLayout->addRow(nrOreLabel, nrOreBox);

		actions->addWidget(add);
		actions->addWidget(upd);
		actions->addWidget(del);

		QHBoxLayout* UndoRedoLayout = new QHBoxLayout();
		UndoRedoLayout->addWidget(undo);
		UndoRedoLayout->addWidget(redo);
		actions->addLayout(UndoRedoLayout);

		addWindow->setLayout(addWindowLayout);
		addWindowLayout->addLayout(addLayout);
		updWindow->setLayout(updWindowLayout);
		updWindowLayout->addLayout(updLayout);


		QLabel* denLabelAdd = new QLabel("Name");
		QLabel* cadruDidacticLabelAdd = new QLabel("Teacher");
		QLabel* tipLabelAdd = new QLabel("Type");
		QLabel* nrOreLabelAdd = new QLabel("Number of hours");
		addLayout->addRow(denLabelAdd, denBoxAdd);
		addLayout->addRow(cadruDidacticLabelAdd, cadruDidacticBoxAdd);
		addLayout->addRow(tipLabelAdd,tipBoxAdd);
		addLayout->addRow(nrOreLabelAdd,nrOreBoxAdd);
		addWindowLayout->addWidget(addDialogue);

		QLabel* denLabelUpd = new QLabel("Name");
		QLabel* cadruDidacticLabelUpd = new QLabel("Teacher");
		QLabel* tipLabelUpd = new QLabel("Type");
		QLabel* nrOreLabelUpd = new QLabel("Number of hours");
		updLayout->addRow(denLabelUpd, denBoxUpd);
		updLayout->addRow(cadruDidacticLabelUpd, cadruDidacticBoxUpd);
		updLayout->addRow(tipLabelUpd, tipBoxUpd);
		updLayout->addRow(nrOreLabelUpd, nrOreBoxUpd);
		updWindowLayout->addWidget(updDialogue);

		QVBoxLayout* listLayout4 = new QVBoxLayout();
		listLayout4->addWidget(listContract);
		QFormLayout* contractLayout = new QFormLayout;
		QLabel* denLabelContract = new QLabel("Name");
		QLabel* cadruDidacticLabelContract = new QLabel("Teacher");
		contractLayout->addRow(denLabelContract, DenContractBox);
		contractLayout->addRow(cadruDidacticLabelContract, ProfContractBox);
		contractLayout->addWidget(addContract);

		QLabel* randomLabelContract = new QLabel("Number of disciplines");
		contractLayout->addRow(randomLabelContract, nrContractBox);
		contractLayout->addWidget(randomContract);

		QLabel* fileLabelContract = new QLabel("Name of file");
		contractLayout->addRow(fileLabelContract, nameFileContractBox);
		contractLayout->addWidget(exportContract);

		contractLayout->addWidget(deleteContract);

		listLayout4->addLayout(contractLayout);
		appLayout->addLayout(listLayout4);
	}

	void Connections()
	{
		QObject::connect(refresh, &QPushButton::clicked, [=]() {
			ShowList(serv.getAll());
		});

		QObject::connect(list, &QListWidget::itemSelectionChanged, [this]() {
			LoadDetails();
		});

		QObject::connect(sortAscendingByDenumire, &QPushButton::clicked, [=]()
		{
			ShowListOfDiscipline(serv.SortAscendingByDenumire());
		});

		QObject::connect(sortDescendingByDenumire, &QPushButton::clicked, [=]()
		{
			ShowListOfDiscipline(serv.SortDescendingByDenumire());
		});

		QObject::connect(sortAscendingByNrOre, &QPushButton::clicked, [=]()
		{
			ShowListOfDiscipline(serv.SortAscendingByNrOre());
		});

		QObject::connect(sortDescendingByNrOre, &QPushButton::clicked, [=]()
		{
			ShowListOfDiscipline(serv.SortDescendingByNrOre());
		});

		QObject::connect(sortAscendingByProfandType, &QPushButton::clicked, [=]()
		{
			ShowListOfDiscipline(serv.SortAscendingByProfAndType());
		});

		QObject::connect(sortDescendingByProfandType, &QPushButton::clicked, [=]()
		{
			ShowListOfDiscipline(serv.SortDescendingByProfAndType());
		});

		QObject::connect(filterByNrOre, &QPushButton::clicked, [=]()
		{
			if (filterByNrOreBox->text().toStdString() == "")
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You must enter the number of hours!"));
			}
			else
				ShowListOfDiscipline(serv.FilterByNrOre(atoi(filterByNrOreBox->text().toStdString().c_str())));
		});

		QObject::connect(filterByProf, &QPushButton::clicked, [=]()
		{
			if (filterByProfBox->text().toStdString() == "")
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You must enter the teacher!"));
			}
			else
				ShowListOfDiscipline(serv.FilterByProf(filterByProfBox->text().toStdString().c_str()));
		});

		QObject::connect(find, &QPushButton::clicked, [=]()
		{
			if (findBoxDen->text().toStdString() == "" || findBoxProf->text().toStdString() == "")
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You must enter the teacher and the name of the subject!"));
			}
			else
			{
				serv.ImportFile();
				char numar[10];
				int poz = serv.find_denumire_prof(findBoxDen->text().toStdString(), findBoxProf->text().toStdString());
				if (poz == -1)
				{
					QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("Doesn't exist!"));
				}
				else
				{
					denBox->setText(QString::fromUtf8(serv.getAll()[poz].getDenumire().c_str()));
					cadruDidacticBox->setText(QString::fromUtf8(serv.getAll()[poz].getCadruDidactic().c_str()));
					nrOreBox->setText(QString::fromUtf8(itoa(serv.getAll()[poz].getNrOre(), numar, 10)));
					tipBox->setText(QString::fromUtf8(serv.getAll()[poz].getTip().c_str()));
					ShowList(serv.getAll());
				}
			}
		});
		QObject::connect(add, &QPushButton::clicked, [=]() {
			serv.ImportFile();
			addWindow->setModal(true);
			addWindow->show();
		});

		QObject::connect(addDialogue, &QPushButton::clicked, [=]()
		{
			std::string denumire = denBoxAdd->text().toStdString();
			std::string cadruDidactic = cadruDidacticBoxAdd->text().toStdString();
			std::string tip = tipBoxAdd->text().toStdString();
			int nrOre = atoi(nrOreBoxAdd->text().toStdString().c_str());

			try
			{
				serv.addDisciplina(Disciplina(denumire, nrOre, cadruDidactic, tip));
			}
			catch (ValidateException& msg)
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msg.GetMessages()[0]));
			}
			catch (DisciplinaRepoException& msgg)
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msgg.GetMessages()));
			}
			serv.ExportFile();
			addWindow->close();
			ShowList(serv.getAll());
		});

		QObject::connect(upd, &QPushButton::clicked, [=]()
		{
			if (list->selectedItems().empty())
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You haven't selected anything!"));
			else
			{
				updWindow->setModal(true);
				updWindow->show();
			}
		});
		QObject::connect(updDialogue, &QPushButton::clicked, [=]()
		{
			std::string denumire = denBox->text().toStdString();
			std::string cadruDidactic = cadruDidacticBox->text().toStdString();
			std::string tip = tipBox->text().toStdString();
			int nrOre = atoi(nrOreBox->text().toStdString().c_str());

			std::string denumire_n = denBoxUpd->text().toStdString();
			std::string cadruDidactic_n = cadruDidacticBoxUpd->text().toStdString();
			std::string tip_n = tipBoxUpd->text().toStdString();
			int nrOre_n = atoi(nrOreBoxUpd->text().toStdString().c_str());
			try {
				serv.updateDisciplina(Disciplina(denumire, nrOre, cadruDidactic, tip), Disciplina(denumire_n, nrOre_n, cadruDidactic_n, tip_n));
			}
			catch (ValidateException& msg)
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msg.GetMessages()[0]));
			}
			catch (DisciplinaRepoException& msgg)
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msgg.GetMessages()));
			}
			serv.ExportFile();
			updWindow->close();
			ShowList(serv.getAll());
		});
		QObject::connect(del, &QPushButton::clicked, [=]()
		{
			if (list->selectedItems().empty())
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You haven't selected anything!"));
			else
			{
				try
				{
					Delete(denBox->text().toStdString(), cadruDidacticBox->text().toStdString());
				}
				catch (ValidateException& msg)
				{
					QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msg.GetMessages()[0]));
				}
				catch (DisciplinaRepoException& msgg)
				{
					QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msgg.GetMessages()));
				}
			}
			ShowList(serv.getAll());
		});
		QObject::connect(undo, &QPushButton::clicked, [=]() {
			try {
				serv.Undo();
			}
			catch (ValidateException& msg) {
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msg.GetMessages()[0]));
			}
			serv.ExportFile();
			ShowList(serv.getAll());
		});
		QObject::connect(redo, &QPushButton::clicked, [=]() {
			try {
				serv.Redo();
			}
			catch (ValidateException& msg) {
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msg.GetMessages()[0]));
			}
			serv.ExportFile();
			ShowList(serv.getAll());
		});
		QObject::connect(addContract, &QPushButton::clicked, [=]() {
			if (DenContractBox->text().toStdString() == "" || ProfContractBox->text().toStdString() == "")
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You must enter the teacher and the name of the subject!"));
			}
			else
			{
				serv.AddContract(DenContractBox->text().toStdString(), ProfContractBox->text().toStdString());
			}
			ShowListContract(serv.GetAllContract());
		});
		QObject::connect(randomContract, &QPushButton::clicked, [=]() {
			if (nrContractBox->text().toStdString() == "")
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You must enter the number of subjects!"));
			}
			else
			{
				const int nr = atoi(nrContractBox->text().toStdString().c_str());
				if (serv.sizeService() < nr)
				{
					QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("Insufficient number of disciplines"));
				}
				else
				{
					serv.Random(serv.getAll(), nr);
				}
			}
			ShowListContract(serv.GetAllContract());
		});
		QObject::connect(deleteContract, &QPushButton::clicked, [=]() {
			serv.DeleteContract();
			ShowListContract(serv.GetAllContract());
		});
		QObject::connect(exportContract, &QPushButton::clicked, [=]() {
			if (nameFileContractBox->text().toStdString() == "")
			{
				QMessageBox::warning(nullptr, "WARNING", QString::fromStdString("You must enter the name of file!"));
			}
			else
			{
				try {
					serv.ExportCSV(nameFileContractBox->text().toStdString());
				}
				catch (ValidateException& msg)
				{
					QMessageBox::warning(nullptr, "WARNING", QString::fromStdString(msg.GetMessages()[0]));
				}
			}
			ShowListContract(serv.GetAllContract());
		});
	}
	void Start()
	{
		ShowList(serv.getAll());
		denBox->setReadOnly(true);
		cadruDidacticBox->setReadOnly(true);
		tipBox->setReadOnly(true);
		nrOreBox->setReadOnly(true);
	}
};