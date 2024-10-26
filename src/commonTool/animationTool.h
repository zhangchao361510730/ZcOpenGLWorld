#ifndef animationTool_H_
#define animationTool_H_

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include"commonTool/boneTool.h"
#include"commonTool/loadAnimation.h"

class animationTool
{
public:
	animationTool(loadAnimation* animation);

	void UpdateAnimation(float dt);

	void PlayAnimation(loadAnimation* pAnimation);

	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

	std::vector<glm::mat4> GetFinalBoneMatrices();

private:
	std::vector<glm::mat4> m_FinalBoneMatrices;
	loadAnimation* m_CurrentAnimation;
	float m_CurrentTime;
	float m_DeltaTime;

};
#endif