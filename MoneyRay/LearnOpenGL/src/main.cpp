#include "Application.h"
#include "../test/FunctorTest.h"
#include "RenderManager.h"
#include "shader/ShaderProgram.h"

int main()
{
	LOGL::Application app;
	LOGL::RenderManager& renderManager = app.GetRenderManager();
	LOGL::RenderJob job(
		[]()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat vertices[] = {
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		GLuint indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		GLuint VBO;
		glGenBuffers(1, &VBO);
		GLuint EBO;
		glGenBuffers(1, &EBO);
		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//do NOT unbind the EBO, keep it bound to this VAO
		}
		glBindVertexArray(0);


		LOGL::ShaderProgram program("shader/first.vs", "shader/first.fs");
		program.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	});
	renderManager.AddRenderJob(job);

	app.Init();
	app.Run();
	return 0;
}