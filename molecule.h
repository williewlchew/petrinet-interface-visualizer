////////////////////////////////////////////////////////////////////
/*
 * Molecule object:
 *  -Stores base data and attributes of a molecule
 *  -Has methods of how to draw the molecule
 *  -Has methods on encoding and decoding the molecule
 */
////////////////////////////////////////////////////////////////////
#ifndef MOLECULE_H
#define MOLECULE_H

#include <iostream>
#include <QtWidgets>
#include <vector>
#include <QObject>

#include "visualeditor.h"
#include "attributelist.h"

////////////////////////////////////////////////////////////////////
class Molecule : public QObject
{
    Q_OBJECT

    public:
        //Constructors
        Molecule();
        ~Molecule();

        //Base Info
        void setName(std::string nameInput);
        std::string getName();
        void setColor(int input);
        QColor getColor();

        //Visual
        QLabel* label;
        QLabel* DrawMolecule(QFrame* parent);
        void EditMolecule(QFrame* parent);

    signals:
        void Changed();

    public slots:
        void updateMoleculeLabel();

    private:
       //Base Data
       AttributeList* attributes;

       VisualEditor* editor;


};

#endif // MOLECULE_H
