#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QLabel>

class ChessPiece: public QLabel
{
    Q_OBJECT
	
	public: 
		enum PieceType{
			Pawn,
			Rook,
			Bishop,
			Knight,
			Queen,
			King,
			None
		};
		
		enum PieceColor{
			Black,
            White
		};

        explicit ChessPiece(int, int, const QString&, const char*, QLabel*);
        ChessPiece(const ChessPiece&)=delete;
        ChessPiece& operator =(const ChessPiece &) =delete;
        virtual ~ChessPiece();

        int pieceType() const;
		void setPieceType(int);

        int pieceColor() const;
		void setPieceColor(int);

        QString pieceName() const;
        void setPieceName(const QString&);

        QString icon() const;
        void setIcon(const QString&);

        QLabel* containerBox() const;
        void setContainerBox(QLabel* );

        bool move(QLabel* destLabel);

	private:
		int mPieceType;
		int mPieceColor;
        QString mPieceName;
		QString mIconPath;
		QLabel* mContainerBox;

};

#endif
