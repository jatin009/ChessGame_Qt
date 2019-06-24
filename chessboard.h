#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QHash>
#include <QVector>

class QLabel;
class QMouseEvent;
class ChessPiece;

class ChessBoard: public QWidget
{
    Q_OBJECT

public:
    ChessBoard(QWidget* parent=0);
    ChessBoard(const ChessBoard&)=delete;
    ChessBoard& operator =(const ChessBoard&)=delete;
    virtual ~ChessBoard();

private:
    ChessPiece* mPieceInFocus = Q_NULLPTR;

    QHash<ChessPiece*, QLabel*> mPiecePositionHash;

    bool isBlackTurn = true;
    static const int BoxCount = 8;

    QLabel*** mChessBoxes ;
    QLabel* mLastMoveLabel;
    QVector<ChessPiece*> mChessPiece;

    void funcCreateChessPieces();
    bool funcValidatePieceMove( QLabel*, bool toKill=false);
    void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
};

#endif
