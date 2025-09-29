#pragma once

#include <QTimer>
#include "edsm.hpp"

class TickMonitor : public QObject
{
	Q_OBJECT

public:
	explicit TickMonitor(const QStringList& referenceSystems, int checkInterval = 60000, QObject* parent = nullptr);
	void start();
	void stop();

private slots:
	void checkNextSystem();

private:
	QList<QMap<QString, EDSM::Faction>> m_influenceHistory;
	QStringList m_referenceSystems;
	int m_checkIntervalMS;
	QTimer* m_timer;
	EDSM::API m_edsmAPI;
	int64_t m_lastTick = 0;
	int m_nextSystem = 0;
};
