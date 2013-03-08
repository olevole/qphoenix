#ifndef PLUGINCONNECTOR_H
#define PLUGINCONNECTOR_H

class MainWindow;
class Config;

struct PluginConnector
{
    PluginConnector() {
        QP_MainWindow = QP_ConfigDialog = NULL;
    }

    MainWindow *QP_MainWindow;
    Config *QP_ConfigDialog;
};


#endif // PLUGINCONNECTOR_H
