#include <QDebug>
#include "chesspiece.h"
#include "chessboard.h"
#include <QMouseEvent>
#include <QGridLayout>
#include <QVBoxLayout>

ChessBoard::ChessBoard(QWidget* parent):QWidget(parent), mChessBoxes(new QLabel**[BoxCount]),
    mLastMoveLabel(new QLabel(this))
{
    setGeometry(10, 10, 900, 700);
    setWindowTitle("Chess Game");

    QStringList colIndex;
    colIndex << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h";

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(0);

    //create chess boxes
    for(int i=0;i<BoxCount;i++)
    {
        mChessBoxes[i] = new QLabel*[BoxCount];
        for (int j=0;j<BoxCount;j++)
        {
            mChessBoxes[i][j] = new QLabel(this);
            mChessBoxes[i][j]->setObjectName(QString::number(i)+":"+QString::number(j));
            mChessBoxes[i][j]->setProperty("chessindex", colIndex.at(i)+QString::number(BoxCount-j));

            if( (i+j)%2 == 0)
                mChessBoxes[i][j]->setStyleSheet("QLabel{background-color:#D2B48C};");
            else
                mChessBoxes[i][j]->setStyleSheet("QLabel{background-color:#F0D9B5};");

            grid->addWidget(mChessBoxes[i][j], i, j);
        }
    }
    funcCreateChessPieces();

    mLastMoveLabel->setText("Black To Move");
    mLastMoveLabel->setStyleSheet("QLabel{color: blue;}");
    mLastMoveLabel->setFont(QFont("PT Sans",16));
    grid->addWidget(mLastMoveLabel, BoxCount, 0, 1, -1, Qt::AlignVCenter|Qt::AlignLeft);
}
/*
ChessBoard &ChessBoard::operator =(const ChessBoard &rhs)
{
    if ( &rhs == this)
        return *this;

    delete mPieceInFocus;
    delete mLastMoveLabel;
    //vector manages memory itself

    for (int i=0; i<BoxCount;i++)
    {
        delete[] mChessBoxes[i];
    }
    delete[] mChessBoxes;
    mChessBoxes = Q_NULLPTR;

    QStringList colIndex;
    colIndex << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h";

    for(int i=0;i<BoxCount;i++)
    {
        mChessBoxes[i] = new QLabel*[BoxCount];
        for (int j=0;j<BoxCount;j++)
        {
            mChessBoxes[i][j] = new QLabel(this);
            mChessBoxes[i][j]->setObjectName(rhs.mChessBoxes[i][j]->objectName());
            mChessBoxes[i][j]->setProperty("chessindex", rhs.mChessBoxes[i][j]->property("chessindex"));

            if( (i+j)%2 == 0)
                mChessBoxes[i][j]->setStyleSheet(rhs.mChessBoxes[i][j]->styleSheet());
            else
                mChessBoxes[i][j]->setStyleSheet(rhs.mChessBoxes[i][j]->styleSheet());
        }
    }
    funcCreateChessPieces();
}

ChessBoard::ChessBoard(const ChessBoard &rhs):mChessBoxes(new QLabel**[BoxCount]),
    mLastMoveLabel(new QLabel(this))
{
    QStringList colIndex;
    colIndex << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h";
    mPieceInFocus = rhs.mPieceInFocus;
    mPiecePositionHash = rhs.mPiecePositionHash;
    isBlackTurn = rhs.isBlackTurn;
    for(int i=0;i<BoxCount;i++)
    {
        mChessBoxes[i] = new QLabel*[BoxCount];
        for (int j=0;j<BoxCount;j++)
        {
            mChessBoxes[i][j] = new QLabel(this);
            mChessBoxes[i][j]->setObjectName(rhs.mChessBoxes[i][j]->objectName());
            mChessBoxes[i][j]->setProperty("chessindex", rhs.mChessBoxes[i][j]->property("chessindex"));

            if( (i+j)%2 == 0)
                mChessBoxes[i][j]->setStyleSheet(rhs.mChessBoxes[i][j]->styleSheet());
            else
                mChessBoxes[i][j]->setStyleSheet(rhs.mChessBoxes[i][j]->styleSheet());
        }
    }
    mLastMoveLabel->setText(rhs.mLastMoveLabel->text());
    mLastMoveLabel->setStyleSheet(rhs.mLastMoveLabel->styleSheet());
    mLastMoveLabel->setFont(rhs.mLastMoveLabel->font());
    funcCreateChessPieces();
}
*/
ChessBoard::~ChessBoard()
{
}

