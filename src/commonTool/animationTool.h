#ifndef animationTool_H_
#define animationTool_H_

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include"boneTool.h"
#include"loadAnimation.h"

class mainLoop;
class animationScene;

class animationTool
{
public:
	animationTool(loadAnimation* animation,mainLoop* parten);
	animationTool(loadAnimation* animation,animationScene* parten);

	void UpdateAnimation(float dt);

	void PlayAnimation(loadAnimation* pAnimation);

	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

	std::vector<glm::mat4> GetFinalBoneMatrices();

private:
	mainLoop* parten_;
	std::vector<glm::mat4> m_FinalBoneMatrices;
	loadAnimation* m_CurrentAnimation;
	//float m_CurrentTime;
	//float m_DeltaTime;

};
#endif