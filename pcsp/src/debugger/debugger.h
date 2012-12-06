/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DEBUGGER_H_
#define DEBUGGER_H_

#include <QObject>
#include <QString>
#include <QMutex>

class Debugger : public QObject
{
	Q_OBJECT
public:
    static Debugger &self();

    Debugger();

    ~Debugger();

    void initialize();
    void finalize();

	void updateViews();
	
    void writeLog(QString text);
    void displayLog(QStringList lines);
	void flushLog();
	
    void log(QString const &line);
	void logStdout(QString const &line);
	void logStderr(QString const &line);

    QMutex mutex;

signals: 
	void updateViewsSignal();
	void logSignal(QString const &line);
	void logStdoutSignal(QString const &line);
	void logStderrSignal(QString const &line);
};

extern Debugger &debugger;

#endif /* DEBUGGER_H_ */
