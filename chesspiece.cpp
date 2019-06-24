#include "chesspiece.h"
//#include <QVariant>

ChessPiece::ChessPiece(int piecetype, int piececolor, const QString& pieceName, const char* icon, QLabel* label)
    :mPieceType(piecetype),mPieceColor(piececolor),mIconPath(icon),mContainerBox(label)
{
    mPieceName = pieceName;

    mContainerBox->setText(icon);
    mContainerBox->setFont(QFont("Helvetica",35));
    mContainerBox->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter );
}
/*
ChessPiece &ChessPiece::operator =(const ChessPiece &rhs)
{
    if ( &rhs == this)
        return *this;

    //free old memory
    delete mContainerBox;

    mPieceType = rhs.mPieceType;
    mPieceColor = rhs.mPieceColor;
    mPieceName = rhs.mPieceName;

    mContainerBox = new QLabel();
    mContainerBox->setObjectName(rhs.mContainerBox->objectName());
    mContainerBox->setProperty("chessindex", rhs.mContainerBox->property("chessindex"));
    mContainerBox->setStyleSheet(rhs.mContainerBox->styleSheet());

}

ChessPiece::ChessPiece(const ChessPiece &rhs)
    :mPieceType(rhs.mPieceType),mPieceColor(rhs.mPieceColor),mPieceName(rhs.mPieceName),mIconPath(rhs.mIconPath),mContainerBox(new QLabel())
{
    mContainerBox->setObjectName(rhs.mContainerBox->objectName());
    mContainerBox->setProperty("chessindex", rhs.mContainerBox->property("chessindex"));
    mContainerBox->setStyleSheet(rhs.mContainerBox->styleSheet());
}
*/

ChessPiece::~ChessPiece(){}

void ChessPiece:: setPieceType(int pieceType)
{
	mPieceType = pieceType;
}

int ChessPiece:: pieceType() const
{
	return mPieceType;
}

void ChessPiece:: setPieceColor(int pieceColor)
{
    mPieceColor = pieceColor;
}

int ChessPiece:: pieceColor() const
{
    return mPieceColor;
}

void ChessPiece::setPieceName(const QString &pieceName)
{
    mPieceName = pieceName;
}

QString ChessPiece::icon() const
{
    return mIconPath;
}

void ChessPiece::setIcon(const QString &str)
{
    mIconPath = str;
}

QString ChessPiece::pieceName() const
{
    return mPieceName;
}

void ChessPiece:: setContainerBox (QLabel* label)
{
    mContainerBox = label;
}

bool ChessPiece::move(QLabel *destLabel)
{
    if ( !destLabel)
        return false;

    mContainerBox->setText("");

    mContainerBox = destLabel;

    mContainerBox->setText(mIconPath);
    mContainerBox->setFont(QFont("Helvetica",35));
    mContainerBox->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter );

    return true;
}

QLabel* ChessPiece::containerBox() const
{
    return mContainerBox;
}
