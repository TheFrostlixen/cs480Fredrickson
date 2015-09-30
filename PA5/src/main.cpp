#include "global.h"
#include "CShaderLoader.h"
#include "CModel.h"

#include <iostream>
#include <chrono>

/** Global Variables **/
int w = 640, h = 480; // Window size
GLuint program; // The GLSL program handle
GLuint vbo_geometry; // VBO handle for our geometry

// uniform locations
GLint loc_mvpmat; // Location of the model-view-projection matrix in the shader

// attribute locations
GLint loc_position;
GLint loc_color;

// transform matrices
Model mdl;
glm::mat4 view;            // world -> eye
glm::mat4 projection;    // eye -> clip
glm::mat4 mvp;            // premultiplied model-view-projection

// time management
std::chrono::time_point<std::chrono::high_resolution_clock> t1,t2;

/** GLUT Callbacks **/
void render();
void update();
void reshape(int n_w, int n_h);
void keyboard(unsigned char key, int x_pos, int y_pos);
void arrowkeys(int key, int x_pos, int y_pos);
void mouse(int btn, int state, int xPos, int yPos);
void menu(int);

/** Resource management **/
bool initialize();
void cleanUp();
float getDT();

/** Application entry point **/
int main(int argc, char **argv)
{
    // Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);

    // Name and create the Window
    glutCreateWindow("CS 480 - Fredrickson");

    // Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();
    if( status != GLEW_OK)
    {
        std::cerr << "[F] GLEW NOT INITIALIZED: ";
        std::cerr << glewGetErrorString(status) << std::endl;
        return -1;
    }

    // Set the GLUT callbacks and our context menu
    glutDisplayFunc(render);    // Called to render the scene
    glutReshapeFunc(reshape);    // Called if the window is resized
    glutIdleFunc(update);        // Called if there is nothing else to do
    glutKeyboardFunc(keyboard);    // Called if there is standard keyboard input
    glutSpecialFunc(arrowkeys); // Called if there is special keyboard input
    glutMouseFunc(mouse);        // Called if there is mouse input

    // Set up the menu
    int menu_id = glutCreateMenu(menu);
    glutSetMenu(menu_id);
    glutAddMenuEntry("Start spinning", 0);
    glutAddMenuEntry("Pause spinning", 1);
    glutAddMenuEntry("Quit game", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Initialize all of our resources (shaders & geometry)
    if ( initialize() )
    {
        t1 = std::chrono::high_resolution_clock::now();
        glutMainLoop();
    }

    // Clean up after ourselves
    cleanUp();
    return 0;
}

/** GLUT Callback Functions **/
void render()
{
    // Clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable the shader program
    glUseProgram(program);

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry);

    // Set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,    // location of attribute
                           3,                // number of elements
                           GL_FLOAT,        // type
                           GL_FALSE,        // normalized
                           sizeof(Vertex),    // stride
                           0 );                // offset in the geometry array

    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(Vertex),
                           0);

    // draw the model
    mvp = projection * view * mdl.GetModel();
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));
//    glDrawArrays(GL_TRIANGLES, 0, 36); // mode, starting index, count

    mdl.Draw();
    // Clean up
    glDisableVertexAttribArray(loc_position);
    glDisableVertexAttribArray(loc_color);

    // Add text
//  glUseProgram(0); // switch from shader programs to fixed function pipeline
//  glColor3f( 1.0f, 1.0f, 1.0f );
//  glRasterPos2f(0,0);
//  glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char*)planet.GetSpinDirection().c_str() );

    // Swap the buffers
    glutSwapBuffers();
}

void update()
{
    // total time
    float dt = getDT(); // if you have anything moving, use dt.

    // move the model around
    mdl.Scale(0.2);
    mdl.SetOrbit(0.0f, 0.0f);
    mdl.Orbit(glm::mat4(1.0f), dt, true, 0.0f);
    mdl.Spin(dt);
    mdl.Scale(0.2);

    // Update the state of the scene
    glutPostRedisplay(); //call the display callback
}

void reshape(int n_w, int n_h)
{
    // Set the width and height to new resized values
    w = n_w;
    h = n_h;

    // Change the viewport to match resize
    glViewport( 0, 0, w, h);

    // Update the projection matrix
    projection = glm::perspective(45.0f, float(w)/float(h), 0.01f, 100.0f);
}

