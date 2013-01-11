#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <QMap>

typedef QMap<QString, QPluginLoader*> PluginList;


class Loader : public OQbject
{
    Q_OBJECT
public:
    explicit Loader(QObject *parent = 0);


    /*!
     * \brief addSearchPaths
     * add path to search plugins
     * \param lst
     */

    void addSearchPaths(const QStringList &lst);


    /*!
     * \brief update
     * Update information about plugins (list, names, etc)
     */
    void update();


    QStringList names() const;

    bool load(const QString &name);

    PluginList *loadedPlugins();

    
signals:
    
public slots:
    
};

#endif // LOADER_H
