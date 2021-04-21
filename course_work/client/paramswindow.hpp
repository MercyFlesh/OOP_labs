#pragma once

#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QJsonObject>

#include <memory>


class ParamsWindow : public QWidget
{
    Q_OBJECT

    std::unique_ptr<QLabel> add_manager_label;
    std::unique_ptr<QLineEdit> add_manager_name_edit, add_manager_rating_edit;
    std::unique_ptr<QPushButton> add_manager_btn;

    std::unique_ptr<QLabel> update_manager_label;
    std::unique_ptr<QLineEdit> id_update_manager_edit;
    std::unique_ptr<QLineEdit> update_rating;
    std::unique_ptr<QPushButton> update_manager_btn;

    std::unique_ptr<QVBoxLayout> vbox_layout;
    std::unique_ptr<QFormLayout> add_form_layout, update_form_layout;

public:
    explicit ParamsWindow(QWidget* parent = nullptr);
    ~ParamsWindow() = default;


};
