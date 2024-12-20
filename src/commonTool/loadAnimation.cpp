#include"loadAnimation.h"

loadAnimation::loadAnimation(const std::string& animationPath, modelBindAnimation* model) {
	Assimp::Importer importer;
	    // 加载 FBX 文件
    //const aiScene* scene = importer.ReadFile(animationPath,aiProcess_Triangulate|aiProcess_FlipUVs |aiProcess_CalcTangentSpace); 
	const aiScene *scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	auto animation = scene->mAnimations[0];
	m_Duration = animation->mDuration;
	m_TicksPerSecond = animation->mTicksPerSecond;
	aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
	globalTransformation = globalTransformation.Inverse();
	ReadHierarchyData(m_RootNode, scene->mRootNode);
	ReadMissingBones(animation, *model);
}


boneTool* loadAnimation::FindBone(const std::string& name) {
	auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),[&](const boneTool& boneTool) {
			return boneTool.GetBoneName() == name;
		}
	);
	if (iter == m_Bones.end()) return nullptr;
	else return &(*iter);
}

	
float loadAnimation::GetTicksPerSecond() { 
	return m_TicksPerSecond; 
}

float loadAnimation::GetDuration() { 
	return m_Duration;
}

const AssimpNodeData& loadAnimation::GetRootNode() { 
	return m_RootNode; 
}

const std::map<std::string,BoneInfo>& loadAnimation::GetBoneIDMap() { 
	return m_BoneInfoMap;
}

void loadAnimation::ReadMissingBones(const aiAnimation* animation, modelBindAnimation& model) {
	int size = animation->mNumChannels;
	auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from modelBindAnimation class
	int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from modelBindAnimation class
	//reading channels(bones engaged in an animation and their keyframes)
	for (int i = 0; i < size; i++) {
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;
		if (boneInfoMap.find(boneName) == boneInfoMap.end())
		{
			boneInfoMap[boneName].id = boneCount;
			boneCount++;
		}
		m_Bones.push_back(boneTool(channel->mNodeName.data,
			boneInfoMap[channel->mNodeName.data].id, channel));
	}
	m_BoneInfoMap = boneInfoMap;
}

void loadAnimation::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src) {
	assert(src);
	dest.name = src->mName.data;
	dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
	dest.childrenCount = src->mNumChildren;
	for (int i = 0; i < src->mNumChildren; i++) {
		AssimpNodeData newData;
		ReadHierarchyData(newData, src->mChildren[i]);
		dest.children.push_back(newData);
	}
}