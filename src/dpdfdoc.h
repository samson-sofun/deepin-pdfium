#ifndef DPDFDOC_H
#define DPDFDOC_H

#include "dpdfglobal.h"

#include <QObject>
#include <QMap>
#include <QVector>
#include <QPointF>

class DPdfPage;
class DPdfDocHandler;
class DEEPIN_PDFIUM_EXPORT DPdfDoc : public QObject
{
    Q_OBJECT
public:
    enum Status {
        NOT_LOADED = -1,
        SUCCESS = 0,
        FILE_ERROR,
        FORMAT_ERROR,
        PASSWORD_ERROR,
        HANDLER_ERROR,
        FILE_NOT_FOUND_ERROR
    };

    struct Section;
    typedef QVector< Section > Outline;
    typedef QMap<QString, QVariant> Properies;

    struct Section {
        int nIndex;
        QPointF offsetPointF;
        QString title;
        Outline children;
    };

    explicit DPdfDoc();
    DPdfDoc(QString filename, QString password = QString());

    virtual ~DPdfDoc();

    /**
     * @brief 文档是否有效
     * @return
     */
    bool isValid() const;

    /**
     * @brief 是否是加密文档
     * @return
     */
    bool isEncrypted() const;

    /**
     * @brief 文档路径
     * @return
     */
    QString filename() const;

    /**
     * @brief 文档页数
     * @return
     */
    int pageCount() const;

    /**
     * @brief 文档状态
     * @return
     */
    Status status() const;

    /**
     * @brief 返回指定PAGE
     * @param i
     * @return
     */
    DPdfPage *page(int i);

    /**
     * @brief 目录
     * @return
     */
    Outline outline();

    /**
     * @brief 文档属性信息
     * Keys:
     * Version
     * Encrypted
     * Linearized
     * KeyWords
     * Title
     * Creator
     * Producer
     * @return
     */
    Properies proeries();

public Q_SLOTS:
    /**
     * @brief 加载文档
     * @param filename
     * @param password
     * @return
     */
    Status loadFile(QString filename, QString password = QString());

private:
    Q_DISABLE_COPY(DPdfDoc)
    DPdfDocHandler *m_docHandler = nullptr;
    QVector<DPdfPage *> m_pages;
    QString m_filename;
    int m_pageCount;
    Status m_status;
    DPdfDoc::Status parseError(int err);
};

#endif // DPDFDOC_H