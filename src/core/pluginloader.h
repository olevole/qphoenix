#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>


namespace Core {

class PipePluginLoader : public QObject
{
    Q_OBJECT
public:
    explicit PipePluginLoader(QObject *parent = 0);
    
signals:
    
public slots:
    
};




} // namespace Core



#endif // PLUGINLOADER_H
