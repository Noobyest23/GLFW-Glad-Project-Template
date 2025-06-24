#ifndef NAPP_QUERY
#define NAPP_QUERY

#include <glad/glad.h>

struct RenderInfo {
    int primitivesDrawn = 0;
	long gpuTime = 0;
};

class Query {
public:

	Query();
	~Query();
	
	void DeleteQueryData() const;

	void BeginQuery();
	void EndQuery();

	RenderInfo GetResult() const;

private:

	GLuint triCountQuery;
	GLuint gpuTimeQuery;

	RenderInfo result;

};


#endif