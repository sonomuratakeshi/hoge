/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtNetwork>

#include "httpwindow.h"
#include "ui_authenticationdialog.h"

HttpWindow::HttpWindow(QWidget *parent)
#ifdef Q_WS_MAEMO_5
    : QWidget(parent)
#else
    : QDialog(parent)
#endif
{
    urlLineEdit = new QLineEdit(this);

    urlLabel = new QLabel(tr("&URL:"));
    urlLabel->setBuddy(urlLineEdit);
    statusLabel = new QLabel(this);
    statusLabel->setWordWrap(true);

    downloadButton = new QPushButton(tr("Download"));
    downloadButton->setDefault(true);
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(downloadButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

#ifndef Q_WS_MAEMO_5
    progressDialog = new QProgressDialog(this);
#endif

    connect(urlLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableDownloadButton()));

    connect(&qnam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
#ifndef QT_NO_OPENSSL
    connect(&qnam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif
#ifndef Q_WS_MAEMO_5
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
#endif
    connect(downloadButton, SIGNAL(clicked()), this, SLOT(downloadFile()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(urlLabel);
    topLayout->addWidget(urlLineEdit);

    QLabel *categoryNameLabel = new QLabel(tr("category"), this);
    QLabel *makerNameLabel = new QLabel(tr("maker"), this);
    QLabel *brandNameLabel = new QLabel(tr("brand"), this);
    QLabel *modelNumberNameLabel = new QLabel(tr("model number"), this);
    QLabel *imageUrlNameLabel = new QLabel(tr("image url"), this);
    QLabel *releaseDateNameLabel = new QLabel(tr("release date"), this);
    QLabel *officialUrlNameLabel = new QLabel(tr("official url"), this);
    QLabel *kakakucomUrlNameLabel = new QLabel(tr("kakaku.com url"), this);
    QLabel *supportNameLabel = new QLabel(tr("support"), this);
    QLabel *faqNameLabel = new QLabel(tr("faq"), this);
    QLabel *cataloqueNameLabel = new QLabel(tr("catalogue"), this);
    QLabel *manualNameLabel = new QLabel(tr("manual"), this);

    categoryLabel = new QLineEdit(this);
    makerLabel = new QLineEdit(this);
    brandLabel = new QLineEdit(this);
    modelNumberLabel = new QLineEdit(this);
    imageUrlLabel = new QLineEdit(this);
    releaseDateLabel = new QLineEdit(this);
    officialUrlLabel = new QLineEdit(this);
    kakakucomUrlLabel = new QLineEdit(this);
    supportLabel = new QLineEdit(this);
    faqLabel = new QLineEdit(this);
    catalogueLabel = new QLineEdit(this);
    manualLabel = new QLineEdit(this);

    catecoryCopyButton = new QPushButton(tr("copy"), this);
    makerCopyButton = new QPushButton(tr("copy"), this);
    brandCopyButton = new QPushButton(tr("copy"), this);
    modelNumberCopyButton = new QPushButton(tr("copy"), this);
    imageUrlCopyButton = new QPushButton(tr("copy"), this);
    releaseDateCopyButton = new QPushButton(tr("copy"), this);
    officialUrlCopyButton = new QPushButton(tr("copy"), this);
    kakakucomUrlCopyButton = new QPushButton(tr("copy"), this);
    supportCopyButton = new QPushButton(tr("copy"), this);
    faqCopyButton = new QPushButton(tr("copy"), this);
    cataloqueCopyButton = new QPushButton(tr("copy"), this);
    manualCopyButton = new QPushButton(tr("copy"), this);

    connect(catecoryCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(makerCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(brandCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(modelNumberCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(imageUrlCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(releaseDateCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(officialUrlCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(kakakucomUrlCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(supportCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(faqCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(cataloqueCopyButton, SIGNAL(clicked()), this, SLOT(copy()));
    connect(manualCopyButton, SIGNAL(clicked()), this, SLOT(copy()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(categoryNameLabel, 0, 0);
    gridLayout->addWidget(categoryLabel, 0, 1);
    gridLayout->addWidget(catecoryCopyButton, 0, 2);
    gridLayout->addWidget(makerNameLabel, 1, 0);
    gridLayout->addWidget(makerLabel, 1, 1);
    gridLayout->addWidget(makerCopyButton, 1, 2);
    gridLayout->addWidget(brandNameLabel, 2, 0);
    gridLayout->addWidget(brandLabel, 2, 1);
    gridLayout->addWidget(brandCopyButton, 2, 2);
    gridLayout->addWidget(modelNumberNameLabel, 3, 0);
    gridLayout->addWidget(modelNumberLabel, 3, 1);
    gridLayout->addWidget(modelNumberCopyButton, 3, 2);
    gridLayout->addWidget(imageUrlNameLabel, 4, 0);
    gridLayout->addWidget(imageUrlLabel, 4, 1);
    gridLayout->addWidget(imageUrlCopyButton, 4, 2);
    gridLayout->addWidget(releaseDateNameLabel, 5, 0);
    gridLayout->addWidget(releaseDateLabel, 5, 1);
    gridLayout->addWidget(releaseDateCopyButton, 5, 2);
    gridLayout->addWidget(kakakucomUrlNameLabel, 6, 0);
    gridLayout->addWidget(kakakucomUrlLabel, 6, 1);
    gridLayout->addWidget(kakakucomUrlCopyButton, 6, 2);
    gridLayout->addWidget(officialUrlNameLabel, 7, 0);
    gridLayout->addWidget(officialUrlLabel, 7, 1);
    gridLayout->addWidget(officialUrlCopyButton, 7, 2);
    gridLayout->addWidget(faqNameLabel, 8, 0);
    gridLayout->addWidget(faqLabel, 8, 1);
    gridLayout->addWidget(faqCopyButton, 8, 2);
    gridLayout->addWidget(cataloqueNameLabel, 9, 0);
    gridLayout->addWidget(catalogueLabel, 9, 1);
    gridLayout->addWidget(cataloqueCopyButton, 9, 2);
    gridLayout->addWidget(manualNameLabel, 10, 0);
    gridLayout->addWidget(manualLabel, 10, 1);
    gridLayout->addWidget(manualCopyButton, 10, 2);
    gridLayout->addWidget(supportNameLabel, 11, 0);
    gridLayout->addWidget(supportLabel, 11, 1);
    gridLayout->addWidget(supportCopyButton, 11, 2);
    gridLayout->setColumnStretch(0, 0);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setColumnStretch(2, 0);
    gridLayout->setColumnMinimumWidth(1, 100);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("HTTP"));
    urlLineEdit->setFocus();
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

void HttpWindow::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    //connect(reply, SIGNAL(readyRead()),
    //        this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void HttpWindow::downloadFile()
{
    url = urlLineEdit->text();

#ifndef Q_WS_MAEMO_5
    progressDialog->setWindowTitle(tr("HTTP"));
#endif
    downloadButton->setEnabled(false);

    // schedule the request
    httpRequestAborted = false;
    startRequest(url);
}

void HttpWindow::cancelDownload()
{
    statusLabel->setText(tr("Download canceled."));
    httpRequestAborted = true;
    reply->abort();
    downloadButton->setEnabled(true);
}

void HttpWindow::httpFinished()
{
    clear();
    if (httpRequestAborted) {
        reply->deleteLater();
#ifndef Q_WS_MAEMO_5
        progressDialog->hide();
#endif
        return;
    }

#ifndef Q_WS_MAEMO_5
    progressDialog->hide();
#endif


    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(reply->errorString()));
        downloadButton->setEnabled(true);
    } else if (!redirectionTarget.isNull()) {        
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        if (QMessageBox::question(this, tr("HTTP"),
                                  tr("Redirect to %1 ?").arg(newUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            url = newUrl;
            reply->deleteLater();
            startRequest(url);
            return;
        }
        parse();
    } else {
        QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
        downloadButton->setEnabled(true);
        parse();
    }

    reply->deleteLater();
    reply = 0;
}

void HttpWindow::parse()
{
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QStringList siteData = codec->toUnicode(reply->readAll()).split("\r\n");

    for (int i=0; i < siteData.size(); i++) {
        if (siteData.at(i).indexOf("prdname") >= 0) {
            modelNumberLabel->setText(splitStrL(siteData.at(i),
                                               QString("'"),
                                               QString("',")));
        }
        else if (siteData.at(i).indexOf("mkrname") >= 0) {
            makerLabel->setText(splitStrL(siteData.at(i),
                                         QString("'"),
                                         QString("',")));
        }
        else if (siteData.at(i).indexOf("ctgname") >= 0) {
            categoryLabel->setText(splitStrL(siteData.at(i),
                                            QString("'"),
                                            QString("',")));
        }
        else if (siteData.at(i).indexOf("seriesLabel") >= 0) {
            brandLabel->setText(splitStrR(siteData.at(i),
                                          QString("\">"),
                                          QString("</a>")));
        }
        else if (siteData.at(i).indexOf("itemprop=\"image\"") >= 0) {
            QString tmp = splitStrL(siteData.at(i),
                                   QString("src=\""),
                                   QString("\""));
            imageUrlLabel->setText(tmp.replace("/l/", "/fullscale/"));
        }
        else if ((siteData.at(i).indexOf(QString::fromLocal8Bit("”­”„“ú")) >= 0) ||
                 (siteData.at(i).indexOf(QString::fromLocal8Bit("“o˜^“ú")) >= 0)) {
            QString year, month, day;
            year = splitStrL(siteData.at(i),
                             QString::fromLocal8Bit("”­”„“úF"),
                             QString::fromLocal8Bit("”N"));
            if (year.isEmpty()) {
                year = splitStrL(siteData.at(i),
                                 QString::fromLocal8Bit("“o˜^“úF"),
                                 QString::fromLocal8Bit("”N"));
            }
            month = splitStrL(siteData.at(i),
                              QString::fromLocal8Bit("”N"),
                              QString::fromLocal8Bit("ŒŽ"));
            day = splitStrL(siteData.at(i),
                            QString::fromLocal8Bit("ŒŽ"),
                            QString::fromLocal8Bit("“ú"));
            if (day.isEmpty()) {
                if (siteData.at(i).indexOf(QString::fromLocal8Bit("ã{")) >= 0) {
                    releaseDateLabel->setText(QString("%1/%2/01")
                                              .arg(year.toInt())
                                              .arg(month.toInt(), 2, 10, QChar('0')));
                }
                else if (siteData.at(i).indexOf(QString::fromLocal8Bit("’†{")) >= 0) {
                    releaseDateLabel->setText(QString("%1/%2/15")
                                              .arg(year.toInt())
                                              .arg(month.toInt(), 2, 10, QChar('0')));
                }
                else if (siteData.at(i).indexOf(QString::fromLocal8Bit("‰º{")) >= 0) {
                    releaseDateLabel->setText(QString("%1/%2/25")
                                              .arg(year.toInt())
                                              .arg(month.toInt(), 2, 10, QChar('0')));
                }
                else {
                    releaseDateLabel->setText(QString("%1/%2/15")
                                              .arg(year.toInt())
                                              .arg(month.toInt(), 2, 10, QChar('0')));
                }
            }
            else {
                releaseDateLabel->setText(QString("%1/%2/%3")
                                          .arg(year.toInt())
                                          .arg(month.toInt(), 2, 10, QChar('0'))
                                          .arg(day.toInt(), 2, 10, QChar('0')));
            }
        }
        else if (siteData.at(i).indexOf("specInfo") >= 0) {
            officialUrlLabel->setText(splitStrR(siteData.at(i+1),
                                      QString("a href=\""),
                                      QString("\" onclick=")));
        }
    }

    kakakucomUrlLabel->setText(urlLineEdit->text());
    QDir *makerDataDir = new QDir(QString("./data/%1").arg(makerLabel->text()));
    if (makerDataDir->exists()) {
        QFileInfoList entries = makerDataDir->entryInfoList();
        for (int j=0; j < entries.size(); j++) {
            if (entries.at(j).isFile()) {
                QFile *file = new QFile(entries.at(j).absoluteFilePath());
                if (file->open(QIODevice::ReadOnly) == false) {
                    continue;
                }
                QString readStr = QString(file->readAll());
                if (entries.at(j).fileName() == QString::fromLocal8Bit("ƒTƒ|[ƒg‚Ü‚Æ‚ßƒy[ƒW")) {
                    supportLabel->setText(readStr);
                }
                else if (entries.at(j).fileName() == QString("FAQ")) {
                    faqLabel->setText(readStr);
                }
                else if (entries.at(j).fileName() == QString::fromLocal8Bit("ƒJƒ^ƒƒO")) {
                    catalogueLabel->setText(readStr);
                }
                else if (entries.at(j).fileName() == QString::fromLocal8Bit("Žæˆµà–¾‘")) {
                    manualLabel->setText(readStr);
                }
                file->close();
                delete file;
            }
        }
    }
    delete makerDataDir;
}

void HttpWindow::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
}

void HttpWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        return;

#ifndef Q_WS_MAEMO_5
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(bytesRead);
#else
    Q_UNUSED(bytesRead);
    Q_UNUSED(totalBytes);
#endif
}

void HttpWindow::enableDownloadButton()
{
    downloadButton->setEnabled(!urlLineEdit->text().isEmpty());
}

void HttpWindow::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)
{
    QDialog dlg;
    Ui::Dialog ui;
    ui.setupUi(&dlg);
    dlg.adjustSize();
    ui.siteDescription->setText(tr("%1 at %2").arg(authenticator->realm()).arg(url.host()));

    // Did the URL have information? Fill the UI
    // This is only relevant if the URL-supplied credentials were wrong
    ui.userEdit->setText(url.userName());
    ui.passwordEdit->setText(url.password());

    if (dlg.exec() == QDialog::Accepted) {
        authenticator->setUser(ui.userEdit->text());
        authenticator->setPassword(ui.passwordEdit->text());
    }
}

#ifndef QT_NO_OPENSSL
void HttpWindow::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += ", ";
        errorString += error.errorString();
    }
    
    if (QMessageBox::warning(this, tr("HTTP"),
                             tr("One or more SSL errors has occurred: %1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        reply->ignoreSslErrors();
    }
}
#endif

void HttpWindow::copy()
{
    QClipboard *clipboard = QApplication::clipboard();
    if (sender() == catecoryCopyButton) {
        clipboard->setText(categoryLabel->text());
    }
    else if (sender() == makerCopyButton) {
        clipboard->setText(makerLabel->text());
    }
    else if (sender() == brandCopyButton) {
        clipboard->setText(brandLabel->text());
    }
    else if (sender() == modelNumberCopyButton) {
        clipboard->setText(modelNumberLabel->text());
    }
    else if (sender() == imageUrlCopyButton) {
        clipboard->setText(imageUrlLabel->text());
    }
    else if (sender() == releaseDateCopyButton) {
        clipboard->setText(releaseDateLabel->text());
    }
    else if (sender() == officialUrlCopyButton) {
        clipboard->setText(officialUrlLabel->text());
    }
    else if (sender() == kakakucomUrlCopyButton) {
        clipboard->setText(kakakucomUrlLabel->text());
    }
    else if (sender() == supportCopyButton) {
        clipboard->setText(supportLabel->text());
    }
    else if (sender() == faqCopyButton) {
        clipboard->setText(faqLabel->text());
    }
    else if (sender() == cataloqueCopyButton) {
        clipboard->setText(catalogueLabel->text());
    }
    else if (sender() == manualCopyButton) {
        clipboard->setText(manualLabel->text());
    }
}

void HttpWindow::clear()
{
    categoryLabel->clear();
    makerLabel->clear();
    brandLabel->clear();
    modelNumberLabel->clear();
    imageUrlLabel->clear();
    releaseDateLabel->clear();
    officialUrlLabel->clear();
    kakakucomUrlLabel->clear();
    supportLabel->clear();
    faqLabel->clear();
    catalogueLabel->clear();
    manualLabel->clear();
}

QString HttpWindow::splitStrL(const QString &text, QString &front, QString &behind)
{
  int start,end;

  start = text.indexOf(front)+front.size();
  end = text.indexOf(behind, start);

  if(start < front.size() || end <= 0){
    return QString();
  }

  return (text.mid(start, end - start));
}

QString HttpWindow::splitStrR(const QString &text, QString &front, QString &behind)
{
  int start,end;

  start = text.lastIndexOf(front)+front.size();
  end = text.lastIndexOf(behind);

  if(start < front.size() || end <= 0){
    return QString();
  }

  return (text.mid(start, end - start));
}

