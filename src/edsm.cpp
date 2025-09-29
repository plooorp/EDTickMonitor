#include "edsm.hpp"
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>

using namespace EDSM;

API::API(QObject* parent)
	: m_manager(new QNetworkAccessManager(this))
{}

QNetworkReply* API::system_v1_factions(const QString& systemName, bool showHistory, std::function<void(QNetworkReply* reply, const System& system)> callback)
{
	QUrlQuery query;
	query.addQueryItem(u"systemName"_s, systemName);
	query.addQueryItem(u"showHistory"_s, "0");
	QUrl url(API::BASE_URL + u"/api-system-v1/factions"_s);
	url.setQuery(query);
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
	QNetworkReply* reply = m_manager->get(request);
	connect(reply, &QNetworkReply::finished, this, [this, reply, callback]() -> void
		{
			if (reply->error() == QNetworkReply::NoError)
			{
				QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();
				if (!obj.isEmpty())
					callback(reply, System(obj));
			}
			else
				qDebug() << reply->errorString();
		});
	return reply;
}

const QString API::BASE_URL = u"https://www.edsm.net"_s;
