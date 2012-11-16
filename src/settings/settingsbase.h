#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QObject>

class SettingsBase : public QObject
{
    Q_OBJECT
public:
    explicit SettingsBase(QObject *parent = 0);
    
    void save() = 0;
    void read() = 0;

    inline void setPageTitle(const QString &t) {
        mPageTitle = t;
    }

    inline QString pageTitle() const {
        return mPageTitle;
    }

    inline void setPageDescription(const QString &d) {
        mPageDescription = d;
    }

    inline QString pageDescription() const {
        return mPageDescription;
    }

private:
    QString mPageTitle,
            mPageDescription;
signals:
    
public slots:
    
};

#endif // SETTINGSBASE_H
