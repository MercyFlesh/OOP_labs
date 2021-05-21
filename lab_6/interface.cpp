#include "interface.hpp"

#include <QLabel>
#include <QFile>
#include <QStringList>
#include <QFileDialog>


Interface::Interface(QWidget *parent)
    : QWidget(parent),
      vbox_main_layout(new QVBoxLayout(this)), hbox_layout(new QHBoxLayout),
      vbox_file_finder_layout(new QVBoxLayout), graph_window(new GraphWindow)
{
    setWindowTitle("lab #6");
    setMinimumSize(320, 120);

    file_path_edit = std::make_unique<QLineEdit>(this);
    choice_file_btn = std::make_unique<QPushButton>(this);
    file_path_edit->setReadOnly(true);
    file_path_edit->setMinimumWidth(300);
    file_path_edit->setMaximumWidth(560);
    choice_file_btn->setIcon(QIcon(":images/open_document.png"));
    choice_file_btn->setMinimumWidth(50);

    hbox_layout->setSpacing(3);
    hbox_layout->addStretch(0);
    hbox_layout->addWidget(file_path_edit.get());
    hbox_layout->addWidget(choice_file_btn.get());

    error_label = std::make_unique<QLabel>(this);
    error_label->setAlignment(Qt::AlignRight);
    error_label->setMinimumHeight(20);
    error_label->setMaximumHeight(20);

    vbox_file_finder_layout->setSpacing(10);
    vbox_file_finder_layout->addLayout(hbox_layout.get());
    vbox_file_finder_layout->addWidget(error_label.get());

    graph_window->setStyleSheet("QWidget {"
                          "border-style: solid;"
                          "border-width: 1px;"
                          "border-color: black;"
                          "}");

    vbox_main_layout->addLayout(vbox_file_finder_layout.get(), 1);
    vbox_main_layout->addWidget(graph_window.get(), 0);
    setLayout(vbox_main_layout.get());

    connect(choice_file_btn.get(), SIGNAL(pressed()), this, SLOT(choice_file()));
}


void Interface::choice_file()
{
    file_name = QFileDialog::getOpenFileName(0, "Choice graph struct", "../lab_6", "*.csv");
    file_path_edit->setText(file_name);

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        return;
    }

    Matrix validate_matrix;
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QVector<qint16> int_line;

        for (const auto& number : line.split(','))
        {
            if (number.toInt() != 0 && number.toInt() != 1)
            {
                error_label->setText("[-] File error: links in the matrix must be denoted only through 0 and 1");
                graph_ptr = nullptr;
                file.close();
                return;
            }

            int_line.append(number.toInt());
        }

        if (validate_matrix.size() > 0 &&
            int_line.size() != validate_matrix[0].size())
        {
            error_label->setText("[-] File error: the number of vertices in the lines does not match");
            graph_ptr = nullptr;
            file.close();
            return;
        }

        validate_matrix.append(int_line);
    }

    if (validate_matrix.size() != validate_matrix[0].size())
    {
        error_label->setText("[-] File error: the number of columns and rows does not match");
        graph_ptr = nullptr;
        return;
    }
    else
    {
        error_label->setText("");
        graph_ptr = std::make_shared<Graph>(std::move(validate_matrix));
        graph_ptr->set_graph_window(graph_window);
        graph_window->set_graph(graph_ptr);
    }

    file.close();
    graph_window->repaint();
}
