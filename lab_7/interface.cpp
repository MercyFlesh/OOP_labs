#include "interface.hpp"

#include <QLabel>
#include <QFile>
#include <QStringList>
#include <QFileDialog>


Interface::Interface(QWidget *parent)
    : QWidget(parent),
      vbox_main_layout(new QVBoxLayout(this)), hbox_file_finder_layout(new QHBoxLayout),
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

    hbox_file_finder_layout->setSpacing(3);
    hbox_file_finder_layout->addStretch(0);
    hbox_file_finder_layout->addWidget(file_path_edit.get());
    hbox_file_finder_layout->addWidget(choice_file_btn.get());

    error_label = std::make_unique<QLabel>(this);
    error_label->setAlignment(Qt::AlignRight);
    error_label->setMinimumHeight(20);
    error_label->setMaximumHeight(20);

    vbox_file_finder_layout->setSpacing(10);
    vbox_file_finder_layout->addLayout(hbox_file_finder_layout.get());
    vbox_file_finder_layout->addWidget(error_label.get());

    graph_window->setStyleSheet("QWidget {"
                          "border-style: solid;"
                          "border-width: 1px;"
                          "border-color: black;"
                          "}");

    active_vertices_label = std::make_unique<QLabel>("Active vertex", this);
    active_vertices_box = std::make_unique<QComboBox>(this);
    active_vertices_btn = std::make_unique<QPushButton>("activate", this);

    event_label = std::make_unique<QLabel>("Event", this);
    event_box = std::make_unique<QComboBox>(this);
    event_btn = std::make_unique<QPushButton>("execute", this);

    active_vertices_box->setEnabled(false);
    event_box->setEnabled(false);
    active_vertices_btn->setEnabled(false);
    event_btn->setEnabled(false);

    grid_choice_vertice = std::make_unique<QGridLayout>();
    grid_choice_vertice->setVerticalSpacing(10);
    grid_choice_vertice->setHorizontalSpacing(5);
    grid_choice_vertice->addWidget(active_vertices_label.get(), 0, 0, 1, 1);
    grid_choice_vertice->addWidget(active_vertices_box.get(), 0, 1, 1, 1);
    grid_choice_vertice->addWidget(active_vertices_btn.get(), 0, 2, 1, 1);
    grid_choice_vertice->addWidget(event_label.get(), 1, 0, 1, 1);
    grid_choice_vertice->addWidget(event_box.get(), 1, 1, 1, 1);
    grid_choice_vertice->addWidget(event_btn.get(), 1, 2, 1, 1);

    vbox_main_layout->addLayout(vbox_file_finder_layout.get(), 1);
    vbox_main_layout->addWidget(graph_window.get(), 0);
    vbox_main_layout->addLayout(grid_choice_vertice.get(), 0);
    setLayout(vbox_main_layout.get());

    connect(choice_file_btn.get(), SIGNAL(pressed()), this, SLOT(choice_file()));
    connect(active_vertices_btn.get(), SIGNAL(pressed()), this, SLOT(set_active_vertex()));
    connect(event_btn.get(), SIGNAL(pressed()), this, SLOT(execute_event()));
}


void Interface::choice_file()
{
    file_name = QFileDialog::getOpenFileName(0, "Choice graph struct", "../lab_7", "*.csv");
    file_path_edit->setText(file_name);

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        active_vertices_box->setEnabled(false);
        event_box->setEnabled(false);
        active_vertices_btn->setEnabled(false);
        event_btn->setEnabled(false);
        return;
    }

    Matrix validate_matrix;
    int count_vertices = file.readAll().split('\n').size() - 1;
    file.seek(0);

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QVector<qint16> int_line;
        for (const auto& number : line.split(','))
        {
            if (number.toInt() > count_vertices)
            {
                error_label->setText("[-] File error: links in the matrix must not be more than the number of vertices");
                graph_ptr = nullptr;
                active_vertices_box->setEnabled(false);
                event_box->setEnabled(false);
                active_vertices_btn->setEnabled(false);
                event_btn->setEnabled(false);
                file.close();
                return;
            }

            int_line.append(number.toInt());
        }

        if (validate_matrix.size() > 0 &&
            int_line.size() != validate_matrix[0].size())
        {
            error_label->setText("[-] File error: incorrect number of events in rows");
            graph_ptr = nullptr;
            active_vertices_box->setEnabled(false);
            event_box->setEnabled(false);
            active_vertices_btn->setEnabled(false);
            event_btn->setEnabled(false);
            file.close();
            return;
        }

        validate_matrix.append(int_line);
    }

    file.close();

    active_vertices_box->clear();
    Matrix transition_matrix;
    for (std::size_t i = 0; i < validate_matrix.size(); ++i)
    {
        active_vertices_box->addItem("№ " + QString().number(i + 1), i);

        transition_matrix.append(QVector<qint16>(validate_matrix.size(), 0));
        for (auto& j : validate_matrix[i])
        {
            if (j != 0)
            {
                transition_matrix[i][j-1] = 1;
            }
        }
    }

    active_vertices_box->setEnabled(true);
    event_box->setEnabled(true);
    active_vertices_btn->setEnabled(true);
    event_btn->setEnabled(true);

    error_label->setText("");
    graph_ptr = std::make_shared<StateGraph>(std::move(transition_matrix), std::move(validate_matrix));
    graph_ptr->set_graph_window(graph_window);
    graph_window->set_graph(graph_ptr);

    update_event_box();
}


void Interface::update_event_box()
{
    event_box->clear();

    QVector<qint16> events_active_vertex = graph_ptr->get_events_vertex(graph_ptr->get_active_vertex());
    for (std::size_t i = 0; i < events_active_vertex.size(); ++i)
    {
        if (events_active_vertex[i] != 0)
        {
            event_box->addItem("№ " + QString().number(i + 1),
                               events_active_vertex[i] - 1);
        }
    }
}


void Interface::set_active_vertex()
{
    int choice_vertex_number = active_vertices_box->currentData().toInt();
    if (choice_vertex_number != graph_ptr->get_active_vertex())
    {
        graph_ptr->set_active_vertex(choice_vertex_number);
        update_event_box();
        graph_window->repaint();
    }
}


void Interface::execute_event()
{
    int choice_event_vertex_number = event_box->currentData().toInt();
    if (choice_event_vertex_number != graph_ptr->get_active_vertex())
    {
        graph_ptr->set_active_vertex(choice_event_vertex_number);
        update_event_box();
        active_vertices_box->setCurrentIndex(choice_event_vertex_number);
        graph_window->repaint();
    }
}
