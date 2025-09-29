#include "tickmonitor.hpp"
#include <QCoreApplication>
#include <QNetworkReply>

TickMonitor::TickMonitor(const QStringList& referenceSystems, int checkIntervalMS, QObject* parent)
	: QObject(parent)
	, m_referenceSystems(referenceSystems)
	, m_influenceHistory(referenceSystems.size())
	, m_checkIntervalMS(checkIntervalMS)
	, m_timer(new QTimer(this))
	, m_edsmAPI(EDSM::API())
{
	Q_ASSERT(m_referenceSystems.size() > 0);
	Q_ASSERT(m_checkIntervalMS > 0);
	connect(m_timer, &QTimer::timeout, this, &TickMonitor::checkNextSystem);
}

void TickMonitor::checkNextSystem()
{
	m_edsmAPI.system_v1_factions(m_referenceSystems[m_nextSystem], false, [this](QNetworkReply* reply, const EDSM::System& system) -> void
		{
			for (const EDSM::Faction& faction : system.factions)
			{
				if (!m_influenceHistory[m_nextSystem].contains(faction.name))
				{
					m_influenceHistory[m_nextSystem].insert(faction.name, faction);
					continue;
				}
				EDSM::Faction prevFaction = m_influenceHistory[m_nextSystem].value(faction.name);
				if (prevFaction.lastUpdate.toSecsSinceEpoch() > m_lastTick
					&& faction.lastUpdate.toSecsSinceEpoch() > m_lastTick
					&& std::abs(faction.influence - prevFaction.influence) >= .001)
				{
					qDebug() << "Tick detected at" << system.name << faction.name << prevFaction.influence << "at"
						<< QLocale().toString(prevFaction.lastUpdate, QLocale::ShortFormat) << "->" << faction.influence;
					m_influenceHistory[m_nextSystem][faction.name] = faction;
					m_lastTick = QDateTime::currentSecsSinceEpoch();
				}
			}
			++m_nextSystem;
			if (m_nextSystem == m_referenceSystems.size())
				m_nextSystem = 0;
			reply->deleteLater();
		});
}

void TickMonitor::start()
{
	m_timer->start(m_checkIntervalMS);
}

void TickMonitor::stop()
{
	m_timer->stop();
}
