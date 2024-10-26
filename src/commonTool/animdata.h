#ifndef animadata_H_
#define animadata_H_
#include<glm/glm.hpp>

struct BoneInfo {
	/*id is index in finalBoneMatrices*/
	int id;
	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;
};

#endif