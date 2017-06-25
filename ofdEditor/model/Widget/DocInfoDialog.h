#ifndef DOCINFODIALOG_H
#define DOCINFODIALOG_H

#include <QDialog>
#include "model_global.h"
class CT_DocInfo;       // �ĵ�Ԫ��Ϣ

namespace Ui {
class DocInfoDialog;
}

class MODELSHARED_EXPORT DocInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocInfoDialog(QWidget *parent = 0);

    DocInfoDialog(CT_DocInfo* docInfo,QWidget *parent);

    ~DocInfoDialog();

private:
    Ui::DocInfoDialog *ui;
    CT_DocInfo* docInfo;        // �ĵ�Ԫ��Ϣ
    void init();                // ��ʼ��
    void initUi();              // ��ʼ��ui

public slots:
    void editTitle(const QString & text);       // �޸ı���
    void editAuthor(const QString & text);      // �޸�����
    void editSubject(const QString & text);     // �޸�����
    void editAbstract(const QString & text);    // �޸�ժҪ
    void editFileType(const QString & text);    // �ĵ�����
    void editFileCover(const QString & text);   // �ĵ�����
    void resetDocId();                          // ����UUID

};

#endif // DOCINFODIALOG_H
