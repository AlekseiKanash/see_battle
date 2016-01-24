#ifndef SCENEPARAMETERS_H
#define SCENEPARAMETERS_H

#include <QColor>

namespace SceneParams
{

static qint32 cellSize = 20;
static qint32 sceneSize = 10; // scene size size x size in cells
static qint32 minLen = 1;
static qint32 maxLen = 5;

static qint32 sheepBorderWidth = 2;
static QColor sheepBorderColor = QColor(Qt::blue);

static float sheetLinesWidth = 0.1;
static QColor sheetLinesColor = QColor(Qt::black);

}

#endif // SCENEPARAMETERS_H
