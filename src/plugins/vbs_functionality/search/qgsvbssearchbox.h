/***************************************************************************
 *  qgsvbssearchbox.h                                                      *
 *  -------------------                                                    *
 *  begin                : Jul 09, 2015                                    *
 *  copyright            : (C) 2015 by Sandro Mani / Sourcepole AG         *
 *  email                : smani@sourcepole.ch                             *
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSVBSSEARCHBOX_H
#define QGSVBSSEARCHBOX_H

#include "qgisinterface.h"
#include "qgsvbssearchprovider.h"
#include <QLineEdit>
#include <QList>
#include <QTimer>
#include <QToolButton>
#include <QTreeWidget>


class QgsCoordinateReferenceSystem;
class QgsPoint;
class QgsRectangle;

class QgsVBSSearchBox : public QLineEdit
{
    Q_OBJECT

  public:
    QgsVBSSearchBox( QgisInterface* iface, QWidget* parent = 0 );
    ~QgsVBSSearchBox();

    void addSearchProvider( QgsVBSSearchProvider* provider );
    void removeSearchProvider( QgsVBSSearchProvider* provider );

  private:
    enum EntryType { EntryTypeCategory, EntryTypeResult };
    static const int sEntryTypeRole;
    static const int sCatNameRole;
    static const int sCatCountRole;
    static const int sResultDataRole;

    QgisInterface* mIface;
    QList<QgsVBSSearchProvider*> mSearchProviders;
    QTimer mTimer;
    QToolButton m_searchButton;
    QToolButton m_clearButton;
    QTreeWidget mPopup;
    int mNumRunningProviders;

    void resizeEvent( QResizeEvent* ) override;
    bool eventFilter( QObject* obj, QEvent* ev ) override;

  private slots:
    void startSearch();
    void clearSearch();
    void searchResultFound( QgsVBSSearchProvider::SearchResult result );
    void searchProviderFinished();
    void resultSelected();
    void resultActivated();
    void setSearchIcon();
};

#endif // QGSVBSSEARCHBOX_H