#ifndef RECURRING_H
#define RECURRING_H

#include "precompiled.h"

class MainWindow;
struct Tx;

enum Schedule {
    DAY = 1,
    WEEK,
    MONTH,
    YEAR
};

QString schedule_desc(Schedule s);

struct RecurringPaymentInfo {
    QString         desc;
    QString         fromAddr;
    QString         toAddr;
    double          amt;
    QString         memo;
    QString         currency;
    Schedule        schedule;
    int             numPayments;

    QDateTime       startDate;
    int             completedPayments;

    QString getScheduleDescription() {
        return "Every " % schedule_desc(schedule) % ", starting " % startDate.toString("yyyy-MMM-dd")
            % ", for " % QString::number(numPayments) % " payments";
    }
};

class Recurring
{
public:
    static Recurring* getInstance() { if (!instance) { instance = new Recurring(); } return instance; }

    RecurringPaymentInfo*    getNewRecurringFromTx(QWidget* parent, MainWindow* main, Tx tx, RecurringPaymentInfo* rpi);
    
    QDateTime    getNextPaymentDate(Schedule s);
    void         updateInfoWithTx(RecurringPaymentInfo* r, Tx tx);
private:
    Recurring() = default;
    static Recurring* instance;
};


#endif // RECURRING_H