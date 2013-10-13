#include "core.h"

Core::Core(MainWindow *mw, QObject *parent)
    :QObject(parent),
    mMainWindow(mw)
{
}
