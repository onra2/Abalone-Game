#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include "hexacell.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QString>
#include <QLineEdit>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <array>
#include <cmath>
#include <exception>
#include "point.hpp"
#include "iObserver.h"
#include "iObservable.h"
#include "config.h"
#include <string>

class MainWindow : public QMainWindow, public iObserver, iObservable
{
    Q_OBJECT
private slots:
    void ButtonOnClick();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    /*!
     * \brief An array to easily convert letters in x coord
     */
    constexpr static std::array<char,9> charsCoord {'I','H','G','F','E','D','C','B','A'};

    QGraphicsScene * scene;

    int SIZE = BoardSize;

    bool eventFilter(QObject *_o, QEvent *_e) ;

    /*!
     * \brief Grid containing all hexacells
     */
    std::vector<std::vector<HexaCell*>> grid;
    /*!
     * \brief Updates the board
     */
    void displayBoard(std::array<std::array<int, BoardSize>, BoardSize> marbles);
    /*!
     * \brief Displays the scores
     */
    void displayHeader(std::array<int, 2> scores);
    /*!
     * \brief Displays who's turn it is
     */
    void currentPlayer(int* player);
    /*!
     * \brief Shows a message
     */
    void displayMessage(std::string error);
    /*!
     * \brief Displays the winner
     */
    void displayWinner(int* player);

    /*!
     * \brief The textbox used for abapro notation
     */
    QLineEdit * AbaProTxtBox;

    /*!
     * \brief The button to play your turn based on the abapro notation provided
     */
    QPushButton *m_button;

    /*!
     * \brief Labels displaying the scores of the players
     */
    std::array<QGraphicsTextItem*,2> playerScoresLabels;
    /*!
     * \brief The observers list
     */
    std::list<iObserver *> observers;

    /*!
     * \brief It will init the label and colors to show who's turn it is
     */
    void initScoreControl(QGraphicsScene * scene);

    /*!
     * \brief It will create labels for an easier use of abapro
     */
    void initSideLetters(QGraphicsScene * scene);

    /*!
     * \brief It will init labels and buttons
     */
    void initButtons(QGraphicsScene * scene);

    /*!
     * \brief unselect all hexacell
     */
    void unselectAll();

    /*!
     * \brief on hexacell selected it will add coordinate in the textline
     * \param coordinate the ABAPRO coordinate to add
     */
    void selectHexacell(std::string * coordinate);

    /*!
     * \brief on hexacell unselected it will remove coordinate in the textline
     * \param coordinate the ABAPRO coordinate to remove
     */
    void unselectHexacell(std::string * coordinate);

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    virtual void update(std::string name, void *);
    /*!
     * \brief Add a observer on MainWindow
     * \param observer the observer to add
     */
    virtual void addObserver(iObserver * observer);

    /*!
     * \brief Remove a observer on MainWindow
     * \param observer the observer to remove
     */
    virtual void removeObserver(iObserver * observer);

    /*!
     * \brief Notify all observer
     */
    virtual void notify(std::string name, void * object);
};
#endif // MAINWINDOW_H