void keyboard(unsigned char key, int x_pos, int y_pos)
{
    // Handle keyboard input
    switch (key)
    {
        case 27:
            glutLeaveMainLoop(); // ESC
            break;

        case '1':
//          planet.ToggleSpin();
            break;
    }
}

void arrowkeys(int key, int x_pos, int y_pos)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
//          planet.SwitchSpinDirection(true);
            break;

        case GLUT_KEY_RIGHT:
//          planet.SwitchSpinDirection(false);
            break;

        case GLUT_KEY_UP:
//          planet.ToggleSpin();
            break;

        case GLUT_KEY_DOWN:
//          planet.SwitchSpinDirection();
            break;
    }
}

void mouse(int btn, int state, int xPos, int yPos)
{
    // On left mouse click, reverse the spin direction
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
//      planet.SwitchSpinDirection();
    }
}

void menu(int value)
{
    // Menu callback, set states based on what menu option is selected
    switch (value)
    {
        // Start spinning
        case 0:
//          planet.SetSpinning(true);
            break;

        // Pause spinning
        case 1:
//          planet.SetSpinning(false);
            break;

        // Exit game
        case 2:
            glutLeaveMainLoop();
            break;
    }
}

/** End GLUT Callback Functions **/

/** Resource Management Functions **/
bool initialize()
{
    // Initialize basic geometry and shaders for this example

    mdl.LoadModel( "house.obj" );

    // Create a Vertex Buffer object (VBO) to store this vertex info on the GPU
    glGenBuffers(1, &vbo_geometry);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mdl.GetVertices().size(), &mdl.GetVertices().front(), GL_STATIC_DRAW);
    // Geometry is done

    // Load and compile shaders
    Shader vertexShader;
    Shader fragmentShader;

    vertexShader.Load("vertex.shader", GL_VERTEX_SHADER);
    fragmentShader.Load("fragment.shader", GL_FRAGMENT_SHADER);

    // Link the 2 shader objects into a program
    program = glCreateProgram();
    glAttachShader(program, vertexShader.GetID());
    glAttachShader(program, fragmentShader.GetID());
    glLinkProgram(program);

    // Check if the shaders linked properly
    GLint shader_status;
    glGetProgramiv(program, GL_LINK_STATUS, &shader_status);

    if(!shader_status)
    {
        std::cerr << "[F] THE SHADER PROGRAM FAILED TO LINK" << std::endl;
        return false;
    }

    // Set the locations of the attributes (out) and uniforms (in)
    //  this allows us to access them easily while rendering
    loc_position = glGetAttribLocation(program, const_cast<const char*>("v_position"));
    if(loc_position == -1)
    {
        std::cerr << "[F] POSITION NOT FOUND" << std::endl;
        return false;
    }
    loc_color = glGetAttribLocation(program, const_cast<const char*>("v_color"));
    if(loc_color == -1)
    {
        std::cerr << "[F] V_COLOR NOT FOUND" << std::endl;
        return false;
    }
    loc_mvpmat = glGetUniformLocation(program, const_cast<const char*>("mvpMatrix"));
    if(loc_mvpmat == -1)
    {
        std::cerr << "[F] MVPMATRIX NOT FOUND" << std::endl;
        return false;
    }

    // Set up any parameters for the models
//  mdl.SetOrbit(0.0f, 0.0f);

    // Init the view and projection matrices
    //  Matrices are defined statically because the camera is static
    view = glm::lookAt( glm::vec3(0.0, 4.0, -16.0),        // Eye Position
                        glm::vec3(0.0, 0.0, 0.0),        // Focus point
                        glm::vec3(0.0, 1.0, 0.0) );        // Y+ is up

    projection = glm::perspective( 45.0f,                // FoV (90 degrees)
                                   float(w)/float(h),    // Aspect ratio
                                   0.01f,                // Distance to the near plane
                                   100.0f );            // Distance to the far plane

    // Depth testing tells not to draw far-away occluded objects
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

void cleanUp()
{
    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo_geometry);
}

float getDT()
{
    float ret;
    t2 = std::chrono::high_resolution_clock::now();
    ret = std::chrono::duration_cast< std::chrono::duration<float> >(t2-t1).count();
    t1 = std::chrono::high_resolution_clock::now();
    return ret;
}

/** End Resource Management Functions **/

/** End MAIN.CPP **/
