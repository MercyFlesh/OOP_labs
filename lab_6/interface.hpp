#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QScopedPointer>
#include <QSharedPointer>
#include <memory>

#include "graphwindow.hpp"
#include "graph.hpp"


class Interface : public QWidget
{
    Q_OBJECT

    std::shared_ptr<GraphWindow> graph_window;
    std::shared_ptr<Graph> graph_ptr;

    std::unique_ptr<QLineEdit> file_path_edit;
    std::unique_ptr<QPushButton> choice_file_btn;
    std::unique_ptr<QLabel> error_label;

    std::unique_ptr<QHBoxLayout> hbox_layout;
    std::unique_ptr<QVBoxLayout> vbox_file_finder_layout;
    std::unique_ptr<QVBoxLayout> vbox_main_layout;

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface() = default;

private slots:
    void choice_file();

private:
    QString file_name;
};