void ChessBoard::funcCreateChessPieces()
{
    int col = 0; int row = BoxCount-1; int hashIndex = 0;

    //black pieces creation

    //rook1
    mChessPiece.push_back(new ChessPiece(ChessPiece::Rook, ChessPiece::Black, "Black Rook", "\u265C", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //knight1
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Knight, ChessPiece::Black, "Black Knight", "\u265E", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //bishop1
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Bishop, ChessPiece::Black, "Black Bishop", "\u265D", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //king
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::King, ChessPiece::Black, "Black King", "\u265A", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //queen
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Queen, ChessPiece::Black, "Black Queen", "\u265B", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //bishop2
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Bishop, ChessPiece::Black, "Black Bishop", "\u265D", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //knight2
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Knight, ChessPiece::Black,  "Black Knight","\u265E", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //rook2
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Rook, ChessPiece::Black,  "Black Rook","\u265C", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //pawns
    row = BoxCount-2;hashIndex++;
    for (int col=0; col < BoxCount; col++, hashIndex++)
    {
        mChessPiece.push_back(new ChessPiece(ChessPiece::Pawn, ChessPiece::Black,  "Black Pawn","\u265F", mChessBoxes[row][col]));
        mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);
    }

    //white pieces creation
    row = col = 0;

    //rook1
    mChessPiece.push_back(new ChessPiece(ChessPiece::Rook, ChessPiece::White,  "White Rook","\u2656", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //knight1
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Knight, ChessPiece::White,  "White Knight","\u2658", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //bishop1
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Bishop, ChessPiece::White, "White Bishop", "\u2657", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //king
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::King, ChessPiece::White, "White King","\u2654", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //queen
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Queen, ChessPiece::White, "White Queen","\u2655", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //bishop2
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Bishop, ChessPiece::White,"White Bishop", "\u2657", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //knight2
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Knight, ChessPiece::White,"White Knight", "\u2658", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //rook2
    col++;hashIndex++;
    mChessPiece.push_back(new ChessPiece(ChessPiece::Rook, ChessPiece::White,"White Rook", "\u2656", mChessBoxes[row][col]));
    mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);

    //pawns
    row = 1;hashIndex++;
    for (int col=0; col < BoxCount; col++, hashIndex++)
    {
        mChessPiece.push_back(new ChessPiece(ChessPiece::Pawn, ChessPiece::White, "White Pawn","\u2659", mChessBoxes[row][col]));
        mPiecePositionHash.insert(mChessPiece.at(hashIndex), mChessBoxes[row][col]);
    }

}

bool ChessBoard::funcValidatePieceMove( QLabel* destBox, bool toKill)
{
    if ( !destBox)
        return false;

    int pieceType = mPieceInFocus->pieceType();

    QString sourObjName = mPieceInFocus->containerBox()->objectName();
    int startX = sourObjName.section(":",0,0).toInt();
    int startY = sourObjName.section(":",1,1).toInt();

    QString destObjName = destBox->objectName();
    int destX = destObjName.section(":",0,0).toInt();
    int destY = destObjName.section(":",1,1).toInt();
    //qInfo() << sourObjName << " " << destObjName;
    switch(pieceType)
    {
    case ChessPiece::Pawn:
    {
        if ( toKill) {
            if (!(qAbs(startX-destX) == 1 && qAbs(destY-startY) == 1))
                return false;

        } else {

            int moveLimit = 1;
            if ( (startX == BoxCount-2 && mPieceInFocus->pieceColor() == ChessPiece::Black)
                 || (startX == 1 && mPieceInFocus->pieceColor() == ChessPiece::White))
                moveLimit = 2;

            if (!(destY == startY && qAbs(destX-startX) <= moveLimit))
                return false;

            //no other piece in path
            for( int i = destX > startX ? startX+1:startX-1; qAbs(destX-i) > 0; destX > i ? i++ : i--)
            {
                if (mPiecePositionHash.values().contains(mChessBoxes[i][destY]))
                    return false;
            }
        }
        return true;
    }
    case ChessPiece::Knight:
    {
        if ( !( (qAbs(destX-startX) == 2 && qAbs(destY-startY) == 1)
                || (qAbs(destY-startY) == 2 && qAbs(destX-startX) == 1) ) )
            return false;
        return true;
    }
    case ChessPiece::Queen:
    {
        if ( !((destX+destY == startX+startY || destX-startX == destY-startY ) || (startX == destX || startY == destY)) )
            return false;
    }
    case ChessPiece::Bishop:
    {
        if ( pieceType == ChessPiece::Bishop)
        {
            if ( !(destX+destY == startX+startY || destX-startX == destY-startY ))
                return false;
        }

        if (destX+destY == startX+startY)
        {
            //no other piece in path
            int i,j;
            if ( destX > startX) {
                i = startX+1; j = startY-1;
            } else {
                i = startX-1; j = startY+1;
            }
            for( ; qAbs(destX-i) > 0; )
            {
                if (mPiecePositionHash.values().contains(mChessBoxes[i][j]))
                    return false;
                if ( destX > i) {
                    i++;j--;
                } else {
                    i--;j++;
                }
            }
            return true;
        }
        else if (destX-startX == destY-startY)
        {
            //no other piece in path
            int i,j;
            if ( destX > startX) {
                i = startX+1; j = startY+1;
            } else {
                i = startX-1; j = startY-1;
            }
            for( ; qAbs(destX-i) > 0; )
            {
                if (mPiecePositionHash.values().contains(mChessBoxes[i][j]))
                    return false;
                if ( destX > i) {
                    i++;j++;
                } else {
                    i--;j--;
                }
            }
            return true;
        }
    }

    case ChessPiece::Rook:
    {

        if ( pieceType == ChessPiece::Rook)
            if ( !(startX == destX || startY == destY))
                return false;

        if ( startX == destX)
        {
            //no other piece in path
            for( int i = destY > startY ? startY+1 : startY-1; qAbs(destY-i) > 0; destY > i ? i++ : i--)
            {
                if (mPiecePositionHash.values().contains(mChessBoxes[destX][i]))
                    return false;
            }
            return true;
        }
        else if ( startY == destY)
        {
            //no other piece in path
            for( int i = destX > startX ? startX+1 : startX-1; qAbs(destX-i) > 0; destX > i ? i++ : i--)
            {
                if (mPiecePositionHash.values().contains(mChessBoxes[i][destY]))
                    return false;
            }
            return true;
        }
    }
    case ChessPiece::King:
    {
        if (!(qAbs(destX-startX) == 1 || qAbs(destY-startY) == 1))
            return false;

        return true;
    }
    default:
        break;
    }
    return false;
}

void ChessBoard::mousePressEvent(QMouseEvent * event)
{
    QLabel* child = static_cast<QLabel*>(childAt(event->pos()));        //downcasting
    if (!child) return;

    //no piece in current selected box
    if ( ! mPiecePositionHash.values().contains(child) )
    {
        if ( mPieceInFocus)
        {
            if ( !funcValidatePieceMove( child)) return;
            if ( mPieceInFocus->move(child) )
            {
                QString sourceBox = mPiecePositionHash[mPieceInFocus]->property("chessindex").toString() ;
                mPiecePositionHash[mPieceInFocus] = child;
                isBlackTurn = !isBlackTurn;

                QString infotext = QString(mPieceInFocus->pieceName()+ " moved from "+sourceBox +
                                           " to "+child->property("chessindex").toString())+
                        (isBlackTurn ? " | Black " : " | White ")+"To Move" ;

                mLastMoveLabel->setText(infotext);
                mPieceInFocus = NULL;
            }
        }
        //reset selection
        else
            mPieceInFocus = NULL;

        return;
    }
    //piece present in current selected box
    else
    {
        ChessPiece* pieceInFocus = mPiecePositionHash.key(child);

        if ((pieceInFocus->pieceColor() == ChessPiece::Black && !isBlackTurn )
                || ( pieceInFocus->pieceColor() == ChessPiece::White && isBlackTurn  ))
        {
            if ( ! mPieceInFocus )
                return;
            else
            {
                if ( !funcValidatePieceMove( child, true)) return;
                if ( mPieceInFocus->move(child) )
                {
                    QString sourceBox = mPiecePositionHash[mPieceInFocus]->property("chessindex").toString() ;
                    QString killedPieceName = mPiecePositionHash.key(child)->pieceName();
                    mPiecePositionHash[mPieceInFocus] = child;
                    mPiecePositionHash.remove(pieceInFocus);
                    isBlackTurn = !isBlackTurn;

                    if ( pieceInFocus->pieceType() == ChessPiece::King)
                    {
                        QString infotext = QString(mPieceInFocus->pieceName()+ " moved from "+sourceBox +
                                                   " to kill "+killedPieceName+" at "+child->property("chessindex").toString())+
                                (isBlackTurn ? " | Black " : " | White ")+"Wins!" ;
                        mLastMoveLabel->setText(infotext);
                    }
                    else
                    {
                        QString infotext = QString(mPieceInFocus->pieceName()+ " moved from "+sourceBox +
                                                   " to kill "+killedPieceName+" at "+child->property("chessindex").toString())+
                                (isBlackTurn ? " | Black " : " | White ")+"To Move" ;
                        mLastMoveLabel->setText(infotext);
                    }

                    mPieceInFocus = NULL;
                }
                return;
            }
        }
        //another black chosen for black turn or white for white turn
        else if ((pieceInFocus->pieceColor() == ChessPiece::Black && isBlackTurn )
                 || ( pieceInFocus->pieceColor() == ChessPiece::White && !isBlackTurn  ))
        {
            //fresh selection
            mPieceInFocus = pieceInFocus;
            return;
        }
    }
}
