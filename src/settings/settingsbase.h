#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QGroupBox>

class SettingsBase : public QGroupBox
{
    Q_OBJECT
public:
    explicit SettingsBase(QWidget *parent = 0);
//    virtual ~SettingsBase();

    // Read and save the settings
    virtual void save() = 0;
    virtual void read() = 0;

//    inline void setPageTitle(const QString &t) {
//        mPageTitle = t;
//    }

//    inline QString pageTitle() const {
//        return mPageTitle;
//    }

//    inline void setPageDescription(const QString &d) {
//        mPageDescription = d;
//    }

//    inline QString pageDescription() const {
//        return mPageDescription;
//    }

//private:
//    QString mPageTitle,
//            mPageDescription;
signals:
    
public slots:
    
};

#endif // SETTINGSBASE_H
