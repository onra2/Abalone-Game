#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    const std::array<std::tuple<int, int>, 61> initalPosition = {
        std::make_tuple(0, 4),
        std::make_tuple(0, 5),
        std::make_tuple(0, 6),
        std::make_tuple(0, 7),
        std::make_tuple(0, 8),

        std::make_tuple(1, 3),
        std::make_tuple(1, 4),
        std::make_tuple(1, 5),
        std::make_tuple(1, 6),
        std::make_tuple(1, 7),
        std::make_tuple(1, 8),

        std::make_tuple(2, 2),
        std::make_tuple(2, 3),
        std::make_tuple(2, 4),
        std::make_tuple(2, 5),
        std::make_tuple(2, 6),
        std::make_tuple(2, 7),
        std::make_tuple(2, 8),

        std::make_tuple(3, 1),
        std::make_tuple(3, 2),
        std::make_tuple(3, 3),
        std::make_tuple(3, 4),
        std::make_tuple(3, 5),
        std::make_tuple(3, 6),
        std::make_tuple(3, 7),
        std::make_tuple(3, 8),

        std::make_tuple(4, 0),
        std::make_tuple(4, 1),
        std::make_tuple(4, 2),
        std::make_tuple(4, 3),
        std::make_tuple(4, 4),
        std::make_tuple(4, 5),
        std::make_tuple(4, 6),
        std::make_tuple(4, 7),
        std::make_tuple(4, 8),

        std::make_tuple(5, 0),
        std::make_tuple(5, 1),
        std::make_tuple(5, 2),
        std::make_tuple(5, 3),
        std::make_tuple(5, 4),
        std::make_tuple(5, 5),
        std::make_tuple(5, 6),
        std::make_tuple(5, 7),

        std::make_tuple(6, 0),
        std::make_tuple(6, 1),
        std::make_tuple(6, 2),
        std::make_tuple(6, 3),
        std::make_tuple(6, 4),
        std::make_tuple(6, 5),
        std::make_tuple(6, 6),

        std::make_tuple(7, 0),
        std::make_tuple(7, 1),
        std::make_tuple(7, 2),
        std::make_tuple(7, 3),
        std::make_tuple(7, 4),
        std::make_tuple(7, 5),

        std::make_tuple(8, 0),
        std::make_tuple(8, 1),
        std::make_tuple(8, 2),
        std::make_tuple(8, 3),
        std::make_tuple(8, 4)
    };

    this->scene = new QGraphicsScene();

    double rad = 45;
    double w = sqrt(3) / 2 * rad;
    double p = 10.5;

    int x, y;
    this->grid = std::vector<std::vector<HexaCell*>>(this->SIZE);

    std::fill(this->grid.begin(), this->grid.end(), std::vector<HexaCell*>(this->SIZE));
    for(int i(0); i < this->SIZE; ++i){
        std::fill(this->grid.at(i).begin(), this->grid.at(i).end(), nullptr);
    }

    for(std::tuple<int, int> pc : initalPosition){
        x = std::get<0>(pc);
        y = std::get<1>(pc);
        this->grid.at(x).at(y) = new HexaCell(charsCoord.at(x) + std::to_string(y+1), rad, w*(2*y+x), 2*x*w - p*x, nullptr);
        this->grid.at(x).at(y)->addObserver(this);
        this->scene->addItem(this->grid.at(x).at(y));
    }

    initScoreControl(scene);
    initSideLetters(scene);
    initButtons(scene);

    QGraphicsView * view = new QGraphicsView(scene);

    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::TextAntialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->update();

    resize(1000, 800);

    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    for( int i = 0; i < this->SIZE; i++ ) {
        for( int j = 0; j < this->SIZE; j++ ) {
            if(this->grid.at(i).at(j) != nullptr){
                delete this->grid.at(i).at(j);
            }
        }
    }
}

void MainWindow::initScoreControl(QGraphicsScene * scene){

    this->playerScoresLabels.at(0) = scene->addText("Black: 0");
    this->playerScoresLabels.at(0)->setPos(QPointF(0,0));

    this->playerScoresLabels.at(1) = scene->addText("White: 0");
    this->playerScoresLabels.at(1)->setPos(QPointF(0,25));

    for(size_t i(0); i< this->playerScoresLabels.size(); ++i){
        auto font = this->playerScoresLabels.at(i)->font();
        font.setBold(true);
        font.setItalic(true);
        font.setPixelSize(20);
        this->playerScoresLabels.at(i)->setFont(font);
    }
}

