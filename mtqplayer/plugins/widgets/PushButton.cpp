#include "PushButton.h"

#include <QPainter>

#include "Design.h"

using namespace mtq;

//We need to register this Type in QML
QML_REGISTER_PLUGIN(PushButton)

PushButton::PushButton(QQuickItem *parent)
    : BaseWidget(parent),
      m_active(false),
      m_svgRenderer(new QSvgRenderer(design::widgetsSvgFile, this))
{
	setHeight(160);
	setWidth(250);
}

PushButton::PushButton(QQuickItem *parent, QString label)
    : BaseWidget(parent),
      m_active(false),
      m_svgRenderer(new QSvgRenderer(design::widgetsSvgFile, this))
{
	setHeight(160);
	setWidth(250);

    setText(label);
}

//This is the painting method. It paints the PushButton using the QPainter painter
void PushButton::paint(QPainter *painter)
{
	int roundedCornerSize = 40;
	if(height() < 80 || width() < 80)
		roundedCornerSize = 0;

	QString elementId;
	if (active())
		elementId = "pressed";
	else
		elementId = "normal";

	// Render SVG
    m_svgRenderer->render(painter, "PushButton::"+elementId+"::topleft", QRect(0, 0, roundedCornerSize, roundedCornerSize));
    m_svgRenderer->render(painter, "PushButton::"+elementId+"::middle", QRect(roundedCornerSize, 0,
																			 width() - (2*roundedCornerSize), height()));
    m_svgRenderer->render(painter, "PushButton::"+elementId+"::bottomleft", QRect(0, height() - roundedCornerSize,
																				roundedCornerSize, roundedCornerSize));
    m_svgRenderer->render(painter, "PushButton::"+elementId+"::topright", QRect(width() - roundedCornerSize, 0,
																			   roundedCornerSize, roundedCornerSize));
    m_svgRenderer->render(painter, "PushButton::"+elementId+"::middle", QRect(0,roundedCornerSize,
																			width(), height() - (2*roundedCornerSize)));
    m_svgRenderer->render(painter, "PushButton::"+elementId+"::bottomright", QRect(width() - roundedCornerSize, height() - roundedCornerSize,
																			   roundedCornerSize, roundedCornerSize));

	// Render caption
	QRectF rect(0, 0, width(), height());
	painter->setPen(design::labelFontColor);
	painter->setFont(design::labelFont);
	painter->drawText(rect, Qt::AlignCenter , m_text);
}


void PushButton::mousePressEvent(QMouseEvent *event) {
	BaseWidget::mousePressEvent(event);
	setActive(true);
	emit pressed();
}

void PushButton::mouseReleaseEvent(QMouseEvent *event) {
	BaseWidget::mouseReleaseEvent(event);
	setActive(false);
}

void PushButton::tapDown(mtq::TapEvent *event) {
	BaseWidget::tapDown(event);
	setActive(true);
	emit pressed();
}

void PushButton::tapUp(mtq::TapEvent *event) {
	BaseWidget::tapUp(event);
	setActive(false);
}

void PushButton::tapCancel(mtq::TapEvent *event) {
	BaseWidget::tapCancel(event);
	setActive(false);
}



QString PushButton::text()
{
	return m_text;
}

void PushButton::setText(QString text)
{
	m_text = text;
}

bool PushButton::active()
{
	return m_active;
}

void PushButton::setActive( bool state)
{
	m_active = state;
	update();
}
