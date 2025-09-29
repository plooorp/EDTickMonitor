#include <csignal>
#include <QCoreApplication>
#include "globals.hpp"
#include "tickmonitor.hpp"

void stop(int signal)
{
	qApp->exit(0);
}

int main(int argc, char* argv[])
{
	qSetMessagePattern(u"%{time yyyy-MM-dd hh:mm:ss.zzz} %{type} %{message}"_s);
	qDebug() << "EDTickMonitor";
	QCoreApplication::setApplicationName(u"EDTickMonitor"_s);
	QScopedPointer<QCoreApplication> app(new QCoreApplication(argc, argv));

	std::signal(SIGINT, &stop);
	std::signal(SIGTERM, &stop);

	const QStringList referenceSystems =
	{
		// population hubs
		u"Diaguandri"_s,
		u"Shinrarta Dezhra"_s,
		u"Sol"_s,
		// engineer
		u"Alioth"_s,
		u"Deciat"_s,
		u"Laksak"_s,
		u"Wolf 397"_s,
		// powerplay
		u"Cubeo"_s,
		u"Gateway"_s,
		u"Kamadhenu"_s,
		u"Lembava"_s
	};
	TickMonitor* tickMonitor = new TickMonitor(referenceSystems);
	tickMonitor->start();
	return app->exec();
}
