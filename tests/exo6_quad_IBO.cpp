//#include <glimac/SDLWindowManager.hpp>
//#include <glimac/FilePath.hpp>
//#include <glimac/Program.hpp>
//#include <glimac/glm.hpp>
//#include <GL/glew.h>
//#include <iostream>

//using namespace glimac;

//struct Vertex2DUV {
//   glm::vec2 position;
//   glm::vec2 texture;

//   Vertex2DUV(){}

//   Vertex2DUV(glm::vec2 position, glm::vec2 texture):
//       position(position), texture(texture) {}
//};

//struct Vertex2DColor {
//   glm::vec2 position;
//   glm::vec3 color;

//   Vertex2DColor() {
//   }

//   Vertex2DColor(glm::vec2 position, glm::vec3 color):
//       position(position), color(color) {
//   }
//};

//glm::mat3 translate(float tx, float ty) {
//   return glm::mat3(
//       glm::vec3(1, 0, 0),
//       glm::vec3(0, 1, 0),
//       glm::vec3(tx, ty, 1)
//   );
//};



//int main(int argc, char** argv) {
//   // Initialize SDL and open a window
//   SDLWindowManager windowManager(600, 600, "GLImac");

//   // Initialize glew for OpenGL3+ support
//   GLenum glewInitError = glewInit();
//   if(GLEW_OK != glewInitError) {
//       std::cerr << glewGetErrorString(glewInitError) << std::endl;
//       return EXIT_FAILURE;
//   }

//   std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
//   std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

//   FilePath applicationPath(argv[0]);
//   Program program = loadProgram(applicationPath.dirPath() + "shaders/quad.vs.glsl",
//                                 applicationPath.dirPath() + "shaders/quad.fs.glsl");
//   program.use();

//   GLuint vbo;
//   glGenBuffers(1, &vbo);

//   glBindBuffer(GL_ARRAY_BUFFER, vbo);

//   // => Tableau de sommets : un seul exemplaire de chaque sommet
//   Vertex2DColor vertices[] = {
//       Vertex2DColor(glm::vec2(-0.25, -0.25), glm::vec3(1, 0, 0)), // Sommet 0
//       Vertex2DColor(glm::vec2(0.25, -0.25), glm::vec3(0, 1, 0)), // Sommet 1
//       Vertex2DColor(glm::vec2(0.25, 0.25), glm::vec3(0, 0, 1)), // Sommet 2
//       Vertex2DColor(glm::vec2(-0.25, 0.25), glm::vec3(1, 1, 1)) // Sommet 3
//   };

//   // => Penser à bien changer le nombre de sommet (4 au lieu de 6):
//   glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);

//   glBindBuffer(GL_ARRAY_BUFFER, 0);

//   // => Creation du IBO
//   GLuint ibo;
//   glGenBuffers(1, &ibo);

//   // => On bind sur GL_ELEMENT_ARRAY_BUFFER, cible reservée pour les IBOs
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

//   // => Tableau d'indices: ce sont les indices des sommets à dessiner
//   // On en a 6 afin de former deux triangles
//   // Chaque indice correspond au sommet correspondant dans le VBO
//   uint32_t indices[] = {
//       0, 1, 2, 0, 2, 3
//   };

//   // => On remplit l'IBO avec les indices:
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

//   // => Comme d'habitude on debind avant de passer à autre chose
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//   GLuint vao;
//   glGenVertexArrays(1, &vao);

//   glBindVertexArray(vao);

//   // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
//   // cela a pour effet d'enregistrer l'IBO dans le VAO
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

//   const GLuint VERTEX_ATTR_POSITION = 0;
//   const GLuint VERTEX_ATTR_COLOR = 1;

//   glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//   glEnableVertexAttribArray(VERTEX_ATTR_COLOR);


//   glBindBuffer(GL_ARRAY_BUFFER, vbo);

//   glVertexAttribPointer(
//       VERTEX_ATTR_POSITION,
//       2,
//       GL_FLOAT,
//       GL_FALSE,
//       sizeof(Vertex2DColor),
//       (const GLvoid*) offsetof(Vertex2DColor, position)
//   );

//   glVertexAttribPointer(
//       VERTEX_ATTR_COLOR,
//       3,
//       GL_FLOAT,
//       GL_FALSE,
//       sizeof(Vertex2DColor),
//       (const GLvoid*) offsetof(Vertex2DColor, color)
//   );


//   // Setup instance rendering
//   const GLuint CUBE_POSITION = 2;
//   glm::vec3 positions[] = {
//       glm::vec3(-0.5, 0, 0),
//       glm::vec3(0.5, 0, 0)
//   };

//   // Create buffer
//   GLuint position_buffer;
//   glGenBuffers(1, &position_buffer);

//   // Binding buffer
//   glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
//   // Describing buffer
//   glVertexAttribPointer(CUBE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//   glEnableVertexAttribArray(CUBE_POSITION);
//   // This is the important bit... set the divisor for the color array
//   // to 1 to get OpenGL to give us a new value of "color" per-instance
//   // rather than per-vertex.
//   glVertexAttribDivisor(CUBE_POSITION, 1);


//   glBindBuffer(GL_ARRAY_BUFFER, 0);

//   glBindVertexArray(0);

//   // Application loop:
//   bool done = false;
//   while(!done) {
//       // Event loop:
//       SDL_Event e;
//       while(windowManager.pollEvent(e)) {
//           if(e.type == SDL_QUIT) {
//               done = true; // Leave the loop after this iteration
//           }
//       }

//       glClear(GL_COLOR_BUFFER_BIT);

//       glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
//       glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2, positions, GL_DYNAMIC_DRAW);
//       glBindVertexArray(vao);

//       glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 2);
//       glBindVertexArray(0);

//       // Update the display
//       windowManager.swapBuffers();
//   }

//   glDeleteBuffers(1, &vbo);
//   glDeleteBuffers(1, &position_buffer);
//   glDeleteVertexArrays(1, &vao);

//   return EXIT_SUCCESS;
//}


