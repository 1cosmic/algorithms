#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <Qcolor>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>

class openGL_sort: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    openGL_sort(QWidget *parent = nullptr);


protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void qColorToRGB(const QColor &C, float &r, float &g, float &b) const;
};

#endif // OPENGL_WIDGET_H
