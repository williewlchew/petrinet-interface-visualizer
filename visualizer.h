////////////////////////////////////////////////////////////
/*
 * The Visualizer
 *  -canvas in which the objects draw themselves on
 *  -sets up where each object should draw themselves
 *  -responsible for drawing lines
 */
////////////////////////////////////////////////////////////
#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QtWidgets>
#include <QFrame>
#include <QObject>

#include "visualeditor.h"
#include "event.h"

///////////////////////////////////////////////////////////
class Visualizer : public QFrame
{
    Q_OBJECT

    public:
        //constructor
        Visualizer(QWidget *parent = nullptr, Event* eventPtr = nullptr);
        virtual ~Visualizer();

    private:
        Event* event;
        QVBoxLayout *layout;
        QBoxLayout* inputList;
        QBoxLayout* outputList;
        QLabel* eventLabel;

        //Event menu manipulation variables
        QLabel* menuTempChild;
        QLabel* menuClipboard;
        QPoint menuPoint;

        //Paint Event Variables
        std::vector<QPoint*> linePoints;

        //helper methods
        void clearVisualizer();

    private slots:
        void EditAction();
        void CopyAction();
        void CutAction();
        void DeleteAction();
        void AddAction();
        void SaveAction();

    public slots:
        void DrawLines();

    protected:
        void ShowContextMenu(const QPoint &pos, QLabel* child);
        void paintEvent(QPaintEvent* QEvent);
        void mousePressEvent(QMouseEvent *QEvent) override;
        void dragEnterEvent(QDragEnterEvent *QEvent) override;
        void dragMoveEvent(QDragMoveEvent *QEvent) override;
        void dropEvent(QDropEvent *QEvent) override;
};
////////////////////////////////////////////////////////////

#endif //VISUALIZER_H
