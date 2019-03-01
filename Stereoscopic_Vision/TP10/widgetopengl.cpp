// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

#include "widgetopengl.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions()
{
    grabKeyboard();
}

WidgetOpenGL::~WidgetOpenGL()
{
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor ( 0 , 0.204f, 0.627f, 0.792f );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_camera = new CameraSpherique();
    m_camera->setAspect_ratio(GLfloat(width())/height());
    m_camera->setPosition(QVector3D(0, 1, 5));
    m_camera->setRho(100);
    m_camera->setTarget(QVector3D(0,50,-100));

    m_cameraSub = new CameraSubjective();
    m_cameraSub->setAspect_ratio(GLfloat(width())/height());
    m_cameraSub->setZmax(2000.0f);
    m_cameraSub->setPosition(QVector3D(0,50,-100));
    m_cameraSub->setFov(45.0f);
    m_cameraSub->updateTarget();

    m_gamepad = new QGamepad();

    m_timer = new QElapsedTimer();
    m_timer->start();
    m_fps_cpt = 0;
    m_fps = 0;

    m_help = false;
    m_help_timer = new QElapsedTimer();

    m_switch = 0;
    m_switch_timer = new QElapsedTimer();

    m_light = new Light();
    m_light->setLight_position(QVector3D(0,5,0));
    m_light->setSpecular_strength(500);

    m_batiment = new Model("C:/Users/user/Desktop/RealiteVirtuelle/TP9/model/IUT_INFO.X");
    m_batiment->setLight(m_light);
    m_batiment->setCamera(m_cameraSub);

}

void WidgetOpenGL::paintGL(){
    // ----------
    m_fps_cpt += 1.0f;

    if(m_timer->elapsed() >= 1000) {
        m_fps = m_fps_cpt;
        m_fps_cpt = 0;
        m_timer->restart();
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    QPainter p(this);
    p.beginNativePainting();

    //-------

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //------

    if(m_switch == DDD_VIEW) {

        glColorMask(true,false,false,false);
        m_cameraSub->setTypeCamera(LEFT);
        m_batiment->draw();
        glClear(GL_DEPTH_BUFFER_BIT);
        glColorMask(false,true,true,false);
        m_cameraSub->setTypeCamera(RIGHT);
        m_batiment->draw();
        glColorMask(true,true,true,true);
    }

    if(m_switch == DOUBLE_VIEW){
        glViewport(0,0, width() / 2.0f, height());
        m_cameraSub->setTypeCamera(LEFT);
        m_batiment->draw();
        glClear(GL_DEPTH_BUFFER_BIT);

        glViewport(width() / 2.0f,0, width(), height());
        m_cameraSub->setTypeCamera(RIGHT);
        m_batiment->draw();
    }

    if(m_switch == NORMAL_VIEW){
        m_cameraSub->setTypeCamera(MONO);
        m_batiment->draw();
    }

    p.endNativePainting();

    if(m_switch == DOUBLE_VIEW){
        p.drawImage(QPointF(0,0), QImage(":/images/ecranRV.PNG"));
        glEnable(GL_ALPHA_TEST);
    }

    p.setPen(Qt::magenta);
    p.setFont(QFont("Athelas",14));
    p.drawText(width() - 125,5,width(),height(),Qt::AlignLeft,"Fps = "+QString::number(m_fps,'f',2));

    if(m_help) {

        float centerX = width() / 2;
        float centerY = height() / 2;
        float dy = 40;
        float x = centerX - 300;
        float y = centerY - 190;

        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Keyboard/Mouse commands : ");
        y += dy;
        p.setPen(Qt::green);
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key Up/Down/Left/Right : Move around ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Mouse move : Move camera ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key P/M : Change fov ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key U/D : Go up and down");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key Space : Jump");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key R : Run");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key S : Switch beetween view ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key H : Help Menu ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Key E : Quit ");


        x += 350;
        y = centerY - 190;
        p.setPen(Qt::magenta);
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Gamepad commands : ");
        p.setPen(Qt::green);
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Joystick left : Move around ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Joystick Right : Move camera ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Button Up/Down : Change fov ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Buttons Y/X :  Go go up and down");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Button A : Jump");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Button L3 + Joystick left : Run");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Button Start : Switch between view ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Button B : Help menu ");
        y += dy;
        p.drawText(x, y, width() , height() ,Qt::AlignLeft,"Button back : Quit ");
    }

    update();
}

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

