#include"animationTool.h"
#include"mainLoop.h"


animationTool::animationTool(loadAnimation* animation,animationScene* parten):parten_(parten) {
	m_CurrentAnimation = animation;
	m_FinalBoneMatrices.reserve(100);
	for (int i = 0; i < 100; i++) {
		m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
	}
}


void animationTool::UpdateAnimation(float dt) {
	 if (parten_->isAnimating) {
		if (m_CurrentAnimation) {
			parten_->m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * dt;
			//std::cout<<"parten_->m_CurrentTime "<<parten_->m_CurrentTime<<std::endl;
			parten_->m_CurrentTime = fmod(parten_->m_CurrentTime, m_CurrentAnimation->GetDuration());// 得到时间刻度
			CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
		}
	 }
}

void animationTool::PlayAnimation(loadAnimation* pAnimation) {
	m_CurrentAnimation = pAnimation;
	//m_CurrentTime = 0.0f;
}

void animationTool::CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform) {
	std::string nodeName = node->name;
	glm::mat4 nodeTransform = node->transformation;
	boneTool* boneTool = m_CurrentAnimation->FindBone(nodeName);
	if (boneTool) {
		boneTool->Update(parten_->m_CurrentTime );
		nodeTransform = boneTool->GetLocalTransform();
	}
	glm::mat4 globalTransformation = parentTransform * nodeTransform;
	std::map<std::string,BoneInfo> boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
	if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
		int index = boneInfoMap[nodeName].id;
		glm::mat4 offset = boneInfoMap[nodeName].offset;
		m_FinalBoneMatrices[index] = globalTransformation * offset;
	}
	for (int i = 0; i < node->childrenCount; i++) {
		CalculateBoneTransform(&node->children[i], globalTransformation);
	}
}

std::vector<glm::mat4> animationTool::GetFinalBoneMatrices() {
	return m_FinalBoneMatrices;
}

