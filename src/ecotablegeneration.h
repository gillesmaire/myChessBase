#ifndef ECOTABLEGENERATION_H
#define ECOTABLEGENERATION_H

 #include <chess.hpp>
 #include <QSqlQuery>

///
/// \brief The EcoTableGeneration class create the table ECO in the database 
/// The table is built from an ECO file from Davif Barnes File (DBF)
/// The structure of the table is  :
///   ECO      : from A00 to E99, the value is given by DBF
///   ECOPLUS  : is ECO plus xx from A00aa to E99zz to extend the number of moves calculated here
///   OPENING  : official name of variation more official than in PGN files  given by DBF
///   VARIATION: the variation  given by DBF
///   MOVES    : the list moves of the variation given by DBF
///   NBM      : is Number of moves in the variation to be able to make select ordered by number of moves
///   WINS     : number of games win in the variation given periodically by the DATABASE
///   LOSTS    : number of games lost in the variation given periodically by the DATABASE
///   EQUALS   : number of equal machs in the variatoion givent periodically by the DATABASE

///  Here is construct 2014 tables with the folowing convention :
/// 
///   the Name of the table is ECO+ECOPLUS A00aa the last one is E99ab following the convention 
///   sugggered by the  classification from David J. Barnes (d.j.barnes@kent.ac.uk)
/// 
/// The table  A00aa contains :
///   ID : for a game
///   MOVES : the list of moves from A00 (b4) isnot in the list
///   BLACK : black player name
///   BLACKELO : 
///   BLACKFIDEID 
///   BLACTITLE 
///   DATE of game
///   Event 
///   Result 
///   Round 
///   SITE 
///   WHITEELO
///   WHITEFIDDEID
///   WHITETITLE
/// 
class CountString {
private:
    int right; // Partie pour la première lettre ('a' à 'z')
    int left;  // Partie pour la deuxième lettre ('a' à 'z' )
    int MAXDigit=0;

public:
    CountString() :  right('a'),left('a') {}

    CountString& operator++() {
        if (right >= 'a' && right < 'z') {
            ++right;
        } else if (right == 'z') {
            right = 'a';  
            if (left >= 'a' && left < 'z') ++left;
        } 
        int val =(left-'a')*26+right-'a';
        if ( val> MAXDigit) MAXDigit=val;
        return *this;
    }
    void Increment()
    {
     ++(*this);
    }
    // Opérateur de post-incrémentation
    CountString operator++(int) {
        CountString temp = *this;
        ++(*this); // Appelle l'opérateur de pré-incrémentation
        return temp;
    }

    // Méthode pour obtenir la chaîne sous forme de QString
    QString toQString() const {
        return QString(QChar(left)) + QChar(right);
    }
    void Raz() { left='a'; right='a';}
    QString Max() { int l = MAXDigit/26; 
                    int r = MAXDigit%26 ;
                 QChar cl(l);
                 QChar cr(r);
                 return QString(cl)+QString(cr);
                 }
};


class EcoTableGeneration : public chess::pgn::Visitor
{
public:
    EcoTableGeneration();
    virtual ~EcoTableGeneration() {} 
    
    void startPgn();
     

    void header(std::string_view key, std::string_view value);

    void startMoves() {}

    void move(std::string_view move, std::string_view comment);

    void endPgn();
    
    void setSqlHandler(QSqlDatabase *db);
    bool CountZZ(){ return(mcountzz); };
    QString maxECOplusCount()
      {
       return mEcoPlusCount.Max();
      }
private:
     QStringList mRecords,mValues,mMoves;
     QString mLastECO;
     chess::PackedBoard BitBoard(QStringList moves);
     QString FEN(QStringList moves);
     QSqlDatabase *mdb;
     CountString mEcoPlusCount;
     bool mcountzz = false;
     bool mStagingTableCreated = false;
     
     
     
};
#endif // ECOTABLEGENERATION_H

