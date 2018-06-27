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

#include "visualeditor.h"
#include "event.h"

///////////////////////////////////////////////////////////
class Visualizer : public QFrame
{
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

        //helper methods
        void clearVisualizer();

    public slots:
        void updateVisualizer();

    protected:
        void mousePressEvent(QMouseEvent *QEvent) override;
        void dragEnterEvent(QDragEnterEvent *QEvent) override;
        void dragMoveEvent(QDragMoveEvent *QEvent) override;
        void dropEvent(QDropEvent *QEvent) override;
};
////////////////////////////////////////////////////////////

#endif //VISUALIZER_H
