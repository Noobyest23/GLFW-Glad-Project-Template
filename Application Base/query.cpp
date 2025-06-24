#include "query.h"

Query::Query() {
	triCountQuery = 0;
	gpuTimeQuery = 0;

	glGenQueries(1, &triCountQuery);
	glGenQueries(1, &gpuTimeQuery);
}

Query::~Query() {
	DeleteQueryData();
}

void Query::DeleteQueryData() const {
	glDeleteQueries(1, &triCountQuery);
	glDeleteQueries(1, &gpuTimeQuery);
}

RenderInfo Query::GetResult() const {
	return result;
}

void Query::BeginQuery() {
	glBeginQuery(GL_PRIMITIVES_GENERATED, triCountQuery);
	glBeginQuery(GL_TIME_ELAPSED, gpuTimeQuery);
}

void Query::EndQuery() {

	glEndQuery(GL_PRIMITIVES_GENERATED);
	glEndQuery(GL_TIME_ELAPSED);

	GLuint64 gpuTime = 0;
	GLuint triangles = 0;
	glGetQueryObjectui64v(gpuTimeQuery, GL_QUERY_RESULT, &gpuTime);
	glGetQueryObjectuiv(triCountQuery, GL_QUERY_RESULT, &triangles);

	result.primitivesDrawn = triangles;
	result.gpuTime = gpuTime;
}