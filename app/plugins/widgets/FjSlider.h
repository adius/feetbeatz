#pragma once

#include <QSvgRenderer>

#include "BaseWidget.h"

class FjSlider: public BaseWidget
{
	//Tell the Qt-Preprocessor this is a QObject
	Q_OBJECT

	//Register widget as plugin for use in QML
	MTQ_QML_PLUGIN_REGISTRATION(FjSlider, "widgets")

	//QProperties: access attributes from QML.
	//Here we define the getters and setters to be used
	Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
	FjSlider(QQuickItem *parent = 0);

	void paint(QPainter *painter);

	qreal value() const;
	void setValue(const qreal value);
	bool active() const;
	void setActive(const bool state);

private:
	bool m_active;
	qreal m_value;
	QSvgRenderer *m_svgRenderer;

	void setValueByTapX(int x);

public slots:
	void test();


protected:
	void processTapDown(mtq::TapEvent *event);
	void processTapUp(mtq::TapEvent *event);
	void processTapCancel(mtq::TapEvent *event);

signals:
	void valueChanged(qreal value);
	void activeChanged(bool active);

};
