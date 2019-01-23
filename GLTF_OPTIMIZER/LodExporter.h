#pragma once
#include <vector>
#include "MyMesh.h"
#include <unordered_map>
#include <stdio.h>

enum AccessorType
{
    POSITION,
    NORMAL,
    UV,
    INDEX
};
namespace tinygltf
{
    class Model;
    class Node;
    class TinyGLTF;
	class Mesh;
	class Material;
    class Primitive;
    class BufferView;
}
class LodExporter
{
public:
    LodExporter(tinygltf::Model* model, std::vector<MyMesh*> myMeshes, tinygltf::TinyGLTF* tinyGLTF);
    ~LodExporter();
    void ExportLods(std::vector<LodInfo> lodInfos, int level);
private:
    void getMeshIdxs(std::vector<int> nodeIdxs, std::vector<int>& meshIdxs);
    void traverseNode(tinygltf::Node* node, std::vector<int>& meshIdxs);

	int addNode(tinygltf::Node* node);
	int addMesh(tinygltf::Mesh* mesh);
	int addMaterial(int material);
	void addPrimitive(tinygltf::Primitive* primitive, tinygltf::Mesh* mesh);
	int addAccessor(AccessorType type);
    int addBufferView(AccessorType type, size_t& byteOffset);
    int addBuffer(AccessorType type);
	std::unordered_map<int, int> m_materialCache; // map between old material and new material;
private:
    tinygltf::Model* m_pModel;
	tinygltf::Model* m_pNewModel;
    std::vector<MyMesh*> m_myMeshes;
    TriEdgeCollapseQuadricParameter* m_pParams;
    tinygltf::TinyGLTF* m_pTinyGTLF;
    MyMesh* m_pCurrentMesh;
    std::string m_currentDir;
    std::vector<unsigned char> m_currentAttributeBuffer;
    std::vector<unsigned char> m_currentIndexBuffer;
    std::map<int, tinygltf::BufferView*> m_targetBufferViewMap;

    std::unordered_map<MyVertex*, uint32_t> m_vertexUintMap;
    std::unordered_map<MyVertex*, uint16_t> m_vertexUshortMap;

    float m_positionMax[3];
    float m_positionMin[3];
};

