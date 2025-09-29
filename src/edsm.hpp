#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "globals.hpp"

namespace EDSM
{
	struct Faction
	{
		int64_t id;
		QString name;
		double influence;
		QDateTime lastUpdate;
		Faction()
			: id(-1)
			, influence(-1)
		{}
		//Faction(const json::object& faction)
		//{
		//	id = faction.at("id").as_int64();
		//	name = faction.at("name").as_string();
		//	influence = faction.at("influence").as_double();
		//	lastUpdate = faction.at("lastUpdate").as_int64();
		//}
		Faction(const QJsonObject& faction)
		{
			id = faction.value(u"id"_s).toInt();
			name = faction.value(u"name"_s).toString();
			influence = faction.value(u"influence"_s).toDouble();
			lastUpdate = QDateTime::fromSecsSinceEpoch(faction.value(u"lastUpdate"_s).toInteger());
		}
	};

	struct System
	{
		int32_t id;
		int64_t id64;
		QString name;
		QList<Faction> factions;
		System()
			: id(-1)
			, id64(-1)
		{}
		//System(const json::object& system)
		//{
		//	id = system.at("id").as_int64();
		//	id64 = system.at("id64").as_int64();
		//	name = system.at("name").as_string();
		//	if (system.contains("factions"))
		//		for (const json::value& faction : system.at("factions").as_array())
		//			factions.insert(Faction(faction.as_object()));
		//}
		System(const QJsonObject& system)
		{
			id = system.value(u"id"_s).toInt();
			id64 = system.value(u"id64"_s).toInteger();
			name = system.value(u"name"_s).toString();
			for (const QJsonValue faction : system.value(u"factions").toArray())
				factions.append(Faction(faction.toObject()));
		}
	};

	class API : public QObject
	{
		Q_OBJECT

	public:
		explicit API(QObject* parent = nullptr);
		QNetworkReply* system_v1_factions(const QString& systemName, bool showHistory, std::function<void(QNetworkReply* reply, const System& system)> callback);

	private:
		static const QString BASE_URL;
		QNetworkAccessManager* m_manager;
	};
}
