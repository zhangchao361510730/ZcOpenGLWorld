#ifndef loadAnimation_H_
#define loadAnimation_H_

#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <learnopengl/bone.h>
#include <functional>
#include <learnopengl/animdata.h>
#include <learnopengl/model_animation.h>

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class loadAnimation
{
public:
	loadAnimation() = default;
	loadAnimation(const std::string& animationPath, Model* model);
	~loadAnimation() = default;
	Bone* FindBone(const std::string& name);
	inline float GetTicksPerSecond();
	inline float GetDuration();
	inline const AssimpNodeData& GetRootNode();
	inline const std::map<std::string,BoneInfo>& GetBoneIDMap();
private:
	void ReadMissingBones(const aiAnimation* animation, Model& model);
	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);
	float m_Duration;
	int m_TicksPerSecond;
	std::vector<Bone> m_Bones;
	AssimpNodeData m_RootNode;
	std::map<std::string, BoneInfo> m_BoneInfoMap;
};











#endif