void MainWindow::initSideLetters(QGraphicsScene *scene)
{
    int fontSize = 15;
    for (int i = 0; i < 9; ++i) {
        QString strLetter;
        QString strNumber;
        switch (i) {
            case 0: strLetter = QString::fromUtf8("I");
                break;
            case 1: strLetter = QString::fromUtf8("H");
                break;
            case 2: strLetter = QString::fromUtf8("G");
                break;
            case 3: strLetter = QString::fromUtf8("F");
                break;
            case 4: strLetter = QString::fromUtf8("E");
                break;
            case 5:
                strLetter = QString::fromUtf8("D");
                strNumber = QString::fromUtf8("9");
                break;
            case 6:
                strLetter = QString::fromUtf8("C");
                strNumber = QString::fromUtf8("8");
                break;
            case 7:
                strLetter = QString::fromUtf8("B");
                strNumber = QString::fromUtf8("7");
                break;
            case 8:
                strLetter = QString::fromUtf8("A");
                strNumber = QString::fromUtf8("6");
                break;
        }
        double rad = 45;
        double w = sqrt(3) / 2 * rad;
        double p = 10.5;

        //side letters
        QGraphicsTextItem* aLetter = scene->addText(strLetter);
        auto font = aLetter->font();
        font.setPixelSize(fontSize);
        aLetter->setFont(font);
        if(i < 5){
            aLetter->setPos(QPointF((w*-i) + (rad*p)/2, (-p -5.5)+(2*w -p)*i));
        }
        else{
            aLetter->setPos(QPointF((w*i) - (rad/p)*2 - (w*1.5), (-p-5.5)+(2*w-p)*i));
        }

        //side numbers
        QGraphicsTextItem* sideNumber = scene->addText(strNumber);
        sideNumber->setFont(font);
        if(i >= 5){
            sideNumber->setPos(QPointF(-i * w + 2 * rad * p + w + 5.5, -p*3+(2*w-p)*i));
        }

        if(i < 5){
            std::string chiffre = std::to_string(i + 1);
            //lower numbers
            QGraphicsTextItem* lowerNumber = scene->addText(QString::fromStdString(chiffre));
            lowerNumber->setFont(font);
            lowerNumber->setPos(QPointF(336 + 2*w*i, rad * 13));
        }
    }
}

void MainWindow::initButtons(QGraphicsScene * scene){
    this->AbaProTxtBox = new QLineEdit();
    //this->AbaProTxtBox->setText("I7H6");
    this->AbaProTxtBox->resize(800,25);
    this->AbaProTxtBox->setMinimumSize(800,50);
    this->AbaProTxtBox->move(0,650);
    this->AbaProTxtBox->installEventFilter(this);
    scene->addWidget(AbaProTxtBox);

    this->m_button = new QPushButton();
    this->m_button->setText("Move");
    this->m_button->resize(100, 50);
    this->m_button->move(800, 650);
    scene->addWidget(m_button);
    connect(m_button, &QPushButton::released, this, &MainWindow::ButtonOnClick);
}

void MainWindow::displayBoard(std::array<std::array<int, 9>, 9> marbles)
{
    int shift = 4;
    int limit = 9;
    for ( int i = 0; i < 9; i++ ) {
        for ( int j = shift; j < limit; j++ ) {
            if (marbles.at(i).at(j) == -1) {
                if(this->grid.at(i).at(j) != nullptr){
                    this->grid.at(i).at(j)->setPlayer(0);
                }
            }
            else {
                if(this->grid.at(i).at(j) != nullptr){
                    this->grid.at(i).at(j)->setPlayer(marbles.at(i).at(j));
                }
            }
        }
        if (shift > 0) {
            --shift;
        }
        else if (shift == 0) {
            --limit;
        }
    }
    this->repaint();
}

void MainWindow::displayHeader(std::array<int, 2> scores)
{
    std::string score1 = std::to_string(scores.at(0));
    std::string text1 = "Black: " + score1;
    playerScoresLabels.at(0)->setPlainText(text1.c_str());

    std::string score2 = std::to_string(scores.at(1));
    std::string text2 = "White: " + score2;
    playerScoresLabels.at(1)->setPlainText(text2.c_str());
}

