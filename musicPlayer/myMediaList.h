#ifndef MYMEDIALIST_H
#define MYMEDIALIST_H
#include <QUrl>
#include <QMap>
#include <QObject>

class playListWidget;


enum PlayMode{playInOrder=0,playRandom=1,playOneCircle=2};

class myMediaList : public QObject
{
    Q_OBJECT
public:
    explicit myMediaList(QObject *parent = 0);
 /*pass pointer*/
    void setTableFinal(playListWidget *pParent){m_pFinal=pParent;}

    QUrl mediaUrl(int index);//赋值给musicIndex;

    QString coverUrl(int index);

    QString songID(int index);

    void addPlayList(const QString& url,const QString&coverUrl=""){m_list.append(url);m_urlMap.insert(url,coverUrl);}

    void addPlayList(const QString &url, const QString &coverUrl="", const QString &ID=""){m_list.append(url);
                                                                                        m_urlMap.insert(url,coverUrl);
                                                                                        m_idMap.insert(url, ID);
                                                                                       }

    const QList<QString> & GetList(){return m_list;}

    const QMap <QString,QString>& GetUrlMap(){return m_urlMap;}

    const QMap <QString, QString>& GetIDMap(){return m_idMap;}

    void setPlayMode(PlayMode);

    void setCurIndex(int index){m_musicIndex=index;}

    int currentMediaIndex(){return m_musicIndex;}

    int nextMediaIndex();

    int preMediaIndex();

    void clearMediaList(){m_list.clear();m_urlMap.clear(); m_idMap.clear();}

public Q_SLOTS:
    void slot_removeSong(int index);
signals:
private:
    int indexMode;
    int m_musicIndex;
    QList<QString> m_list;
    QMap <QString,QString> m_urlMap;   //songUrl-coverUrl
    QMap <QString,QString> m_idMap; //songUrl-songID
    playListWidget *m_pFinal;
};

#endif // MYMEDIALIST_H
