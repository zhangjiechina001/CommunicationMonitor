#ifndef WIDGETUTILSNEW_H
#define WIDGETUTILSNEW_H
#include <QWidget>
#include <functional>
#include <QDebug>

namespace WidgetUtils {

    template<typename Func>
    void Execute(QWidget *widget,Func func,bool showExMsg=true)
    {
        try
        {
            widget->setEnabled(false);
            func();
        }
        catch(QString ex)
        {
//            if(showExMsg)
//            {
//                WidgetUtilsNew::ShowWarning(ex);
//            }
            qDebug()<<ex;
        }
        widget->setEnabled(true);
    }

    class WidgetUtilsNew
    {
    public:
        WidgetUtilsNew();
        static void ShowWarning(const QString &warningText);
    };

}


#endif // WIDGETUTILSNEW_H