void WidgetOpenGL::update()
{

    float padLeftX = m_gamepad->axisLeftX();
    float padLeftY = m_gamepad->axisLeftY();
    float padRightX = m_gamepad->axisRightX();
    float padRightY = m_gamepad->axisRightY();
    bool fovUp = m_gamepad->buttonUp();
    bool fovDown = m_gamepad->buttonDown();
    bool back = m_gamepad->buttonSelect();
    bool help = m_gamepad->buttonB();
    bool up = m_gamepad->buttonY();
    bool down = m_gamepad->buttonX();
    bool switchView = m_gamepad->buttonStart();
    bool run = m_gamepad->buttonL3();
    bool jump = m_gamepad->buttonA();

    m_cameraSub->lateral(padLeftX);
    m_cameraSub->avance(-padLeftY);

    m_cameraSub->setTangage(m_cameraSub->tangage() - padRightY);
    m_cameraSub->setLacet(m_cameraSub->lacet() - padRightX);

    if(run) {
        m_cameraSub->avance(-padLeftY * 3);
    }

    if(jump) {
        m_cameraSub->jump();
    }

    if(fovUp) {
        m_cameraSub->setFov(m_cameraSub->fov() - 1.0);
    }
    if(fovDown) {
        m_cameraSub->setFov(m_cameraSub->fov() + 1.0);
    }

    float speed = 1.0f;
    bool goodUp = (m_cameraSub->position().y() + speed) <= 50;
    bool goodDown = (m_cameraSub->position().y() - speed) > 2;

    if(up && goodUp) {
        m_cameraSub->vertical(speed);
    }

    if(down && goodDown) {
        m_cameraSub->vertical(-speed);
    }

    if(back) {
        std::cout << "Goodbye my friend !" << std::endl;
        QCoreApplication::exit();
    }

    if(help){
        bool timerStarted = m_help_timer->isValid();
        if(timerStarted){
            int elapsedMs = m_help_timer->elapsed();
            if(elapsedMs >= 250){
                m_help = !m_help;
                m_help_timer->restart();
            }
        } else {
            m_help_timer->start();
            m_help = !m_help;
        }
    }

    if(switchView){
        bool timerStarted = m_switch_timer->isValid();
        if(timerStarted){
            int elapsedMs = m_switch_timer->elapsed();
            if(elapsedMs >= 250){
                m_switch += 1;
                m_switch %= 3;
                m_switch_timer->restart();
            }
        } else {
            m_switch_timer->start();
            m_switch += 1;
            m_switch %= 3;
        }
    }
    m_cameraSub->updateJump();
    QOpenGLWidget::update();
}

void WidgetOpenGL::mousePressEvent(QMouseEvent* event){
    lastPos = event->pos();

    float x = lastPos.x();
    float y = lastPos.y();

    float exitx = 10;
    float exity = 10;
    float exitxw = exitx + 23;
    float exityh = exity + 21;

    float helpx = 420;
    float helpy = 405;
    float helpxw = helpx + 28;
    float helpyh = helpy + 26;


    if(m_switch == DOUBLE_VIEW && x >= exitx && x <= exitxw && y >= exity && y <= exityh){
        std::cout << "Exiting application through mouse event..." << std::endl;
        QCoreApplication::exit(0);
    }

    if(m_switch == DOUBLE_VIEW && x >= helpx && x <= helpxw && y >= helpy && y <= helpyh){
        m_help = !m_help;
    }
}

void WidgetOpenGL::mouseMoveEvent(QMouseEvent* event){
    float dx = (event->pos().x() - lastPos.x()) / static_cast<float> (width());
    float dy = (event->pos().y() - lastPos.y()) / static_cast<float> (height());

    m_cameraSub->setTangage(m_cameraSub->tangage() - dy * 30); // + pour tirer
    m_cameraSub->setLacet(m_cameraSub->lacet() - dx * 30);

    QOpenGLWidget::update();
    lastPos = event->pos();
}

Light *WidgetOpenGL::light() const
{
    return m_light;
}

void WidgetOpenGL::setLight(Light *light)
{
    m_light = light;
}

void WidgetOpenGL::keyPressEvent(QKeyEvent*event){
    float speed = 1.0f;
    bool goodUp = (m_cameraSub->position().y() + speed) <= 50;
    bool goodDown = (m_cameraSub->position().y() - speed) > 2;
    switch(event->key()){
        case Qt::Key_Up:
            m_cameraSub->avance(speed);
            break;
        case Qt::Key_Down:
            m_cameraSub->avance(-speed);
            break;
        case Qt::Key_Right:
             m_cameraSub->lateral(speed);
             break;
        case Qt::Key_Left:
             m_cameraSub->lateral(-speed);
            break;
        case Qt::Key_U:
             if(goodUp)
             m_cameraSub->vertical(speed);
             break;
        case Qt::Key_D:
             if(goodDown)
             m_cameraSub->vertical(-speed);
             break;
        case Qt::Key_H:
            m_help = !m_help;
            break;
        case Qt::Key_S:
            m_switch += 1;
            m_switch %= 3;
            break;
        case Qt::Key_E :
            std::cout << "Goodbye my friend !" << std::endl;
            QCoreApplication::exit();
            break;
        case Qt::Key_P:
            m_cameraSub->setFov(m_cameraSub->fov() - 1.0);
            break;
        case Qt::Key_M:
            m_cameraSub->setFov(m_cameraSub->fov() + 1.0);
            break;
        case Qt::Key_Space:
            m_cameraSub->jump();
            break;
        case Qt::Key_R:
            m_cameraSub->avance(speed*3);
            break;
         default:
            break;
         }

    update();

}

