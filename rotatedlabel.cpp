/*
    File    :   rotatedlabel.cpp
    Project :   LightPlot2D

    Last modified July 8, 2010

    Copyright (C) 2010 Avdeev Maxim (avdeyev_mv@mail.ru)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/
#include "rotatedlabel.h"
#include <QPainter>

RotatedLabel::RotatedLabel(const QString &text, QWidget *parent)
        : QWidget(parent), _label(text)
{
    _angle = 0;
    _label.setTextFormat(Qt::RichText);
}
//-----------------------------------------------------------------------------

void RotatedLabel::setAngle(qreal angle)
{
    if (_angle != angle) {
        _angle = angle;
        updateBuffer();
    }
}
//-----------------------------------------------------------------------------

void RotatedLabel::setText(const QString &text)
{
    if (text != _label.text()) {
        _label.setText(text);
        updateBuffer();
    }
}
//-----------------------------------------------------------------------------

void RotatedLabel::updateBuffer()
{
    _label.setFont(this->font());
    _label.setPalette(palette());
    _label.adjustSize();
    _img = QImage(_label.size(), QImage::Format_ARGB32);
    _label.render(&_img);
    QTransform t;
    t.rotate(_angle);
    _img = _img.transformed(t, Qt::SmoothTransformation);
    setMinimumSize(_img.width(), _img.height());

    QRgb clr0 = _img.pixel(0, 0);

    for (int n = 0; n < _img.width(); ++n) {
        for (int m = 0; m < _img.height(); ++m) {
            QRgb clr = _img.pixel(n, m);
            if (clr == clr0) {
                _img.setPixel(n, m, 0x00ffffff);
            }
        }
    }
    update();
}
//-----------------------------------------------------------------------------

void RotatedLabel::updateLabel()
{
    updateBuffer();
}
//-----------------------------------------------------------------------------

QSize RotatedLabel::sizeHint() const
{
    return minimumSize();
}
//-----------------------------------------------------------------------------

QSize RotatedLabel::minimumSizeHint() const
{
    return minimumSize();
}
//-----------------------------------------------------------------------------

void RotatedLabel::resizeEvent(QResizeEvent */*event*/)
{
    updateBuffer();
}
//-----------------------------------------------------------------------------

void RotatedLabel::paintEvent(QPaintEvent */*event*/)
{ 
    QPainter painter(this);
    int x = 0;
    int y = 0;

    Qt::Alignment alignment = _label.alignment();

    switch (alignment) {

    case Qt::AlignHCenter: x = (width() - _img.width())/2;
        break;
    case Qt::AlignRight: x = width() - _img.width();
        break;
    case Qt::AlignVCenter: y = (height() - _img.height())/2;
        break;
    case Qt::AlignBottom: y = height() - _img.height();
        break;
    case Qt::AlignCenter: {
            x = (width() - _img.width())/2;
            y = (height() - _img.height())/2;
        } break;

    default: break;
    }

    if (alignment == (Qt::AlignLeft | Qt::AlignTop)) {
        x = 0;
        y = 0;
    }
    if (alignment == (Qt::AlignLeft | Qt::AlignVCenter)) {
        x = 0;
        y = (height() - _img.height())/2;
    }
    if (alignment == (Qt::AlignLeft | Qt::AlignBottom)) {
        x = 0;
        y = height() - _img.height();
    }

    if (alignment == (Qt::AlignHCenter | Qt::AlignTop)) {
        x = (width() - _img.width())/2;
        y = 0;
    }
    if (alignment == (Qt::AlignHCenter | Qt::AlignBottom)) {
        x = (width() - _img.width())/2;
        y = height() - _img.height();
    }

    if (alignment == (Qt::AlignRight | Qt::AlignTop)) {
        x = width() - _img.width();
        y = 0;
    }
    if (alignment == (Qt::AlignRight | Qt::AlignVCenter)) {
        x = width() - _img.width();
        y = (height() - _img.height())/2;
    }
    if (alignment == (Qt::AlignRight | Qt::AlignBottom)) {
        x = width() - _img.width();
        y = height() - _img.height();
    }

    painter.drawImage(x, y, _img);
}
//-----------------------------------------------------------------------------

void RotatedLabel::setAlignment(Qt::Alignment alignment)
{
    if (alignment != _label.alignment()) {
        _label.setAlignment(alignment);
        updateBuffer();
    }
}
//-----------------------------------------------------------------------------

Qt::Alignment RotatedLabel::alignment() const
{
    return _label.alignment();
}
//-----------------------------------------------------------------------------

QString RotatedLabel::text() const
{
    return _label.text();
}
//-----------------------------------------------------------------------------

qreal RotatedLabel::angle() const
{
    return _angle;
}
//-----------------------------------------------------------------------------
