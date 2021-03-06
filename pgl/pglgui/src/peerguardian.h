
/***************************************************************************
 *   Copyright (C) 2007-2008 by Dimitris Palyvos-Giannas   *
 *   jimaras@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef PEERGUARDIAN_H
#define PEERGUARDIAN_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QEvent>
#include <QVariant>
#include <QByteArray>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QPushButton>
#include <QIcon>
#include <QMenu>
#include <QCursor>
#include <QMessageBox>
#include <QFile>
#include <QFont>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QDate>
#include <QTime>
#include <QFileDialog>
#include <QStringList>
#include <QList>
#include <QTreeWidgetItem>

#include "ui_main_window.h"

#include "file_transactions.h"
#include "pgl_settings.h"
#include "pgl_lists.h"
#include "peerguardian_info.h"
#include "pglcmd.h"
#include "super_user.h"

#include "settings.h"
#include "add_exception_dialog.h"
#include "pgl_whitelist.h"


#define VERSION_NUMBER VERSION
#define DEFAULT_WINDOW_TITLE "PeerGuardian Linux"

//Time related defines
#define MEDIUM_TIMER_INTERVAL 2000
#define SLOW_TIMER_INTERVAL 5000
#define INFOMSG_DELAY 5000


//Icon related defines
#define LOG_LIST_INFO_ICON ":/images/info.png"
#define LOG_LIST_OUTGOING_ICON ":/images/outgoing.png"
#define LOG_LIST_INCOMING_ICON ":/images/incoming.png"
#define LOG_LIST_FORWARD_ICON ":/images/forward.png"
#define LOG_LIST_ERROR_ICON ":/images/error.png"
#define TRAY_ICON ":/images/tray.png"
#define TRAY_DISABLED_ICON ":/images/tray_disabled.png"
#define ENABLED_ICON ":/images/ok.png"
#define DISABLED_ICON ":/images/cancel.png"
#define RUNNING_ICON ":/images/ok.png"
#define NOT_RUNNING_ICON ":/images/cancel.png"
#define WARNING_ICON ":/images/warning.png"
#define ICON_WIDTH 24
#define ICON_HEIGHT 24

#define UNCHECKED 0
#define CHECKED 2

#define MAX_LOG_SIZE 512


class GuiOptions;
class QTreeWidgetItem;
class QApplication;

/**
*
* @short Class representing the main window of the program. Handles everything that has to do with the GUI.
*
*/

class Peerguardian : public QMainWindow, private Ui::MainWindow {

	Q_OBJECT

    QSettings *m_ProgramSettings;
    QString m_Loaded_RootFile;
    SuperUser *m_Root;
    PeerguardianInfo *m_Info;
    PeerguardianList *m_List;
    PglWhitelist *m_Whitelist;
    PglCmd *m_Control;
    QSystemTrayIcon *m_Tray;
    QIcon mTrayIconEnabled;
    QIcon mTrayIconDisabled;
    QMenu * m_TrayMenu;
    QMenu * m_LogMenu;
    //Timers
    QTimer *m_MediumTimer;
    QTimer *m_SlowTimer;
    bool quitApp;
    bool m_WhitelistItemPressed;
    bool m_BlocklistItemPressed;
    bool m_treeItemPressed;
    GuiOptions *guiOptions;
    QStringList m_FilesToMove;
    bool m_StopLogging;
    QHash<QString, QString> m_ConnectType;
    QHash<QString, QIcon> m_ConnectIconType;
    int m_MaxLogSize;
    //whitelist QActions
    QAction *a_whitelistIpPerm;
    QAction *a_whitelistIpTemp;
    QAction *a_whitelistPortPerm;
    QAction *a_whitelistPortTemp;
    QString m_selectedAction; //store the QAction hovered in the log view when whitelisting an IP/Port
    QTreeWidgetItem *m_selectedItem; //store the selected item from the log view when whitelisting an IP/Port
    bool mLastRunningState;
    CommandList mFailedCommands;
    volatile bool mAutomaticScroll;
    volatile bool mIgnoreScroll;
    QAction *aWhoisIp;

	public:
		/**
		 * Constructor.
		 * This function calls several other functions to do the following:
		 * a)Setup the GUI.
		 * b)Create objects of the main classes.
		 * c)Create the connections between the objects.
		 * @param parent The QWidget parent of the object.
		 */
		Peerguardian( QWidget *parent = 0);
		/**
		 * Destructor. Takes the appropriate actions when Peerguardian is destroyed.
		 * Deletes object pointers and saves settings.
		 */
		virtual ~Peerguardian();

        void g_MakeConnections();
        void initializeSettings();
		void g_SetRoot();
		void g_SetInfoPath();
        void g_SetListPath();
        void g_SetControlPath();
        void g_MakeTray();
        void g_MakeMenus();
        void g_ShowAddDialog(int);
        void startTimers();
        void updateGUI();
        QList<QTreeWidgetItem*> getTreeItems(QTreeWidget *tree, int checkState=-1);
        QRadioButton * getAutoListUpdateDailyRadio() {return m_AutoListUpdateDailyRadio;}
        QRadioButton * getAutoListUpdateWeeklyRadio() {return m_AutoListUpdateWeeklyRadio;}
        QRadioButton * getAutoListUpdateMonthlyRadio() {return m_AutoListUpdateMonthlyRadio;}
        QCheckBox * getAutoListUpdateBox() { return m_AutoListUpdateBox; }
        QCheckBox * getStartAtBootBox() { return m_StartAtBootBox; }
        QTreeWidget * getBlocklistTreeWidget() { return m_BlocklistTreeWidget; }
        QTreeWidget * getWhitelistTreeWidget() { return m_WhitelistTreeWidget; }
        QString getUpdateFrequencyPath();
        QString getUpdateFrequencyCurrentPath();
        void updateWhitelist();
        void updateBlocklist();
        int getMaxLogSize(){ return m_MaxLogSize; }
        virtual bool eventFilter(QObject*, QEvent*);

    public slots:
        void g_ShowAddExceptionDialog() { g_ShowAddDialog(ADD_MODE | EXCEPTION_MODE); };
        void g_ShowAddBlockListDialog() { g_ShowAddDialog(ADD_MODE | BLOCKLIST_MODE); };
        void g_ShowAboutDialog();
        void updateInfo();
        void g_UpdateDaemonStatus();
        void treeItemChanged(QTreeWidgetItem*, int);
        void treeItemPressed(QTreeWidgetItem* item, int column);
        void applyChanges();
        void updateRadioButtonToggled(bool);
        void rootFinished();
        void removeListItems();
        void onTrayIconClicked(QSystemTrayIcon::ActivationReason);
        void checkboxChanged(bool);
        void undoGuiOptions();
        void addLogItem(QString);
        void startStopLogging();
        void openSettingsDialog();
        void showLogRightClickMenu(const QPoint&);
        void hoveredAction(QAction*);
        void whitelistItem(QAction*);
        void rootError(const QString&);
        void rootError(const CommandList&);

    protected:
        void closeEvent ( QCloseEvent * event );

    protected slots:
        void quit();
        void onViewerWidgetRequested();
    
    private slots:
        void onLogViewVerticalScrollbarMoved(int);
        void onLogViewVerticalScrollbarActionTriggered(int);
        void onWhoisTriggered();
        void showCommandsOutput(const CommandList&);
};	

#endif //PEERGUARDIAN_H

