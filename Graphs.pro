#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T14:01:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphs
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS\
           ACTIVE_BRIDGE_COLOR=QColor(205,97,97)\
           PASSIVE_BRIDGE_COLOR=QColor(71,144,119)\
           DEFAULT_BRIDGE_COLOR=QColor(163,170,168)

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    Edits/bridgeedit.cpp \
    Edits/edgeedit.cpp \
    Forms/mainwindow.cpp \
    Forms/visualalgorithm.cpp \
    Forms/visualgraph.cpp \
    SceneElements/bridge.cpp \
    SceneElements/graph.cpp \
    SceneElements/line.cpp \
    SceneElements/myedge.cpp \
    AppElements/CodeEdit/linenumberarea.cpp \
    AppElements/CodeEdit/codeeditor.cpp \
    AppElements/visualgraphsceneview.cpp \
    AppElements/visualalgorithmsceneview.cpp \
    AppElements/mytabwidget.cpp \
    AppElements/CodeEdit/codeeditor.cpp \
    AppElements/CodeEdit/linenumberarea.cpp \
    AppElements/mytabwidget.cpp \
    AppElements/visualalgorithmsceneview.cpp \
    AppElements/visualgraphsceneview.cpp \
    AppElements/CodeEdit/codeeditor.cpp \
    AppElements/CodeEdit/linenumberarea.cpp \
    AppElements/mytabwidget.cpp \
    AppElements/visualalgorithmsceneview.cpp \
    AppElements/visualgraphsceneview.cpp \
    AppElements/CodeEdit/codeeditor.cpp \
    AppElements/CodeEdit/linenumberarea.cpp \
    AppElements/mytabwidget.cpp \
    AppElements/visualalgorithmsceneview.cpp \
    AppElements/visualgraphsceneview.cpp \
    Edits/bridgeedit.cpp \
    Edits/edgeedit.cpp \
    Forms/mainwindow.cpp \
    Forms/visualalgorithm.cpp \
    Forms/visualgraph.cpp \
    SceneElements/bridge.cpp \
    SceneElements/graph.cpp \
    SceneElements/line.cpp \
    SceneElements/myedge.cpp \
    main.cpp \
    AppElements/CodeEdit/codeeditor.cpp \
    AppElements/CodeEdit/linenumberarea.cpp \
    AppElements/mytabwidget.cpp \
    AppElements/visualalgorithmsceneview.cpp \
    AppElements/visualgraphsceneview.cpp \
    Edits/bridgeedit.cpp \
    Edits/edgeedit.cpp \
    Forms/mainwindow.cpp \
    Forms/visualalgorithm.cpp \
    Forms/visualgraph.cpp \
    SceneElements/bridge.cpp \
    SceneElements/graph.cpp \
    SceneElements/line.cpp \
    SceneElements/myedge.cpp \
    main.cpp \
    AppElements/DebugWatch/debugwatch.cpp


HEADERS += \
    Edits/bridgeedit.h \
    Edits/edgeedit.h \
    Forms/mainwindow.h \
    Forms/visualalgorithm.h \
    Forms/visualgraph.h \
    SceneElements/bridge.h \
    SceneElements/graph.h \
    SceneElements/line.h \
    SceneElements/myedge.h \
    AppElements/CodeEdit/linenumberarea.h \
    AppElements/CodeEdit/codeeditor.h \
    AppElements/visualgraphsceneview.h \
    AppElements/visualalgorithmsceneview.h \
    AppElements/mytabwidget.h \
    AppElements/CodeEdit/codeeditor.h \
    AppElements/CodeEdit/linenumberarea.h \
    AppElements/mytabwidget.h \
    AppElements/visualalgorithmsceneview.h \
    AppElements/visualgraphsceneview.h \
    AppElements/CodeEdit/codeeditor.h \
    AppElements/CodeEdit/linenumberarea.h \
    AppElements/mytabwidget.h \
    AppElements/visualalgorithmsceneview.h \
    AppElements/visualgraphsceneview.h \
    AppElements/CodeEdit/codeeditor.h \
    AppElements/CodeEdit/linenumberarea.h \
    AppElements/mytabwidget.h \
    AppElements/visualalgorithmsceneview.h \
    AppElements/visualgraphsceneview.h \
    Edits/bridgeedit.h \
    Edits/edgeedit.h \
    Forms/mainwindow.h \
    Forms/visualalgorithm.h \
    Forms/visualgraph.h \
    SceneElements/bridge.h \
    SceneElements/graph.h \
    SceneElements/line.h \
    SceneElements/myedge.h \
    AppElements/CodeEdit/codeeditor.h \
    AppElements/CodeEdit/linenumberarea.h \
    AppElements/mytabwidget.h \
    AppElements/visualalgorithmsceneview.h \
    AppElements/visualgraphsceneview.h \
    Edits/bridgeedit.h \
    Edits/edgeedit.h \
    Forms/mainwindow.h \
    Forms/visualalgorithm.h \
    Forms/visualgraph.h \
    SceneElements/bridge.h \
    SceneElements/graph.h \
    SceneElements/line.h \
    SceneElements/myedge.h \
    AppElements/DebugWatch/debugwatch.h


FORMS += \
    Edits/bridgeedit.ui \
    Edits/edgeedit.ui \
    Forms/mainwindow.ui \
    Forms/visualalgorithm.ui \
    Forms/visualgraph.ui \

RESOURCES += \
    res.qrc \

SUBDIRS += \
    Graphs.pro