void MainWindow::currentPlayer(int* player)
{
    //reset color
    for(size_t i(0); i < this->playerScoresLabels.size(); ++i){
        this->playerScoresLabels.at(i)->setDefaultTextColor(Qt::black);
    }

    //set color
    this->playerScoresLabels.at(*player-1)->setDefaultTextColor(Qt::red);
}

void MainWindow::displayMessage(std::string message)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromUtf8(message.c_str()));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Message");
    msgBox.exec();
}

void MainWindow::displayWinner(int *player)
{
    std::string winner = "";
    if(*player == 2){
        winner = "White";
    }
    else{
        winner = "Black";
    }

    this->displayMessage(winner + " player won!");
}

void MainWindow::ButtonOnClick()
{
    std::string textBox = this->AbaProTxtBox->text().toStdString();
    std::array<std::string, 3> * result = new std::array<std::string, 3>();
    std::transform(textBox.begin(), textBox.end(), textBox.begin(), ::toupper);

    if(textBox.length() != 4 && textBox.length() != 6){
        this->displayMessage("Please use only ABA-PRO notation.\nExemple: A1B2 or A1A3B2");
    }
    else {
        for (size_t i(0); i < sizeof(char[6]) && i + 2 <= textBox.size(); i = i + 2) {
            result->at(i / 2) = textBox.substr(i, 2);
        }

        unselectAll();
        this->notify("ABAPROMove", result);//todo trier le tableau
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        this->ButtonOnClick();
    }
}

bool MainWindow::eventFilter(QObject *_o, QEvent *_e)
{
    if(_e->type() == QEvent::KeyPress)
    {
        QKeyEvent* eventKey = static_cast<QKeyEvent*>(_e);
        if(eventKey->key() == Qt::Key_Return || eventKey->key() == Qt::Key_Enter)
        {
            this->ButtonOnClick();
            return true;
        }
    }
    this->scene->update();
    return QObject::eventFilter(_o, _e);
}

void MainWindow::unselectAll(){
    for (int x(0); x < this->SIZE; ++x) {
        for (int y(0); y < this->SIZE; ++y) {
            if(this->grid.at(x).at(y) != nullptr){
                this->grid.at(x).at(y)->unselect();
            }
        }
    }
    this->AbaProTxtBox->setText("");
}

void MainWindow::selectHexacell(std::string * coordinate){
    QString qstr = QString::fromUtf8(coordinate->c_str());
    this->AbaProTxtBox->setText(this->AbaProTxtBox->text() + qstr);
}

void MainWindow::unselectHexacell(std::string * coordinate){
    std::string originalStr = this->AbaProTxtBox->text().toStdString();

    char* original = originalStr.data();
    char* pattern = coordinate->data();
    int lenght = strlen(pattern);

    char* ptr = strstr(original, pattern);
    strcpy(ptr, ptr + lenght);

    QString qstr = QString::fromUtf8(original);
    this->AbaProTxtBox->setText(qstr);
}

void MainWindow::update(std::string name, void * object) {
    if (name == "Board") {
        std::array<std::array<int, 9>, 9> * marbels;
        marbels = static_cast<std::array<std::array<int, 9>, 9> *>(object);

        this->displayBoard(*marbels);
    }
    else if (name == "Score") {
        this->displayHeader(*static_cast<std::array<int, 2> *>(object));
    }
    else if (name == "currentPlayer") {
        int * player = static_cast<int *>(object);
        this->currentPlayer(player);
    }
    else if (name == "displayWinner") {
        this->displayWinner(static_cast<int *>(object));
    }
    else if (name == "error") {
        std::exception * str = static_cast<std::exception *>(object);
        this->displayMessage(str->what());
    }
    else if(name == "selectedHexaCell"){
        selectHexacell(static_cast<std::string *>(object));
    }
    else if(name == "unselectedHexaCell"){
        unselectHexacell(static_cast<std::string *>(object));
    }
    else if(name == "unselectAll"){
        this->unselectAll();
    }
    else {
        throw new std::exception();
    }
}

void MainWindow::addObserver(iObserver * observer) {
    observers.push_back(observer);
}

void MainWindow::removeObserver(iObserver * observer) {
    observers.remove(observer);
}

void MainWindow::notify(std::string name, void * object) {
    for (iObserver * o : observers) {
        o->update(name, object);
    }
}
