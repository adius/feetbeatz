#include "AngleSlider.h"

#include <QPainter>

#include "Design.h"

//We need to register this Type in MTQ
MTQ_QML_REGISTER_PLUGIN(AngleSlider)

//This is a neat circular slider, with values from 0 to 2pi
AngleSlider::AngleSlider(QQuickItem *parent)
	: BaseWidget(parent),
	  m_value(30),
	  m_active(false)
{
	setWidth(500);
	setHeight(500);
}

void AngleSlider::paint(QPainter *painter)
{
	forceSquare();

	int margin = height() / 8;
	qreal borderThickness = 8;
	int rotationIndicatorSize = height()/10;

	painter->setRenderHint(QPainter::Antialiasing);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);


	//draw main ellipses
	painter->setPen(QPen(QBrush(design::normalColor),borderThickness));
	painter->drawEllipse(QRect(margin/2,
							  margin/2,
							  width() - margin,
							  height() - margin));

	painter->drawEllipse(QRect(margin/2 + rotationIndicatorSize,
							  margin/2 + rotationIndicatorSize,
							  width() - margin - 2*rotationIndicatorSize,
							  height() - margin - 2*rotationIndicatorSize));


	//draw Rotation indicator
	painter->setPen(QPen(QBrush(design::normalColor),0));
	int rotationIndicatorX = cos(m_value)
								* (width()/2 - rotationIndicatorSize/2 - margin/2);
	int rotationIndicatorY = sin(m_value)
								* (height()/2 - rotationIndicatorSize/2 - margin/2);

	if(m_active)
		painter->setBrush(QBrush(design::activeColor));
	else
		painter->setBrush(QBrush(design::normalColor));

	painter->drawEllipse(QRect(width()/2 + rotationIndicatorX - rotationIndicatorSize/2,
							  height()/2 + rotationIndicatorY - rotationIndicatorSize/2,
							  rotationIndicatorSize,
							  rotationIndicatorSize));


	//draw caption of rotation indicator
	if(m_active) {
		QString valueString;
		valueString.sprintf("%.2f",m_value);
		painter->setPen(design::darkTextColor);
		painter->setFont(design::labelFont);

		painter->drawText(QRect(width()/2 + rotationIndicatorX - rotationIndicatorSize/2,
								  height()/2 + rotationIndicatorY - rotationIndicatorSize/2,
								  rotationIndicatorSize,
								  rotationIndicatorSize),
						  Qt::AlignCenter , valueString);
	}
}

void AngleSlider::forceSquare()
{
	if (height() < width())
		setWidth(height());
	else if (height() > width())
		setHeight(width());
}


void AngleSlider::setValueByTapPos(const int xInWidget, const int yInWidget)
{
	//move to middle
	qreal x = (xInWidget - (height()/2));
	qreal y = (yInWidget - (width()/2));

	//scale to unit circle
	qreal distanceToCenter = sqrt(x*x + y*y);
	x /= distanceToCenter;
	y /= distanceToCenter;

	if(distanceToCenter > width() / 4 && distanceToCenter < width()/2) {
		if (y > 0)
			m_value = acos(x);
		else
			m_value = 2*3.141569 - acos(x);
		emit valueChanged(m_value);
		setActive(true);
	}
}

void AngleSlider::processTapDown(mtq::TapEvent *event)
{
    setValueByTapPos(static_cast<int>(event->mappedCenter().x()),
                     static_cast<int>(event->mappedCenter().y()));
}

void AngleSlider::processTapUp(mtq::TapEvent *event)
{
	setActive(false);
}

void AngleSlider::processTapCancel(mtq::TapEvent *event)
{
	setActive(false);
}

bool AngleSlider::active() const
{
	return m_active;
}

void AngleSlider::setActive(const bool state)
{
	m_active = state;
	update();
}

qreal AngleSlider::value() const
{
	return m_value;
}

void AngleSlider::setValue(const qreal value)
{
	m_value = value;
}
