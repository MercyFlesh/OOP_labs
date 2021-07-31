#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QScopedPointer>
#include <QSharedPointer>
#include <memory>

#include "graphwindow.hpp"
#include "state_graph.hpp"


class Interface : public QWidget
{
    Q_OBJECT

    std::shared_ptr<GraphWindow> graph_window;
    std::shared_ptr<StateGraph> graph_ptr;

    std::unique_ptr<QLineEdit> file_path_edit;
    std::unique_ptr<QPushButton> choice_file_btn;
    std::unique_ptr<QLabel> error_label;
    std::unique_ptr<QComboBox> active_vertices_box;
    std::unique_ptr<QComboBox> event_box;
    std::unique_ptr<QPushButton> active_vertices_btn;
    std::unique_ptr<QPushButton> event_btn;
    std::unique_ptr<QLabel> active_vertices_label;
    std::unique_ptr<QLabel> event_label;

    std::unique_ptr<QHBoxLayout> hbox_file_finder_layout;
    std::unique_ptr<QVBoxLayout> vbox_file_finder_layout;
    std::unique_ptr<QGridLayout> grid_choice_vertice;
    //std::unique_ptr<QHBoxLayout> hbox_graph_layout;
    std::unique_ptr<QVBoxLayout> vbox_main_layout;

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface() = default;

private:
    void update_event_box();
    void setCurrentIndex_active_vertices_box(int index);

private slots:
    void choice_file();
    void set_active_vertex();
    void execute_event();

private:
    QString file_name;
};
