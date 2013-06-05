#ifndef PLUGINCONNECTOR_H
#define PLUGINCONNECTOR_H

class MainWindow;
class Config;

struct PluginConnector
{
    PluginConnector() {
        QP_MainWindow = QP_ConfigDialog = NULL;
    }

    MainWindow *MainWindow;
    Config *ConfigDialog;
};


#endif // PLUGINCONNECTOR_H
